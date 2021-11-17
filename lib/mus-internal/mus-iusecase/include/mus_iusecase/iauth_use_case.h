#ifndef MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_

#include "mus-dto/user_request_dto.h"

class IAuthUseCase {
public:
    IAuthUseCase() = default;

    IAuthUseCase(const IAuthUseCase& auth_use_case) = default;

    IChatUseCase& operator=(const IAuthUseCase& auth_use_case) = default;

    virtual bool Authorization(UserRequestDTO& user) = 0;

    virtual bool Authentication(UserRequestDTO& user) = 0;

    virtual ~IAuthUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_
