#ifndef MUS_HTTPSERVER_ROUTE_H_
#define MUS_HTTPSERVER_ROUTE_H_

#include <string>  // std::string
#include <vector>  // std::vector
#include <memory>  // std::shared_ptr
#include <initializer_list>  // std::initializer_list

#include "http-server/requesthandler.h"

namespace music_share {

class IMiddlewareBuilder;

class Route {
public:
    Route(const std::string& path, RequestHandler handler,
          std::initializer_list<std::shared_ptr<IMiddlewareBuilder>>
          middleware_builders);
    ~Route() = default;

    std::string GetPath() const;
    RequestHandler GetHandler();
private:
    std::string m_path;
    RequestHandler m_handler;
    std::vector<std::shared_ptr<IMiddlewareBuilder>> m_middleware_builders;
};

}  // namespace music_share

#endif  // MUS_HTTPSERVER_ROUTE_H_
