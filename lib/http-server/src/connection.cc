#include "http-server/connection.h"

namespace music_share {

Connection::Connection(std::shared_ptr<Router>& router) : m_router(router) {}

void Connection::Start() {
}

void Connection::read() {
}

void Connection::on_read() {
}

void Connection::write() {
}

void Connection::on_write() {
}

}  // namespace music_share