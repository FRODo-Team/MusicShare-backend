// Oweners: Faris Nabiev, WEB-12
#include "http/server/router/router.h"

#include <vector>  // std::vector

#include "http/server/router/routetrie.h"  // music_share::http::server::router::RouteTrie
#include "http/server/router/routenode.h"  // music_share::http::server::router::RouteNode
#include "http/server/middleware.h"  // all
#include "http/common/request.h"  // music_share::http::common::Request
#include "util.h"  // music_share::util::split

namespace music_share::http::server::router {

Router::Router()
    : m_trie(std::make_unique<RouteTrie>()) {
}

std::pair<RequestHandler, std::map<std::string, std::string>>
Router::RouteTo(const common::Request& request) {
    auto path = request.target().to_string();

    auto [handler, params] = m_trie->Match(path.substr(0, path.find('?')),
                                           request.method_string().to_string());

    for (auto it = m_middleware_builders.rbegin();
         it != m_middleware_builders.rend(); ++it) {
        handler = (*it)->Build(handler);
    }

    return {handler, params};
}

void Router::Require(std::shared_ptr<middleware::IMiddlewareBuilder> mw_builder) {
    m_middleware_builders.push_back(mw_builder);
}

void Router::addRoute(const Route& route, std::string method) {
    m_trie->AddRoute(route, method);
}

void Router::GET(const Route& route) {
    addRoute(route, "GET");
}
void Router::PUT(const Route& route) {
    addRoute(route, "PUT");
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

}  // namespace music_share::http::server::router
