#ifndef MUS_HTTPSERVER_ROUTER_H_
#define MUS_HTTPSERVER_ROUTER_H_

#include "http-server/requesthandler.h"

namespace music_share {

class Route;

class Router {
public:
    Router() = default;
    ~Router() = default;

    RequestHandler RouteTo(const std::string& path);
    void Register(Route&& route);
private:
};

}  // namespace music_share

#endif  // MUS_HTTPSERVER_ROUTER_H_
