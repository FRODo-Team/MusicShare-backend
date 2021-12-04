#include "http-server/routenode.h"

#include <regex> //  std::regex
#include <cstring> //  strcmp

namespace music_share {
namespace http_server {

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

}  // namespace http_server
}  // namespace music_share
