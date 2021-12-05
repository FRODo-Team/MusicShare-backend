#include "http/server/router/router.h"

#include <vector>  // std::vector

#include "http/server/router/routetrie.h"  // music_share::http::server::router::RouteTrie
#include "http/common/request.h"  // music_share::http::common::Request
#include "util.h"  // music_share::util::split

namespace music_share {
namespace http {
namespace server {
namespace router {

Router::Router()
    : m_trie(std::make_unique<RouteTrie>()) {
}

std::pair<RequestHandler, std::map<std::string, std::string>>
Router::RouteTo(const common::Request& request) {
    std::vector<std::string> path_fragmets = util::split(request.Path(), "/");

    return m_trie->Match(path_fragmets, request.Method());
}

void Router::addRoute(const Route& route, std::string method) {
    m_trie->AddRoute(route, method);
}

void Router::GET(const Route& route) {
    addRoute(route, "GET");
}
void Router::POST(const Route& route) {
    addRoute(route, "POST");
}
void Router::PATCH(const Route& route) {
    addRoute(route, "PATCH");
}
void Router::DELETE(const Route& route) {
    addRoute(route, "DELETE");
}

}  // namespace router
}  // namespace server
}  // namespace http
}  // namespace music_share
