#include "http/server/server.h"

#include "http/server/acceptor.h"

namespace music_share {
namespace http {
namespace server {

Server::Server(const std::string& portnum)
    : Server(portnum, std::thread::hardware_concurrency()) {}

Server::Server(const std::string& portnum, size_t workers_qty)
    : m_portnum(portnum),
      m_workers_qty(workers_qty) {}

void Server::Run() {
}

void Server::on_stop() {
}

}  // namespace server
}  // namespace http
}  // namespace music_share
