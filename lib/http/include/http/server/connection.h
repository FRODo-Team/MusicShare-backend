#ifndef MUS_HTTP_SERVER_CONNECTION_H_
#define MUS_HTTP_SERVER_CONNECTION_H_

#include <memory>  // std::shared_ptr
#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "http/common/request.h"

namespace music_share {
namespace http {
namespace server {

namespace router {

class Router;

}  // namespace router

class Connection : public std::enable_shared_from_this<Connection> {
public:
    Connection(boost::asio::ip::tcp::socket&& socket,
               std::weak_ptr<router::Router> router_ptr);
    ~Connection() = default;

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    void Start();
private:
    void read();
    void on_read(boost::beast::error_code e, size_t transfered);
    void on_write(bool need_close, boost::beast::error_code e,
                  size_t transfered);
    void close();

    boost::beast::tcp_stream m_stream;
    boost::beast::flat_buffer m_buffer;
    common::Request m_request;
    std::weak_ptr<router::Router> m_router;

    //std::shared_ptr<Router> m_router;
};


}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_CONNECTION_H_
