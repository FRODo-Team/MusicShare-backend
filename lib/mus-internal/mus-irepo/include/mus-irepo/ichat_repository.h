#ifndef MUS_INTERNAL_MUS_IREPO_ICHAT_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_ICHAT_REPOSITORY_H_

#include <vector>

#include "mus-models/chat.h"
#include "irepository.h"

namespace music_share {

class IChatRepository : public IRepository<Chat> {
public:
    /* Возвращает список всех чатов конкретного пользователя. */
    virtual std::vector<Chat> FindByUserId(uint32_t user_id) = 0;

    /* Возвращает чат-диалог двух пользователей. */
    virtual Chat FindByIdsOfUserPair(uint32_t first_user_id,
                                     uint32_t second_user_id) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_ICHAT_REPOSITORY_H_
