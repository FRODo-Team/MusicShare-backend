#include "http/server/router/routenode.h"

#include <regex> //  std::regex
#include <cstring> //  strcmp

namespace music_share {
namespace http {
namespace server {
namespace router {

RouteNode::RouteNode(const std::string name,
        std::optional<std::string> pattern)
    : name(name),
      pattern(pattern) {}

int operator<=>(const RouteNode& a, const RouteNode& b) {
    int diff = a.pattern.has_value() - b.pattern.has_value();

    if (diff == 0) {
        diff = strcmp(a.name.c_str(), b.name.c_str());
    }

    return diff;
}

}  // namespace router
}  // namespace server
}  // namespace http
}  // namespace music_share
