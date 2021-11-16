#ifndef MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_

#include <memory>

struct PlaylistSongRequestDTO {
    PlaylistSongRequestDTO(std::shared_ptr<int> song_ids_)
                            : song_ids(song_ids_) {}

    std::shared_ptr<int> song_ids;
};

#endif  // MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
