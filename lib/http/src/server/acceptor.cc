#include "http/server/acceptor.h"

#include "http/server/connection.h"
#include "http/server/router/router.h"

namespace music_share {
namespace http {
namespace server {

Acceptor::Acceptor(boost::asio::io_context& io,
                   const std::string& address,
                   const std::string& portnum,
                   std::weak_ptr<router::Router> router_ptr)
    : m_io(io),
      m_acceptor(boost::asio::make_strand(m_io.get())),
      m_router(router_ptr) {
    boost::asio::ip::tcp::resolver resolver(m_io.get());
    boost::asio::ip::tcp::endpoint endpoint =
        *resolver.resolve(address, portnum).begin();
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();
}

void Acceptor::Run() {
    accept();
}

void Acceptor::accept() {
    m_acceptor.async_accept(
        boost::asio::make_strand(m_io.get()),
        boost::beast::bind_front_handler(&Acceptor::on_accept,
                                         shared_from_this())
    );
}

void Acceptor::on_accept(boost::beast::error_code e,
                         boost::asio::ip::tcp::socket socket) {
    if (e) {
    } else {
        auto connection = std::make_shared<Connection>(std::move(socket),
                                                       m_router);
        connection->Start();
    }

    accept();
}

}  // namespace server
}  // namespace http
}  // namespace music_share
