#ifndef MUS_INTERNAL_MUS_USECASE_AUTH_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_AUTH_USE_CASE_H_

#include "mus-iusecase/iauth_use_case.h"
#include "mus-irepo/isession_repository.h"
#include "mus-irepo/iuser_repository.h"

namespace music_share {

class AuthUseCase : public IAuthUseCase {
public:
    AuthUseCase(ISessionRepository& session_repository,
                IUserRepository& user_repository)
                :
                m_session_repository(session_repository),
                m_user_repository(user_repository) { }

    ~AuthUseCase() override = default;

    std::optional<SessionData> Authenticate(
            const std::string& username,
            const std::string& password) override;

    std::optional<uint32_t> ValidateSessionKey(
            const std::string& session_key) override;

private:
    static std::string GenerateSessionKey();
    static std::string HashPassword(const std::string& plain_password);

    ISessionRepository& m_session_repository;
    IUserRepository& m_user_repository;
};

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_AUTH_USE_CASE_H_
