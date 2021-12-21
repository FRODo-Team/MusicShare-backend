// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>
#include <string>

struct PlaylistResponseDTO {
    PlaylistResponseDTO(uint32_t id_, uint32_t author_id_,
                        uint32_t songs_count_,
                        const std::string& title_)
                        : id(id_), author_id(author_id_),
                        songs_count(songs_count_),
                        title(title_) {}

    uint32_t id;
    uint32_t author_id;
    uint32_t songs_count;
    std::string title;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&PlaylistResponseDTO::id, "id"),
        music_share::reflectable::Property(&PlaylistResponseDTO::author_id, "authorId"),
        music_share::reflectable::Property(&PlaylistResponseDTO::songs_count, "songsCount"),
        music_share::reflectable::Property(&PlaylistResponseDTO::title, "title")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
