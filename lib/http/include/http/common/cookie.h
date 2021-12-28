// Owners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_COMMON_COOKIE_H_
#define MUS_HTTP_COMMON_COOKIE_H_

#include <map>
#include <string>
#include <string_view>

#include "http/common/request.h"
#include "http/common/response.h"

namespace music_share::http::common {

std::map<std::string, std::string> GetCookies(const Request& request);

void SetCookie(Response& response, std::string_view key, std::string_view val);

}  // namespace music_share::http::common

#endif  // MUS_HTTP_COMMON_COOKIE_H_
