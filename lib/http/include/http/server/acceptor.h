// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_SERVER_ACCEPTOR_H_
#define MUS_HTTP_SERVER_ACCEPTOR_H_

#include <memory>  // std::shared_ptr
#include <functional>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace music_share {
namespace http {
namespace server {

namespace router {

class Router;

}  // namespace router

class Acceptor: public std::enable_shared_from_this<Acceptor> {
public:
    //Acceptor(std::shared_ptr<Router>& router);
    Acceptor(boost::asio::io_context& io,
             const std::string& address,
             const std::string& portnum,
             std::weak_ptr<router::Router> router_ptr);
    ~Acceptor() = default;

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    void Run();
private:
    void accept();
    void on_accept(boost::beast::error_code e, boost::asio::ip::tcp::socket);

    std::reference_wrapper<boost::asio::io_context> m_io;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::weak_ptr<router::Router> m_router;
};

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_ACCEPTOR_H_
