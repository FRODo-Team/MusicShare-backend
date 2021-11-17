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
         std::optional<uint32_t> id = {});
    Chat(const Chat&) = default;
    Chat(Chat&&) = default;
    ~Chat() = default;

    std::optional<uint32_t> GetId() const;
    std::pair<uint32_t, uint32_t> GetUserIds() const;

private:
    std::pair<uint32_t, uint32_t> m_user_ids;
    std::optional<uint32_t> m_id;
};

}

#endif // MUS_INTERNAL_MUS_MODELS_CHAT_H_
