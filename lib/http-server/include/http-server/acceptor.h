#ifndef MUS_HTTPSERVER_ACCEPTOR_H_
#define MUS_HTTPSERVER_ACCEPTOR_H_

#include <memory>  // std::shared_ptr

namespace music_share {

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

}  // namespace music_share

#endif  // MUS_HTTPSERVER_ACCEPTOR_H_
