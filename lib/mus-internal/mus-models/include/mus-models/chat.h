// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_MODELS_CHAT_H_
#define MUS_INTERNAL_MUS_MODELS_CHAT_H_

#include <cstdint>
#include <utility>
#include <optional>

namespace music_share {

class Chat {
public:
    Chat() = delete;

    Chat(std::pair<uint32_t, uint32_t> user_ids,
         std::optional<uint32_t> id = { });

    Chat(uint32_t user_1_id, uint32_t user_2_id,
         std::optional<uint32_t> id = { });

    Chat(const Chat& other, uint32_t id);
    Chat(const Chat&) = default;
    Chat(Chat&&) = default;
    ~Chat() = default;

    Chat& operator=(const Chat&) = default;

    std::optional<uint32_t> GetId() const { return m_id; }
    std::pair<uint32_t, uint32_t> GetUserIds() const { return m_user_ids; }

private:
    std::pair<uint32_t, uint32_t> m_user_ids;
    std::optional<uint32_t> m_id;
};

}

#endif // MUS_INTERNAL_MUS_MODELS_CHAT_H_
