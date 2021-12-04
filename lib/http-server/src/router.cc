#include "http-server/router.h"

namespace music_share {
namespace http_server {

RequestHandler Router::RouteTo(const std::string&) {
    return RequestHandler();
}

void Router::Register(Route&&) {
}

}  // namespace http_server
}  // namespace music_share
