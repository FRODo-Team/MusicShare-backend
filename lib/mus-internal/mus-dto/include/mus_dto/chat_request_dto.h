#ifndef MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_

#include <cstdint>

struct ChatRequestDTO {
    ChatRequestDTO(uint32_t target_id_) : target_id(target_id_) {}

    uint32_t target_id;
};

#endif  // MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_
