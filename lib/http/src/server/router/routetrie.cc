// Oweners: Faris Nabiev, WEB-12
#include "http/server/router/routetrie.h"

#include <regex>  // std::regex_match
#include <stack>  // std::stack
#include <ranges>  // std::ranges::move
#include <cstring>  // strcmp
#include <cassert>  // assert
#include <iterator>  // std::inserter
#include <algorithm>  // std::pair

#include "http/server/router/route.h"
#include "http/server/router/routenode.h"
#include "http/server/exception/notfound.h"
#include "http/server/exception/methodnotallowed.h"
#include "util.h"

namespace {

struct NotParametricKey {
    std::string name;
};

int operator<=>(const music_share::http::server::router::RouteNode& a,
                const NotParametricKey& b) {
    if (a.pattern) {
        return 1;
    }
    return strcmp(a.name.c_str(), b.name.c_str());
}

int operator<=>(const NotParametricKey& a,
                const music_share::http::server::router::RouteNode& b) {
    if (b.pattern) {
        return -1;
    }
    return strcmp(a.name.c_str(), b.name.c_str());
}

struct ParametricKey {
    std::string name;
    std::string pattern;
};

int operator<=>(const music_share::http::server::router::RouteNode& a,
                const ParametricKey& b) {
    if (!a.pattern) {
        return -1;
    }
    return strcmp((a.name + a.pattern.value()).c_str(),
                  (b.name + b.pattern).c_str());
}

int operator<=>(const ParametricKey& a,
                const music_share::http::server::router::RouteNode& b) {
    if (!b.pattern) {
        return 1;
    }
    return strcmp((a.name + a.pattern).c_str(),
                  (b.name + b.pattern.value()).c_str());
}

}

namespace music_share::http::server::router {

using RouteNodeHolder = std::reference_wrapper<const RouteNode>;

RouteTrie::RouteTrie() : m_root(std::make_unique<RouteNode>("")) {}

void RouteTrie::AddRoute(const Route& route, const std::string method) {
    auto& nodes = route.GetPathNodes();
    size_t nodes_qty = nodes.size();

    RouteNodeHolder current = *m_root;
    for (size_t idx = 0; idx < nodes_qty; ++ idx) {
        // skip empty path node (example: /some/path///to/ == /some/path/to)
        if (nodes[idx].name == "") {
            continue;
        }

        auto& children = current.get().children;
        auto next_it = children.end();

        // if no children, skip find and go to creation of new route node
        if (children.size() > 0) {
            // if searching route node is parametric,
            // find among parametric nodes
            if (nodes[idx].pattern) {
                next_it = children.find(ParametricKey{nodes[idx].name,
                                                      nodes[idx].pattern
                                                        .value()});
            } else {
                next_it = children.find(NotParametricKey{nodes[idx].name});
            }
        }

        // if search has been unsuccess, create new route node
        if (next_it == children.end()) {
            std::tie(next_it, std::ignore) = 
                children.emplace(nodes[idx].name, nodes[idx].pattern);
        }

        current = *next_it;
    }

    auto& handlers = current.get().handlers;
    auto hint = handlers.lower_bound(method);
    if (hint != handlers.end() && hint->first == method) {
        throw ExistingHTTPMethodException(method, route.GetPath());
    }
    handlers.emplace_hint(hint, method, route.GetHandler());
}

std::pair<RequestHandler, std::map<std::string, std::string>>
RouteTrie::Match(const std::string& path, const std::string method) {
    assert(path.size() > 0 && path[0] == '/' &&
           "Path is required to be absolute");
    auto path_frags = util::split(path.c_str() + 1, "/");

    std::map<std::string, RequestHandler>::iterator handler_it;
    // route node, where we shall search handler
    // for specified path and method
    RouteNodeHolder last_visited = *m_root;
    // future dictionary of path parameters (example 'id' in /libraries/:id([0-9]+))
    std::vector<std::pair<std::string, std::string>> path_parameters;
    // route node, in which children we are searching path_frag[idx]
    // idx
    // size of path_parameters
    // (we have to erase parse paremeters of rejected nodes)
    std::stack<std::tuple<RouteNodeHolder, size_t, size_t>> to_visit;
    to_visit.push({*m_root, 0, 0});

    bool is_found = false;
    size_t path_frags_qty = path_frags.size();
    while (!to_visit.empty()) {
        auto [current, idx, param_qty] = to_visit.top();
        to_visit.pop();

        // erase path parameters of regected path
        // example:
        // if '/path/to/:a{.*}/smth' has been rejected
        // and next val in stack correspond to '/path/to/:id{[0-9]+}/smb'
        // we have to erase parameter 'a' from path_parameters
        while (param_qty < path_parameters.size()) {
            path_parameters.pop_back();
        }

        if (current.get().pattern) {
            // push current path parameter
            assert(idx > 0 && "root route node is forbidden to be parametric");
            path_parameters.emplace_back(current.get().name, path_frags[idx - 1]);
        }

        // if idx out of range path_frags, we achieved
        // searching node on previous step
        if (idx >= path_frags_qty) {
            last_visited = current;
            is_found = true;

            auto& handlers = last_visited.get().handlers;
            handler_it = handlers.find(method);
            if (handler_it == handlers.end()) {
                continue;
            }

            break;
        }

        // skip empty path fragment
        // (example: /some/path///to/ == /some/path/to)
        if (path_frags[idx] == "") {
            to_visit.push({current, idx + 1, param_qty});
            continue;
        }

        // push to 'to_visit' all parametric route nodes
        // which pattern matches current path_frag
        auto& children = current.get().children;
        for (auto it = children.rbegin();
             it != children.rend() && it->pattern;
             ++it) {
            std::regex re = std::regex(it->pattern.value());
            if (std::regex_match(path_frags[idx], re)) {
                to_visit.push({*it, idx + 1, path_parameters.size()});
            }
        }

        // try to find matching non-parametric route node
        // this kind of nodes have the highest priority,
        // that's why we put it on the top of stack
        auto it = children.find(NotParametricKey{path_frags[idx]});
        if (it != children.end()) {
            to_visit.push({*it, idx + 1, path_parameters.size()});
        }

        last_visited = current;
    }

    if (!is_found) {
        return {[path](auto, auto) -> common::Response {
            throw exception::NotFound(path);
        }, Parameters()};
    }

    auto& handlers = last_visited.get().handlers;
    if (handler_it == handlers.end()) {
        return {[method, path](auto, auto) -> common::Response {
            throw exception::MethodNotAllowed(method, path);
        }, Parameters()};
    }

    // move path parameters from vector to map
    // for more convenient usage
    std::map<std::string, std::string> path_params;
    std::ranges::move(path_parameters,
                      std::inserter(path_params, path_params.end()));

    return {handler_it->second, path_params};
}

}  // namespace music_share::htttp::server::router
