#ifndef MUS_HTTP_ROUTER_H_
#define MUS_HTTP_ROUTER_H_

#include <map>  // std::map
#include <string>  // std::string
#include <memory>  // std::unique_ptr
#include <algorithm>  // std::pair

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler

namespace music_share {
namespace http {

namespace common {

class Request;  // namespace common

}  // namespace common

namespace server {
namespace router {

class Route;
class RouteTrie;

class Router {
public:
    Router();
    ~Router() = default;

    std::pair<RequestHandler, std::map<std::string, std::string>>
    RouteTo(const common::Request& request);

    void GET(const Route& route);
    void POST(const Route& route);
    void PATCH(const Route& route);
    void DELETE(const Route& route);

private:
    void addRoute(const Route& route, std::string method);

    std::unique_ptr<RouteTrie> m_trie;
};

}  // namespace router
}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_ROUTER_H_
