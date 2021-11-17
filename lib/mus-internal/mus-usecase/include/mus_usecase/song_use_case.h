#ifndef MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_

#include "mus-iusecase/isong_use_case.h"
#include "mus-irepo/isong_repository.h"

class SongUseCase : public ISongUseCase {
public:
    SongUseCase() = delete;

    SongUseCase(music_share::ISongRepository& song_rep);

    SongUseCase(const SongUseCase& song_use_case);

    SongUseCase& operator=(const SongUseCase& song_use_case);

    std::optional<SongResponseDTO> GetById(uint32_t id) override;

    std::vector<SongResponseDTO> GetByTitle(std::string title) override;

    std::vector<SongResponseDTO> GetByArtist(std::string artist) override;

    ~SongUseCase();

private:
    music_share::ISongRepository& m_song_rep;
};


#endif  // MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_
