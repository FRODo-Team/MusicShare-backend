#include "http-server/acceptor.h"

namespace music_share {

Acceptor::Acceptor(std::shared_ptr<Router>& router) : m_router(router) {}

void Acceptor::Run() {
}

void Acceptor::accept() {
}

void Acceptor::on_accept() {
}

}  // namespace music_share
