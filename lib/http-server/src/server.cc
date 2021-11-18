#include "http-server/server.h"

namespace music_share {

Server::Server(const std::string& portnum)
    : Server(portnum, std::thread::hardware_concurrency()) {}

Server::Server(const std::string& portnum, size_t workers_qty)
    : m_portnum(portnum),
      m_workers_qty(workers_qty) {}

void Server::Run() {
}

void Server::on_stop() {
}

}  // namespace music_share
