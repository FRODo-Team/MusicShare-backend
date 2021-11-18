#ifndef MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_

#include "mus-iusecase/iplaylist_use_case.h"
#include "mus-irepo/iplaylist_repository.h"

namespace music_share {

class PlaylistUseCase : public IPlaylistUseCase {
public:
    PlaylistUseCase() = delete;

    PlaylistUseCase(IPlaylistRepository &playlist_rep);

    PlaylistUseCase(const PlaylistUseCase &playlist_use_case);

    virtual PlaylistUseCase &operator=(const PlaylistUseCase &playlist_use_case);

    ~PlaylistUseCase();

    std::optional<uint32_t> Create(uint32_t user_id, PlaylistRequestDTO playlist) override;

    bool DeleteById(uint32_t user_id, uint32_t playlist_id) override;

    bool AddSongById(PlaylistSongRequestDTO song, uint32_t playlist_id,
                     uint32_t user_id) override;

    bool DeleteSongById(uint32_t song_id, uint32_t playlist_id, uint32_t user_id) override;

    std::vector<PlaylistResponseDTO> GetByUserId(uint32_t user_id,
                                                 uint32_t author_id) override;

    std::optional<PlaylistResponseDTO> GetById(uint32_t id) override;

    std::vector<SongResponseDTO> GetSongs(uint32_t playlist_id) override;

private:
    IPlaylistRepository &m_playlist_rep;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
