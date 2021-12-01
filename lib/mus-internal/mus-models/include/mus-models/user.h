#ifndef MUS_INTERNAL_MUS_MODELS_USER_H_
#define MUS_INTERNAL_MUS_MODELS_USER_H_

#include <string>
#include <optional>

namespace music_share {

class User {
public:
    enum class AccessLevel {
        Admin = 0,
        Authorized
    };

    User() = delete;
    User(const std::string& nickname,
         const std::string& email,
         const std::string& username,
         const std::string& password_hash,
         AccessLevel access_level = AccessLevel::Authorized,
         std::optional<uint32_t> id = {});

    User(const User&) = default;
    User(const User& other, uint32_t id);
    ~User() = default;

    std::optional<uint32_t> GetId() const;
    const std::string& GetNickname() const;
    const std::string& GetEmail() const;
    const std::string& GetUsername() const;
    const std::string& GetPasswordHash() const;
    AccessLevel GetAccessLevel() const;

    void SetNickname(const std::string& nickname);
    void SetEmail(const std::string& email);
    void SetUsername(const std::string& username);
    void SetPasswordHash(const std::string& password_hash);
    void SetAccessLevel(AccessLevel access_level);

private:
    std::string m_nickname;
    std::string m_email;
    std::string m_username;
    std::string m_password_hash;
    AccessLevel m_access_level;
    std::optional<uint32_t> m_id;

    static constexpr uint32_t kNicknameMaxLength = 30;
    static constexpr uint32_t kEmailMaxLength = 254;        // RFC3696 Errata ID 1690 standard set 254 characters for email as maximum
    static constexpr uint32_t kUsernameMaxLength = 30;
    static constexpr uint32_t kPasswordHashMaxLength = 30;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_USER_H_
