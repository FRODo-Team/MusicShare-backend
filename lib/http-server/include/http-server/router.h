#ifndef MUS_HTTPSERVER_ROUTER_H_
#define MUS_HTTPSERVER_ROUTER_H_

#include <string>  // std::string

#include "http-server/requesthandler.h"

namespace music_share {
namespace http_server {

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

}  // namespace http_server
}  // namespace music_share

#endif  // MUS_HTTPSERVER_ROUTER_H_
