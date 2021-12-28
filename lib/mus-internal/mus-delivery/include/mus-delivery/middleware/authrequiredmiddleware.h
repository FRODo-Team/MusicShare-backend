// Owners: Faris Nabiev, WEB-12
#ifndef MUS_MUSINTERNAL_MUSDELIVERY_MIDDLEWARE_AUTHREQUIRED_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_MIDDLEWARE_AUTHREQUIRED_H_

#include "http/common.h"
#include "http/server/requesthandler.h"
#include "http/server/middleware/middleware.h"
#include "mus-iusecase/iauth_use_case.h"

namespace music_share::middleware {

class AuthRequiredMiddleware: public http::server::middleware::IMiddleware {
public:
    AuthRequiredMiddleware(http::server::RequestHandler handler,
                           IAuthUseCase& auth);
    ~AuthRequiredMiddleware() = default;
    http::common::Response operator()(const http::common::Request& request,
                                const http::server::Parameters& params);
private:
    IAuthUseCase& m_auth;
};

class AuthRequiredMiddlewareBuilder
    : public http::server::middleware::IMiddlewareBuilder {
public:
    AuthRequiredMiddlewareBuilder(IAuthUseCase& auth)
        : m_auth(auth) {}
    ~AuthRequiredMiddlewareBuilder() = default;

    http::server::RequestHandler Build(http::server::RequestHandler inner_handler) const {
        return AuthRequiredMiddleware(inner_handler, m_auth);
    }

    static std::shared_ptr<AuthRequiredMiddlewareBuilder>
    Create(IAuthUseCase& auth) {
        return std::make_shared<AuthRequiredMiddlewareBuilder>(auth);
    }

private:
    IAuthUseCase& m_auth;
};


} // namespace music_share::middleware


#endif  // MUS_MUSINTERNAL_MUSDELIVERY_MIDDLEWARE_AUTHREQUIRED_H_
