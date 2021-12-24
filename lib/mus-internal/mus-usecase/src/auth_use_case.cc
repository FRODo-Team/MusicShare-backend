#include "mus-usecase/auth_use_case.h"
#include "mus-utility/random.h"
#include "mus-utility/crypto.h"


namespace music_share {

std::optional<IAuthUseCase::SessionData> AuthUseCase::Authenticate(
        const std::string& username,
        const std::string& password)
{
    std::optional<User> user = m_user_repository.FindByUsername(username);
    if (!user) {
        return { };
    }

    const std::string hashed_password = HashPassword(password);
    if (hashed_password != user->GetPasswordHash()) {
        return { };
    }

    const std::string session_key = GenerateSessionKey();

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

std::string AuthUseCase::GenerateSessionKey() {
    return utility::Random::GenerateString(Session::SessionKeyLength);
}

std::string AuthUseCase::HashPassword(const std::string& plain_password) {
    std::string salted_password = plain_password + "DefinitelyNotSalt";
    return utility::Crypto::HashString_SHA256(salted_password);
}

}  // namespace music_share
