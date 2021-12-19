#ifndef MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <string>

struct MessageRequestDTO {
    MessageRequestDTO(const std::string& content_,
                      std::optional<uint32_t> playlist_id_ = {})
                    : content(content_),
                      playlist_id(playlist_id_) {}

    std::string content;
    std::optional<uint32_t> playlist_id;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&MessageRequestDTO::content, "content"),
        music_share::reflectable::Property(&MessageRequestDTO::playlist_id, "playlistId")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_MESSAGE_REQUEST_DTO_H_
