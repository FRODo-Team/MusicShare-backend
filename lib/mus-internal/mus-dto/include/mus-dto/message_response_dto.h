#ifndef MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_

#include <string>

struct MessageResponseDTO {
    MessageResponseDTO(int id_, int chat_id_, int sender_id_,
                       std::string content_, std::string datetime_)
                       : id(id_), chat_id(chat_id_), sender_id(sender_id_),
                       content(content_), datetime(datetime_) {}

    int id;
    int chat_id;
    int sender_id;
    std::string content;
    std::string datetime;
};

#endif  // MUS_INTERNAL_MUS_DTO_MESSAGE_RESPONSE_DTO_H_
