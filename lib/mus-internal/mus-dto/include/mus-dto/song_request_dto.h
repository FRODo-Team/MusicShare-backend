#ifndef MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_

#include <optional>
#include <string>

struct SongRequestDTO {
    SongRequestDTO(const std::string& name_,
                   const std::string& author_,
                   const std::string& duration_,
                   const std::string& path_,
                   std::optional<uint32_t> year_ = { },
                   std::optional<std::string> album_ = { },
                   std::optional<std::string> genre_ = { } )
            : name(name_), author(author_),
              duration(duration_), path(path_),
              year(year_), album(album_), genre(genre_) { }

    std::string name;
    std::string author;
    std::string duration;
    std::string path;
    std::optional<uint32_t> year;
    std::optional<std::string> album;
    std::optional<std::string> genre;
};

#endif  // MUS_INTERNAL_MUS_DTO_SONG_REQUEST_DTO_H_
