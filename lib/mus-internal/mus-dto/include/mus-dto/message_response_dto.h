#ifndef MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_

#include <cstdint>
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
};

#endif  // MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_
