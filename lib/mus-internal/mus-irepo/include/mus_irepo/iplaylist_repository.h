#ifndef MUS_INTERNAL_MUS_IREPO_IPLAYLIST_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IPLAYLIST_REPOSITORY_H_

#include "mus_models/playlist.h"
#include "irepository.h"

namespace music_share {

class IPlaylistRepository : public IRepository<Playlist> {
public:
    virtual std::vector<Playlist> FindByUserId(uint32_t user_id) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IPLAYLIST_REPOSITORY_H_
