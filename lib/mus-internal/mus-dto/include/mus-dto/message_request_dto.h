#ifndef MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <string>

struct MessageRequestDTO {
    MessageRequestDTO(const std::string& content_)
                    : content(content_) {}

    std::string content;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&MessageRequestDTO::content, "content")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_
