// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_ROUTE_H_
#define MUS_HTTP_ROUTE_H_

#include <regex>  // std::regex
#include <string>  // std::string
#include <vector>  // std::vector
#include <memory>  // std::unique_ptr
#include <optional>  // std::optional
#include <initializer_list>  // std::initializer_list

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler

namespace music_share::http::server::middleware {

class IMiddlewareBuilder;

}  // namespace music_share::http::server::middleware

namespace music_share::http::server::router {

class Route {
public:
    struct PathNode {
        std::string name;
        std::optional<std::string> pattern;

        static std::optional<PathNode> fromString(const std::string& node);
    };

    class PathValidationException: public std::exception {
    public:
        PathValidationException(const std::string& message)
            : m_message(message) {}

        const char* what() const noexcept {
            return m_message.c_str();
        }
    private:
        std::string m_message;
    };

    Route(const std::string& path, RequestHandler handler,
          std::initializer_list<std::shared_ptr<middleware::IMiddlewareBuilder>>
          middleware_builders = {});
    ~Route() = default;

    std::string GetPath() const;
    RequestHandler GetHandler() const;
    const std::vector<PathNode>& GetPathNodes() const;
private:
    std::string m_path;
    RequestHandler m_handler;
    std::vector<PathNode> m_path_nodes;
    std::vector<std::shared_ptr<middleware::IMiddlewareBuilder>>
    m_middleware_builders;
};

}  // namespace music_share::http::server::router

#endif  // MUS_HTTP_ROUTE_H_
