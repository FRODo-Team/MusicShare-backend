#include "mus-models/chat.h"

namespace music_share {

Chat::Chat(std::pair<uint32_t, uint32_t> user_ids,
           std::optional<uint32_t> id) :
    m_user_ids(user_ids),
    m_id(id) { }

std::optional<uint32_t> Chat::GetId() const {
    return m_id;
}

std::pair<uint32_t, uint32_t> Chat::GetUserIds() const {
    return m_user_ids;
}

} // namespace music_share