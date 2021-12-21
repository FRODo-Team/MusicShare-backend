// Oweners: Faris Nabiev, WEB-12
#include "http/server/router/route.h"

#include <cstring>

#include "http/server/router/routenode.h"
#include "http/server/middleware/middleware.h"
#include "util.h"

namespace {

const char* PATH_NODE_RE = "[\\w\\-_.~]*";
const char* PATH_PARAM_RE = ":([a-zA-Z_]+[\\w_]*)\\((.*)\\)";

}

namespace music_share::http::server::router {

std::optional<Route::PathNode>
Route::PathNode::fromString(const std::string& node) {
    // not parametric node
    if (node.size() == 0 || (node.size() > 0 && node[0] != ':')) {
        if (std::regex_match(node, std::regex(PATH_NODE_RE))) {
            return PathNode{node, std::nullopt};
        }
    }
    // parametric node
    std::smatch matches;
    if (!std::regex_match(node, matches, std::regex(PATH_PARAM_RE))) {
        return std::nullopt;
    }

    // check if regex of parametric node is valid
    try {
        std::string param_name = matches[1].str();
        std::string param_pattern = matches[2].str();
        std::regex param_re = std::regex(param_pattern);

        return PathNode{param_name, param_pattern};
    } catch (const std::regex_error&) {
        return std::nullopt;
    }
}

Route::Route(const std::string& path, RequestHandler handler,
             std::initializer_list<
                std::shared_ptr<middleware::IMiddlewareBuilder>>
                middleware_builders)
    : m_path(path),
      m_handler(handler),
      m_middleware_builders(middleware_builders) {
    if (m_path.size() < 1 || m_path[0] != '/') {
        throw PathValidationException("Absolute path has been expected "
                                      "(missing '/' at the begin of path)");
    }

    for (const auto& node: util::split(m_path.c_str() + 1, "/")) {
        auto path_node = PathNode::fromString(node);
        if (!path_node) {
            throw PathValidationException("Invalid path: " + m_path +
                                          ". Can't parse node: " + node);
        }
        m_path_nodes.push_back(path_node.value());
    }
}

std::string Route::GetPath() const {
    return m_path;
}

RequestHandler Route::GetHandler() const {
    RequestHandler handler = m_handler;

    for (auto it = m_middleware_builders.rbegin();
         it != m_middleware_builders.rend(); ++it) {
        handler = (*it)->Build(handler);
    }

    return handler;
}

const std::vector<Route::PathNode>& Route::GetPathNodes() const {
    return m_path_nodes;
}

}  // namespace music_share::http::server::router
