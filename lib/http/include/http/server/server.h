#ifndef MUS_HTTP_SERVER_SERVER_H_
#define MUS_HTTP_SERVER_SERVER_H_

#include <thread>  // std::thread
#include <memory>  // std::unique_ptr, std::shared_ptr
#include <vector>  // std::vector

namespace music_share {
namespace http {
namespace server {

class Acceptor;
class Router;

class Server {
public:
    Server(const std::string& portnum);
    Server(const std::string& portnum, size_t workers_qty);
    ~Server() = default;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void Run();
private:
    void on_stop();

    std::string m_portnum;
    size_t m_workers_qty;
    std::vector<std::thread> m_workers;
    std::unique_ptr<Acceptor> m_acceptor;
    std::shared_ptr<Router> m_router;
};

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_SERVER_H_
