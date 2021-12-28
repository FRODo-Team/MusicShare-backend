// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_IREPO_IMESSAGE_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IMESSAGE_REPOSITORY_H_

#include <vector>

#include "mus-models/chat_message.h"
#include "irepository.h"

namespace music_share {

class IChatMessageRepository : public IRepository<ChatMessage> {
public:
    virtual ~IChatMessageRepository() = default;
    /* Возвращает список всех сообщений, отправленных обоими пользователями
     * в чате-диалоге друг с другом.
     */
    virtual std::vector<ChatMessage> FindByChatId(uint32_t chat_id) = 0;

    virtual std::vector<ChatMessage> FindByUserId(
            uint32_t user_id, std::optional<std::string> since_datetime) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IMESSAGE_REPOSITORY_H_
