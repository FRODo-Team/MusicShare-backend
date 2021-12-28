// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>
#include <vector>

struct PlaylistSongRequestDTO {
    PlaylistSongRequestDTO(const std::vector<uint32_t>& song_ids_)
                            : song_ids(song_ids_) {}

    std::vector<uint32_t> song_ids;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&PlaylistSongRequestDTO::song_ids, "songIds")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_SONG_REQUEST_DTO_H_
