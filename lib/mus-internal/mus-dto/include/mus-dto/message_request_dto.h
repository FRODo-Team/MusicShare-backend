#ifndef MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_

#include <string>

struct MessageRequestDTO {
    MessageRequestDTO(std::string content_): content(content_) {}

    std::string content;
};

#endif  // MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_
