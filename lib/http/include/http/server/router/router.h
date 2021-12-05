#ifndef MUS_HTTP_ROUTER_H_
#define MUS_HTTP_ROUTER_H_

#include <string>  // std::string

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler

namespace music_share {
namespace http {
namespace server {
namespace router {

class Route;
class RouteTrie;

class Router {
public:
    Router() = default;
    ~Router() = default;

    RequestHandler RouteTo(const std::string& path);
    void Register(Route&& route);
private:

};

}  // namespace router
}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_ROUTER_H_
