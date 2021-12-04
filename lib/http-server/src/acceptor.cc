#include "http-server/acceptor.h"

namespace music_share {
namespace http_server {

Acceptor::Acceptor(std::shared_ptr<Router>& router) : m_router(router) {}

void Acceptor::Run() {
}

void Acceptor::accept() {
}

void Acceptor::on_accept() {
}

}  // namespace http_server
}  // namespace music_share
