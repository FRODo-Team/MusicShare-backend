// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_

#include "mus-dto/user_request_dto.h"

namespace music_share {

class IAuthUseCase {
public:
    IAuthUseCase() = default;

    IAuthUseCase(const IAuthUseCase& auth_use_case) = default;

    IAuthUseCase& operator=(const IAuthUseCase& auth_use_case) = default;

    virtual bool Authorization(const UserRequestDTO& user) = 0;

    virtual bool Authentication(const UserRequestDTO& user) = 0;

    virtual ~IAuthUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_
