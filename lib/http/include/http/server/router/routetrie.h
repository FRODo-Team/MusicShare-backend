// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_ROUTETRIE_H_
#define MUS_HTTP_ROUTETRIE_H_

#include <map>  // std::map
#include <string>  // std::string
#include <vector>  // std::vector
#include <memory>  // std::unique_ptr
#include <algorithm>  // std::pair
#include <exception>  // std::exception

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler
#include "http/server/router/routenode.h"

namespace music_share::http::server::router {

class Route;
struct RouteNode;

class RouteTrie {
public:
    class ExistingHTTPMethodException: public std::exception {
    public:
        ExistingHTTPMethodException(const std::string& method,
                                    const std::string& path)
            : m_message("Method '" + method +
                        "' is already declared for path: " + path) {}

        const char* what() const noexcept {
            return m_message.c_str();
        }
    private:
        std::string m_message;
    };

    class NotExistingHandler: public std::exception {
    public:
        NotExistingHandler(const std::string& method)
            : m_message("Can't find handler for method '" + method + "'") {}

        const char* what() const noexcept {
            return m_message.c_str();
        }
    private:
        std::string m_message;
    };

    RouteTrie();

    void AddRoute(const Route& route, const std::string method);
    std::pair<RequestHandler, std::map<std::string, std::string>>
    Match(const std::string& path, const std::string method);
private:
    std::unique_ptr<RouteNode> m_root;
};

}  // namespace music_share::http::server::router

#endif  // MUS_HTTP_ROUTETRIE_H_
