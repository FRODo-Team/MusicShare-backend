#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_

#include "reflectable/reflectable.h"
#include "mus-dto/playlist_song_request_dto.h"

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>

struct PlaylistRequestDTO {
    PlaylistRequestDTO(const std::string& name_,
                       const PlaylistSongRequestDTO& song_dto)
                        : name(name_), song_dto(song_dto) {}

    std::string name;
    PlaylistSongRequestDTO song_dto;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&PlaylistRequestDTO::name, "name"),
        music_share::reflectable::Property(&PlaylistRequestDTO::song_dto, "songDto")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
