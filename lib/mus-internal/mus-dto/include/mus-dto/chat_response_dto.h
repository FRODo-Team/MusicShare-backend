// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_DTO_CHAT_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_CHAT_RESPONSE_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>

struct ChatResponseDTO {
    ChatResponseDTO(uint32_t chat_id_, uint32_t user_first_id_,
                    uint32_t user_second_id_) :
                    chat_id(chat_id_), user_first_id(user_first_id_),
                    user_second_id(user_second_id_) {}

    uint32_t chat_id;
    uint32_t user_first_id;
    uint32_t user_second_id;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&ChatResponseDTO::chat_id, "chatId"),
        music_share::reflectable::Property(&ChatResponseDTO::user_first_id, "user1Id"),
        music_share::reflectable::Property(&ChatResponseDTO::user_second_id, "user2Id")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_CHAT_RESPONSE_DTO_H_
