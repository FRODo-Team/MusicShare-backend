#include "mus_models/user.h"

namespace music_share {

User::User(const std::string& nickname,
           const std::string& email,
           const std::string& username,
           const std::string& password_hash,
           AccessLevel access_level,
           std::optional<uint32_t> id) :
    m_nickname(nickname),
    m_email(email),
    m_username(username),
    m_password_hash(password_hash),
    m_access_level(access_level),
    m_id(id) { }

std::optional<uint32_t> User::GetId() const {
    return m_id;
}

const std::string& User::GetNickname() const {
    return m_nickname;
}

const std::string& User::GetEmail() const {
    return m_email;
}

const std::string& User::GetUsername() const {
    return m_username;
}

const std::string& User::GetPasswordHash() const {
    return m_password_hash;
}

User::AccessLevel User::GetAccessLevel() const {
    return m_access_level;
}

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
