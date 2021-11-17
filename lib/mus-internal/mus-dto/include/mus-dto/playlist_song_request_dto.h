#ifndef MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_

#include <cstdint>
#include <vector>

struct PlaylistSongRequestDTO {
    PlaylistSongRequestDTO(std::vector<uint32_t> song_ids_)
                            : song_ids(song_ids_) {}

    std::vector<uint32_t> song_ids;
};

#endif  // MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
