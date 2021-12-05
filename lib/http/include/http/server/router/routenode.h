#ifndef MUS_HTTP_ROUTENODE_H_
#define MUS_HTTP_ROUTENODE_H_

#include <set>  // std::set
#include <map>  // std::map
#include <regex>  // std::regex
#include <string>  // std::string
#include <optional>  // std::optional
#include <functional>  // std::less

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler

namespace music_share {
namespace http {
namespace server {
namespace router {

struct RouteNode final {
    RouteNode(const std::string name,
              std::optional<std::string> pattern = std::nullopt);
    ~RouteNode();

    RouteNode(const RouteNode&) = default;
    RouteNode& operator=(const RouteNode&) = default;
    RouteNode(RouteNode&&) = default;
    RouteNode& operator=(RouteNode&&) = default;

    std::string name;
    std::optional<std::string> pattern;
    std::map<std::string, RequestHandler> mutable handlers;
    std::set<RouteNode, std::less<>> mutable children;

    friend int operator<=>(const RouteNode& a, const RouteNode& b);
};

}  // namespace router
}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_ROUTENODE_H_
