#ifndef MUS_HTTP_SERVER_SERVER_H_
#define MUS_HTTP_SERVER_SERVER_H_

#include <memory>  // std::unique_ptr, std::shared_ptr
#include <vector>  // std::vector
#include <boost/asio.hpp>

namespace music_share {
namespace http {
namespace server {
namespace router {

class Router;

}  // namespace router

class Acceptor;

class Server {
public:
    Server(const std::string& address, const std::string& portnum);
    Server(const std::string& address, const std::string& portnum,
           size_t workers_qty);
    ~Server() = default;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    router::Router& Router();

    void Run();
private:
    void on_stop();

    size_t m_workers_qty;
    boost::asio::io_context m_io;
    std::shared_ptr<router::Router> m_router;
    std::shared_ptr<Acceptor> m_acceptor;
};

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_SERVER_H_
