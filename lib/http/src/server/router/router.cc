#include "http/server/router/router.h"

namespace music_share {
namespace http {
namespace server {
namespace router {

RequestHandler Router::RouteTo(const std::string&) {
    return RequestHandler();
}

void Router::Register(Route&&) {
}

}  // namespace router
}  // namespace server
}  // namespace http
}  // namespace music_share
