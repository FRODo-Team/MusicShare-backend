// Oweners: Faris Nabiev, WEB-12
#include "http/server/router/routenode.h"

#include <regex> //  std::regex
#include <cstring> //  strcmp

namespace music_share::http::server::router {

RouteNode::RouteNode(const std::string name,
        std::optional<std::string> pattern)
    : name(name),
      pattern(pattern) {}

int operator<=>(const RouteNode& a, const RouteNode& b) {
    int diff = a.pattern.has_value() - b.pattern.has_value();

    if (diff == 0) {
        std::string a_name = a.pattern ? a.name + a.pattern.value() : a.name;
        std::string b_name = b.pattern ? b.name + b.pattern.value() : b.name;
        diff = strcmp(a_name.c_str(), b_name.c_str());
    }

    return diff;
}

bool operator==(const RouteNode& a, const RouteNode& b) {
    return std::tie(a.name, a.pattern) == std::tie(b.name, b.pattern);
}   

}  // namespace music_share::http::server::router
