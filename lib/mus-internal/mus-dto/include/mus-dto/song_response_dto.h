#ifndef MUS_INTERNAL_MUS_DTO_SONG_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_SONG_RESPONSE_DTO_H_

#include <cstdint>
#include <string>

struct SongResponseDTO {
    SongResponseDTO(uint32_t id_, const std::string& name_,
                    const std::string& author_,
                    const std::string& path_)
                    : id(id_), name(name_), author(author_),
                      path(path_) {}

    uint32_t id;
    std::string name;
    std::string author;
    std::string path;
};

#endif  // MUS_INTERNAL_MUS_DTO_SONG_RESPONSE_DTO_H_
