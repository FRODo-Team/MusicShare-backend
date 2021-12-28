// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_IREPO_IPLAYLIST_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IPLAYLIST_REPOSITORY_H_

#include "mus-models/playlist.h"
#include "irepository.h"

namespace music_share {

class IPlaylistRepository : public IRepository<Playlist> {
public:
    virtual ~IPlaylistRepository() = default;
    virtual std::vector<Playlist> FindByTitle(const std::string& title) = 0;
    virtual std::vector<Playlist> FindByCreatorId(uint32_t creator_id) = 0;
    virtual std::vector<Playlist> FindByUserId(uint32_t user_id) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IPLAYLIST_REPOSITORY_H_
