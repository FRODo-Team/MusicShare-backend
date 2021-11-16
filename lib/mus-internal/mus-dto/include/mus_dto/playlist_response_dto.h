#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_

#include <cstdint>
#include <string>

struct PlaylistResponseDTO {
    PlaylistResponseDTO(uint32_t id_, uint32_t author_id_, uint32_t songs_count_,
                        uint32_t likes_count_, std::string title_)
                        : id(id_), author_id(author_id_),
                        songs_count(songs_count_), likes_count(likes_count_),
                        title(title_) {}

    uint32_t id;
    uint32_t author_id;
    uint32_t songs_count;
    uint32_t likes_count;
    std::string title;
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
