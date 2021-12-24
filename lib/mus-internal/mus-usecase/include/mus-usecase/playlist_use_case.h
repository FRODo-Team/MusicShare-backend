#ifndef MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_

#include <optional>
#include <string>
#include <vector>

#include "mus-iusecase/iplaylist_use_case.h"
#include "mus-iusecase/isong_use_case.h"
#include "mus-irepo/iplaylist_repository.h"

namespace music_share {

    class PlaylistUseCase : public IPlaylistUseCase {
    public:
        PlaylistUseCase() = delete;

        PlaylistUseCase(IPlaylistRepository& playlist_rep, ISongUseCase& song_usecase);

        PlaylistUseCase(const PlaylistUseCase& playlist_use_case);

        PlaylistUseCase &operator=(const PlaylistUseCase& playlist_use_case);

        uint32_t Create(uint32_t user_id,
                        const PlaylistRequestDTO& playlist_dto) override;

        void DeleteById(uint32_t user_id,
                        uint32_t playlist_id) override;

        void AddSongById(const PlaylistSongRequestDTO& song_dto,
                         uint32_t playlist_id,
                         uint32_t user_id) override;

        void DeleteSongById(uint32_t song_id, uint32_t playlist_id,
                            uint32_t user_id) override;

        std::vector<PlaylistResponseDTO> GetByUserId(uint32_t user_id) const override;

        PlaylistResponseDTO GetById(uint32_t id) const override;

        ~PlaylistUseCase() = default;

    private:
        std::vector<SongResponseDTO> GetSongs(const std::vector<uint32_t>& song_ids) const;

        IPlaylistRepository& m_playlist_rep;
        ISongUseCase& m_song_usecase;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
