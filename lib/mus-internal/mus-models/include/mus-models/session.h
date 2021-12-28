// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_MODELS_SESSION_H_
#define MUS_INTERNAL_MUS_MODELS_SESSION_H_

#include <optional>
#include <string>

namespace music_share {

class Session {
public:
    static constexpr int SessionKeyLength = 128;

    Session() = delete;

    Session(uint32_t user_id,
            const std::string& session_key,
            const std::string& date_expires,
            std::optional<uint32_t> id = { })
            :
            m_user_id(user_id),
            m_session_key(session_key),
            m_date_expires(date_expires),
            m_id(id) { }

    Session(const Session& other, uint32_t id)
            :
            m_user_id(other.m_user_id),
            m_session_key(other.m_session_key),
            m_date_expires(other.m_date_expires),
            m_id(id) { }

    Session(const Session&) = default;
    Session(Session&&) = default;
    ~Session() = default;

    Session& operator=(const Session&) = default;

    std::optional<uint32_t> GetId() const { return m_id; }
    uint32_t GetUserId() const { return m_user_id; }
    const std::string& GetSessionKey() const { return m_session_key; }
    const std::string& GetDateExpires() const { return m_date_expires; }

private:
    uint32_t m_user_id;
    std::string m_session_key;
    std::string m_date_expires;
    std::optional<uint32_t> m_id;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_SESSION_H_
