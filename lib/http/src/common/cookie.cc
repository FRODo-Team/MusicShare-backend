#include "http/common/cookie.h"

#include <sstream>

#include "http/common/header.h"
#include "util.h"

namespace music_share::http::common {

std::map<std::string, std::string> GetCookies(const Request& request) {
    std::map<std::string, std::string> cookies;

    std::size_t delim_pos = std::string::npos;
    for (const auto& cookie: util::split(request["Cookie"].to_string(), "; ")) {
        delim_pos = cookie.find('=');
        cookies.emplace(cookie.substr(0, delim_pos),
                        cookie.substr(delim_pos + 1, std::string::npos));
    }

    return cookies;
}

void SetCookie(Response& response, std::string_view key, std::string_view val) {
    std::stringstream cookie_bilder;
    cookie_bilder << key << "=" << val;
    response.set(header::set_cookie, cookie_bilder.str());
}

}  // namespace music_share::http::common
