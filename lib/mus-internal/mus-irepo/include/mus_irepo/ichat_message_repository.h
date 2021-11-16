#ifndef MUS_INTERNAL_MUS_IREPO_IMESSAGE_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IMESSAGE_REPOSITORY_H_

#include "mus_models/chat_message.h"
#include "irepository.h"

namespace music_share {

class IChatMessageRepository : public IRepository<ChatMessage> {
public:
    /* Возвращает список всех сообщений, отправленных обоими пользователями
     * в чате-диалоге друг с другом.
     */
    virtual std::vector<ChatMessage> FindByChatId(uint32_t chat_id) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IMESSAGE_REPOSITORY_H_
