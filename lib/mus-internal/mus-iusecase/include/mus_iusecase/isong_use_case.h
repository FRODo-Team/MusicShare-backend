#ifndef MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_

#include <cstdint>
#include <vector>
#include <string>

#include "mus-dto/song_response_dto.h"

class ISongUseCase {
public:
    ISongUseCase() = default;

    ISongUseCase(const ISongUseCase& song_use_case) = default;

    ISongUseCase& operator=(const ISongUseCase& song_use_case) = default;

    virtual std::optional<SongResponseDTO> GetById(uint32_t id) = 0;

    virtual std::vector<SongResponseDTO> GetByTitle(std::string title) = 0;

    virtual std::vector<SongResponseDTO> GetByArtist(std::string artist) = 0;

    virtual ~ISongUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
