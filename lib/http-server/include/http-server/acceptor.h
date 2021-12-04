#ifndef MUS_HTTPSERVER_ACCEPTOR_H_
#define MUS_HTTPSERVER_ACCEPTOR_H_

#include <memory>  // std::shared_ptr

namespace music_share {
namespace http_server {

class Router;

class Acceptor {
public:
    Acceptor(std::shared_ptr<Router>& router);
    ~Acceptor() = default;

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    void Run();
private:
    void accept();
    void on_accept();

    std::shared_ptr<Router> m_router;
};

}  // namespace http_server
}  // namespace music_share

#endif  // MUS_HTTPSERVER_ACCEPTOR_H_
