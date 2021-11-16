#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_

#include <string>
#include <memory>

struct PlaylistRequestDTO {
    PlaylistRequestDTO(std::string name_,
                       std::shared_ptr<int> song_ids_)
                        : name(name_), song_ids(song_ids_) {}

    std::string name;
    std::shared_ptr<int> song_ids;
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_REQUEST_DTO_H_
