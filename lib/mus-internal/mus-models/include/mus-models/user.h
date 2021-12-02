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

    User(const std::string& username,
         const std::string& email,
         const std::string& password_hash,
         const std::string& nickname,
         AccessLevel access_level,
         std::optional<uint32_t> id = { });

    User(const User&) = default;
    User(const User& other, uint32_t id);
    User(User&&) = default;
    ~User() = default;

    User& operator=(const User&) = default;

    std::optional<uint32_t> GetId() const { return m_id; }
    const std::string& GetUsername() const { return m_username; }
    const std::string& GetEmail() const { return m_email; }
    const std::string& GetPasswordHash() const { return m_password_hash; }
    const std::string& GetNickname() const { return m_nickname; }
    AccessLevel GetAccessLevel() const { return m_access_level; }

    void SetUsername(const std::string& username);
    void SetEmail(const std::string& email);
    void SetPasswordHash(const std::string& password_hash);
    void SetNickname(const std::string& nickname);
    void SetAccessLevel(AccessLevel access_level);

private:
    std::string m_username;             // Уникален
    std::string m_email;
    std::string m_password_hash;
    std::string m_nickname;             // Отображаемое имя. Может быть неуникален.
    AccessLevel m_access_level;
    std::optional<uint32_t> m_id;

    static constexpr uint32_t kNicknameMaxLength = 30;
    static constexpr uint32_t kEmailMaxLength = 254;        // RFC3696 Errata ID 1690 standard set 254 characters for email as maximum
    static constexpr uint32_t kUsernameMaxLength = 30;
    static constexpr uint32_t kPasswordHashMaxLength = 30;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_USER_H_
