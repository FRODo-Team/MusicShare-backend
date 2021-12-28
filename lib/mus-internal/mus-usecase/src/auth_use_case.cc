// Oweners: Darya Vlaskina, ML-13
#include "mus-usecase/auth_use_case.h"
#include "mus-utility/random.h"
#include "mus-utility/crypto.h"


namespace music_share {

std::optional<IAuthUseCase::SessionData> AuthUseCase::Authenticate(
        const AuthRequestDTO& auth_dto)
{
    std::optional<User> user = m_user_repository.FindByUsername(auth_dto.username);
    if (!user) {
        return { };
    }

    const std::string hashed_password =
            utility::Crypto::HashAndSalt(auth_dto.password);

    if (hashed_password != user->GetPasswordHash()) {
        return { };
    }

    const std::string session_key =
            utility::Random::GenerateString(Session::SessionKeyLength);

    // TODO: Сгенерировать нормальную дату
    const std::string datetime_expires = "2022-01-30 19:30:00";
    Session session(*user->GetId(), session_key, datetime_expires);

    m_session_repository.Insert(session);

    // TODO: Сконвертировать дату для cookie
    SessionData result {
        *user->GetId(),
        session.GetSessionKey(),
        "Sun, 30 Jan 2012 00:00:01 GMT"
    };

    return result;
}

std::optional<uint32_t> AuthUseCase::ValidateSessionKey(
        const std::string& session_key)
{
    std::optional<Session> session =
            m_session_repository.FindBySessionKey(session_key);
    if (!session) {
        return { };
    }

    // TODO: проверить дату окончания сессии
    return session->GetUserId();
}

}  // namespace music_share
