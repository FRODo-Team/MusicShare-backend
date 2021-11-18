#include "http-server/router.h"

namespace music_share {

RequestHandler Router::RouteTo(const std::string&) {
    return RequestHandler();
}

void Router::Register(Route&&) {
}

}  // namespace music_share
