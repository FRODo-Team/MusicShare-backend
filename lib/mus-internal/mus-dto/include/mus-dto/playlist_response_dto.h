#ifndef MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_

#include <string>

struct PlaylistResponseDTO {
    PlaylistResponseDTO(int id_, int author_id_, int songs_count_,
                        int likes_count_, std::string title_)
                        : id(id_), author_id(author_id_),
                        songs_count(songs_count_), likes_count(likes_count_),
                        title(title_) {}

    int id;
    int author_id;
    int songs_count;
    int likes_count;
    std::string title;
};

#endif  // MUS_INTERNAL_MUS_DTO_PLAYLIST_RESPONSE_DTO_H_
