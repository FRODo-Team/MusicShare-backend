#include "mus-models/user.h"

namespace music_share {

User::User(const std::string& username,
           const std::string& email,
           const std::string& password_hash,
           const std::string& nickname,
           AccessLevel access_level,
           std::optional<uint32_t> id)
        :
        m_username(username),
        m_email(email),
        m_password_hash(password_hash),
        m_nickname(nickname),
        m_access_level(access_level),
        m_id(id) { }

User::User(const User& other, uint32_t id)
        :
        m_username(other.GetUsername()),
        m_email(other.GetEmail()),
        m_password_hash(other.GetPasswordHash()),
        m_nickname(other.GetNickname()),
        m_access_level(other.GetAccessLevel()),
        m_id(id) { }

void User::SetNickname(const std::string& nickname) {
    if (!nickname.empty() && nickname.size() <= kNicknameMaxLength) {
        m_nickname = nickname;
    }
}

void User::SetEmail(const std::string& email) {
    if (!email.empty() && email.size() <= kEmailMaxLength) {
        m_email = email;
    }
}

void User::SetUsername(const std::string& username) {
    if (!username.empty() && username.size() <= kUsernameMaxLength) {
        m_username = username;
    }
}

void User::SetPasswordHash(const std::string& password_hash) {
    if (!password_hash.empty() &&
         password_hash.size() <= kPasswordHashMaxLength) {
        m_password_hash = password_hash;
    }
}

void User::SetAccessLevel(AccessLevel access_level) {
    m_access_level = access_level;
}

} // namespace music_share
