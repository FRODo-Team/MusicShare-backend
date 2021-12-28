// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_SERVER_REQUESTHANDLER_H_
#define MUS_HTTP_SERVER_REQUESTHANDLER_H_

#include <map>  // std::map
#include <string>  // std::string
#include <functional>  // std::function

#include "http/common/request.h"
#include "http/common/response.h"

namespace music_share {
namespace http {

namespace server {

using Parameters = std::map<std::string, std::string>;

using RequestHandler =
    std::function<common::Response(const common::Request&,
                                   const Parameters&)>;

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_REQUESTHANDLER_H_
