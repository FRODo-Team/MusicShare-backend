// Owners: Rostislav Vivcharuk, WEB-12
#include "mus-models/chat.h"

namespace music_share {

Chat::Chat(std::pair<uint32_t, uint32_t> user_ids,
           std::optional<uint32_t> id)
        :
        m_user_ids(user_ids),
        m_id(id) { }

Chat::Chat(uint32_t user_1_id, uint32_t user_2_id, std::optional<uint32_t> id)
        :
        m_user_ids(std::make_pair(user_1_id, user_2_id)),
        m_id(id) { }

Chat::Chat(const Chat& other, uint32_t id)
        :
        m_user_ids(other.GetUserIds()),
        m_id(id) { }

} // namespace music_share