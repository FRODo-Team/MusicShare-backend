#ifndef MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_

#include "isong_use_case.h"
#include "isong_reprositoriy.h"

class SongUseCase : ISongUseCase {
public:
    SongUseCase() = delete;

    SongUseCase(ISongReprositoriy& song_rep);

    SongUseCase(const SongUseCase& song_use_case);

    SongUseCase& operator=(const SongUseCase& song_use_case);

    std::optional<SongResponseDTO> GetById(int id) override;

    std::vector<SongResponseDTO> GetByTitle(std::string title) override;

    vector<SongResponseDTO> GetByArtist(std::string artist) override;

    ~ISongUseCase();

private:
    ISongReprositoriy& m_song_rep;
};


#endif  // MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_
