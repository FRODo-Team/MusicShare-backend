#ifndef MUS_HTTPSERVER_CONNECTION_H_
#define MUS_HTTPSERVER_CONNECTION_H_

#include <memory>  // std::shared_ptr

namespace music_share {
namespace http_server {

class Router;

class Connection {
public:
    Connection(std::shared_ptr<Router>& router);
    ~Connection() = default;

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    void Start();
private:
    void read();
    void on_read();
    void write();
    void on_write();

    std::shared_ptr<Router> m_router;
};


}  // namespace http_server
}  // namespace music_share

#endif  // MUS_HTTPSERVER_CONNECTION_H_
