#include "http/server/server.h"

#include <ranges>  // std::views::iota
#include <thread>  // std::thread

#include "http/server/acceptor.h"
#include "http/server/router/router.h"

namespace music_share {
namespace http {
namespace server {

Server::Server(const std::string& address, const std::string& portnum)
    : Server(address, portnum, std::thread::hardware_concurrency()) {}

Server::Server(const std::string& address, const std::string& portnum,
               size_t workers_qty)
    : m_workers_qty(workers_qty),
      m_router(std::make_shared<router::Router>()),
      m_acceptor(std::make_shared<Acceptor>(m_io,
                                            address,
                                            portnum,
                                            m_router)) {}

void Server::Run() {
    m_acceptor->Run();

    std::vector<std::shared_ptr<std::thread>> workers;
    for (size_t i = 0; i < m_workers_qty; ++i) {
        auto worker =
            std::make_shared<std::thread>([this]() { m_io.run(); });
        workers.push_back(worker);
    }

    for (auto& worker: workers) {
        worker->join();
    }
}

router::Router& Server::Router() {
    return *m_router;
}

void Server::on_stop() {
    m_io.stop();
}

}  // namespace server
}  // namespace http
}  // namespace music_share
