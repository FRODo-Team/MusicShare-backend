#include "mus-usecase/auth_use_case.h"

namespace music_share {

    AuthUseCase::AuthUseCase(IAuthRepository& auth_rep)
                            : m_auth_rep(auth_rep) { }

    AuthUseCase::AuthUseCase(const AuthUseCase& auth_use_case)
                            : m_auth_rep(auth_use_case.m_auth_rep) { }

    AuthUseCase& AuthUseCase::operator=(const AuthUseCase& auth_use_case) {
        m_auth_rep = auth_use_case.m_auth_rep;
        return *this;
    }

    bool AuthUseCase::Authorization(const UserRequestDTO& user) {
        return true;
    }

    bool AuthUseCase::Authentication(const UserRequestDTO& user) {
        return true;
    }

}  // namespace music_share
