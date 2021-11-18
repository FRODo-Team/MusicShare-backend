#ifndef MUS_INTERNAL_MUS_USECASE_AUTH_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_AUTH_USE_CASE_H_

#include "iauth_use_case.h"
#include "iauth_repository.h"

class AuthUseCase : IAuthUseCase {
public:
    AuthUseCase() = delete;

    AuthUseCase(IAuthRepository& auth_rep);

    AuthUseCase(const AuthUseCase& auth_use_case);

    AuthUseCase& operator=(const AuthUseCase& auth_use_case);

    bool Authorization(UserRequestDTO user) override;

    bool Authentication(UserRequestDTO user) override;

    ~AuthUseCase();

private:
    IAuthRepository& m_auth_rep;
};

#endif  // MUS_INTERNAL_MUS_USECASE_AUTH_USE_CASE_H_