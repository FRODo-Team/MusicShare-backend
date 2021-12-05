#include "http/server/acceptor.h"

namespace music_share {
namespace http {
namespace server {

Acceptor::Acceptor(std::shared_ptr<router::Router>& router)
    : m_router(router) {}

void Acceptor::Run() {
}

void Acceptor::accept() {
}

void Acceptor::on_accept() {
}

}  // namespace server
}  // namespace http
}  // namespace music_share
