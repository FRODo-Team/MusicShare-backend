#ifndef MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_

#include <vector>
#include <string>

#include "isong_use_case.h"

class ISongUseCase {
public:
    ISongUseCase() = default;

    ISongUseCase(const ISongUseCase& song_use_case) = default;

    ISongUseCase& operator=(const ISongUseCase& song_use_case) = default;

    virtual std::optional<SongResponseDTO> GetById(int id) = 0;

    virtual std::vector<SongResponseDTO> GetByTitle(std::string title) = 0;

    virtual vector<SongResponseDTO> GetByArtist(std::string artist) = 0;

    virtual ~ISongUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_ISONG_USE_CASE_H_
