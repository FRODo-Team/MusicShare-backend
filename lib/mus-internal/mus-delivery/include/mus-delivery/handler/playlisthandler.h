// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_PLAYLISTHANDLER_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_PLAYLISTHANDLER_H_

#include <memory>  // std::shared_ptr
#include <vector>  // std::vector

#include "mus-iusecase/iplaylist_use_case.h"
#include "http/server/router/router.h"

namespace music_share::delivery {

class PlaylistHandler final {
public:
    PlaylistHandler(IPlaylistUseCase& usecase);
    void Config(http::server::router::Router& router);

    std::vector<PlaylistResponseDTO>
    GetByAuthor(uint32_t author_id);

    uint32_t
    CreatePlaylist(uint32_t author_id, const PlaylistRequestDTO& request);

    PlaylistResponseDTO
    GetById(uint32_t author_id, uint32_t playlist_id);

    void
    DeleteById(uint32_t author_id, uint32_t playlist_id);

    std::vector<uint32_t>
    GetSongsById(uint32_t author_id, uint32_t playlist_id);

    void
    AddSongById(uint32_t author_id, uint32_t playlist_id,
                const PlaylistSongRequestDTO& request);

    void
    RemoveSongById(uint32_t author_id, uint32_t playlist_id,
                   uint32_t song_id);
private:
    [[maybe_unused]] IPlaylistUseCase& m_usecase;
};

}  // namespace music_share::delivery

#endif  // MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_PLAYLISTHANDLER_H_
