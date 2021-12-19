#ifndef MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>
#include <optional>
#include <string>

struct MessageResponseDTO {
    MessageResponseDTO(uint32_t id_, uint32_t chat_id_,
                       uint32_t sender_id_,
                       const std::string& content_,
                       const std::string& datetime_)
                       : id(id_), chat_id(chat_id_), sender_id(sender_id_),
                       content(content_), datetime(datetime_) {}

    uint32_t id;
    uint32_t chat_id;
    uint32_t sender_id;
    std::string content;
    std::string datetime;
    std::optional<uint32_t> playlist_id;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&MessageResponseDTO::id, "id"),
        music_share::reflectable::Property(&MessageResponseDTO::chat_id, "chatId"),
        music_share::reflectable::Property(&MessageResponseDTO::sender_id, "senderId"),
        music_share::reflectable::Property(&MessageResponseDTO::content, "content"),
        music_share::reflectable::Property(&MessageResponseDTO::datetime, "datetime"),
        music_share::reflectable::Property(&MessageResponseDTO::playlist_id, "playlistId")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_
