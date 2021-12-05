#ifndef MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_

#include <cstdint>
#include <string>
#include <vector>

#include "mus-dto/song_request_dto.h"
#include "mus-dto/song_response_dto.h"

namespace music_share {

class ISongUseCase {
public:
    ISongUseCase() = default;

    ISongUseCase(const ISongUseCase& song_use_case) = default;

    ISongUseCase& operator=(const ISongUseCase& song_use_case) = default;

    virtual SongResponseDTO GetById(uint32_t id) = 0;

    virtual std::vector<SongResponseDTO> GetByTitle(const std::string& title) = 0;

    virtual std::vector<SongResponseDTO> GetByArtist(const std::string& artist) = 0;

    virtual uint32_t Create(const SongRequestDTO& song_dto) = 0;

    virtual SongResponseDTO Update(uint32_t song_id,
                        const SongRequestDTO& song_dto) = 0;

    virtual void DeleteById(uint32_t song_id) = 0;

    virtual ~ISongUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
