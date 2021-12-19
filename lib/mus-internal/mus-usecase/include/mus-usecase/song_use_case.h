#ifndef MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_

#include <vector>

#include "mus-iusecase/isong_use_case.h"
#include "mus-irepo/isong_repository.h"

namespace music_share {

    class SongUseCase : public ISongUseCase {
    public:
        SongUseCase() = delete;

        explicit SongUseCase(ISongRepository& song_rep);

        SongUseCase(const SongUseCase& song_use_case);

        SongUseCase &operator=(const SongUseCase& song_use_case);

        SongResponseDTO GetById(uint32_t id) const override;

        std::vector<SongResponseDTO> GetByArtistAndTitle(const std::optional<std::string>& artist = {},
                                                         const std::optional<std::string>& title = {}) const override;

        ~SongUseCase() = default;

    private:
        ISongRepository &m_song_rep;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_SONG_USE_CASE_H_
