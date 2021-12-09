#include "http/server/connection.h"

#include "http/server/router/route.h"
#include "http/server/router/routenode.h"
#include "http/server/router/routetrie.h"
#include "http/server/router/router.h"

namespace music_share::http::server {

Connection::Connection(boost::asio::ip::tcp::socket&& socket,
                       std::weak_ptr<router::Router> router_ptr)
    : m_stream(std::move(socket)),
      m_router(router_ptr) {}

void Connection::Start() {
    boost::asio::dispatch(
        m_stream.get_executor(),
        boost::beast::bind_front_handler(&Connection::read,
                                         shared_from_this())
    );
}

void Connection::read() {
    m_request = {};

    boost::beast::http::async_read(
        m_stream, m_buffer, m_request,
        boost::beast::bind_front_handler(&Connection::on_read,
                                         shared_from_this())
    );
}

void Connection::on_read(boost::beast::error_code e, size_t transfered) {
    if (e == boost::beast::http::error::end_of_stream) {
        return close();
    }

    if (e) {
        // TODO: send 5xx
    }

    if (m_router.use_count() <= 0) {
        return close();
    }

    auto [handler, params] = m_router.lock()->RouteTo(m_request);

    namespace http = boost::beast::http;
    using ResponseMessage = http::message<false, http::string_body>;
    auto message =
        std::make_shared<ResponseMessage>(handler(m_request, params));
    message->set(boost::beast::http::field::server,
                 BOOST_BEAST_VERSION_STRING);
    //for (const auto& header_it: m_request.base()) {
        //message->set(header_it.name(), header_it.value());
    //}
    m_response = message;

    boost::beast::http::async_write(
        m_stream, *message,
        boost::beast::bind_front_handler(&Connection::on_write,
                                         shared_from_this(),
                                         message->need_eof())
    );
}

void Connection::on_write(bool need_close, boost::beast::error_code e,
                          size_t transfered) {
    if (need_close) {
        return close();
    }

    if (!e) {
        read();
    }
}

void Connection::close() {
    boost::beast::error_code e;
    m_stream
        .socket()
        .shutdown(boost::asio::ip::tcp::socket::shutdown_send, e);
}

}  // namespace music_share::http::server
