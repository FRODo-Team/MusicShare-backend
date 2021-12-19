#ifndef MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <optional>

#include "mus-dto/song_response_dto.h"

namespace music_share {

class ISongUseCase {
public:
    ISongUseCase() = default;

    ISongUseCase(const ISongUseCase& song_use_case) = default;

    ISongUseCase& operator=(const ISongUseCase& song_use_case) = default;

    virtual SongResponseDTO GetById(uint32_t id) const = 0;

    virtual std::vector<SongResponseDTO> GetByArtistAndTitle(const std::optional<std::string> artist,
                                                             const std::optional<std::string> title) const = 0;

    virtual ~ISongUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
