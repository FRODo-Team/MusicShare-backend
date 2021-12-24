#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_

#include "reflectable/reflectable.h"
#include "mus-dto/song_response_dto.h"

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>

struct PlaylistResponseDTO {
    PlaylistResponseDTO(uint32_t id_, uint32_t author_id_,
                        uint32_t songs_count_,
                        const std::string& title_,
                        const std::vector<SongResponseDTO>& songs_dto_)
                        : id(id_), author_id(author_id_),
                        songs_count(songs_count_),
                        title(title_), songs_dto(songs_dto_) {}

    uint32_t id;
    uint32_t author_id;
    uint32_t songs_count;
    std::string title;
    std::vector<SongResponseDTO> songs_dto;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&PlaylistResponseDTO::id, "id"),
        music_share::reflectable::Property(&PlaylistResponseDTO::author_id, "authorId"),
        music_share::reflectable::Property(&PlaylistResponseDTO::songs_count, "songsCount"),
        music_share::reflectable::Property(&PlaylistResponseDTO::title, "title"),
        music_share::reflectable::Property(&PlaylistResponseDTO::songs_dto, "songsDto")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
