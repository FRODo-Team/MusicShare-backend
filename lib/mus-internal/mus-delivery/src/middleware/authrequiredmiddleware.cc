#include "mus-delivery/middleware/authrequiredmiddleware.h"


namespace music_share::middleware {

AuthRequiredMiddleware::AuthRequiredMiddleware(
        http::server::RequestHandler handler,
        IAuthUseCase& auth)
    : http::server::middleware::IMiddleware(handler)
    , m_auth(auth) {}

http::common::Response
AuthRequiredMiddleware::operator()(const http::common::Request& request,
                                   const http::server::Parameters& params) {
    auto cookies = http::common::GetCookies(request);
    auto session_key_it = cookies.find("token");

    std::optional<uint32_t> user_id = std::nullopt;
    if (session_key_it != cookies.end()) {
        user_id = m_auth.ValidateSessionKey(session_key_it->second);
    }

    if (!user_id.has_value()) {
        http::common::Response response;
        response.result(http::common::status::forbidden);
        return response;
    }

    auto new_params = params;
    new_params["user_id"] = std::to_string(user_id.value());

    return get_response(request, new_params);
}

} // namespace music_share::middleware
