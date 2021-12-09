#ifndef MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>

struct ChatRequestDTO {
    ChatRequestDTO(uint32_t target_id_)
                    : target_id(target_id_) { }

    uint32_t target_id;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&ChatRequestDTO::target_id, "targetId")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_
