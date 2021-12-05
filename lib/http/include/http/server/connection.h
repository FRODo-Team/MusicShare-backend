#ifndef MUS_HTTP_SERVER_CONNECTION_H_
#define MUS_HTTP_SERVER_CONNECTION_H_

#include <memory>  // std::shared_ptr

namespace music_share {
namespace http {
namespace server {

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


}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_CONNECTION_H_
