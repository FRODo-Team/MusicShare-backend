#ifndef MUS_HTTP_SERVER_ACCEPTOR_H_
#define MUS_HTTP_SERVER_ACCEPTOR_H_

#include <memory>  // std::shared_ptr

namespace music_share {
namespace http {
namespace server {

namespace router {
class Router;
}  // namespace router

class Acceptor {
public:
    Acceptor(std::shared_ptr<router::Router>& router);
    ~Acceptor() = default;

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    void Run();
private:
    void accept();
    void on_accept();

    std::shared_ptr<router::Router> m_router;
};

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_ACCEPTOR_H_
