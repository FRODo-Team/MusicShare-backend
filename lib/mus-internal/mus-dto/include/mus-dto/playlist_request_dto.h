// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>
#include <string>
#include <vector>

struct PlaylistRequestDTO {
    PlaylistRequestDTO(const std::string& name_,
                       const std::vector<uint32_t>& song_ids_)
                        : name(name_), song_ids(song_ids_) {}

    std::string name;
    std::vector<uint32_t> song_ids;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&PlaylistRequestDTO::name, "name"),
        music_share::reflectable::Property(&PlaylistRequestDTO::song_ids, "songIds")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
