#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_

#include <cstdint>
#include <string>
#include <vector>

struct PlaylistRequestDTO {
    PlaylistRequestDTO(const std::string& name_,
                       const std::vector<uint32_t>& song_ids_)
                        : name(name_), song_ids(song_ids_) {}

    std::string name;
    std::vector<uint32_t> song_ids;
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
