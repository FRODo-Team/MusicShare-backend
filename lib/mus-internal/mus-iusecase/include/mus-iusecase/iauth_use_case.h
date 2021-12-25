#ifndef MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_

#include <optional>
#include <utility>
#include "mus-dto/user_request_dto.h"

namespace music_share {

class IAuthUseCase {
public:
    struct SessionData {
        uint32_t user_id;
        std::string session_key;
        std::string session_expires;
    };

    virtual
    std::optional<SessionData> Authenticate(
            const std::string& username,
            const std::string& password) = 0;

    // Возвращает идентификатор пользователя, если сессионный ключ валиден
    virtual
    std::optional<uint32_t> ValidateSessionKey(
            const std::string& session_key) = 0;

    virtual ~IAuthUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_IAUTH_USE_CASE_H_
