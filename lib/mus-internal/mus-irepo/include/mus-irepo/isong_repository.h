#ifndef MUS_INTERNAL_MUS_IREPO_ISONG_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_ISONG_REPOSITORY_H_

#include <vector>

#include "mus-models/song.h"
#include "irepository.h"

namespace music_share {

class ISongRepository : public IRepository<Song> {
public:
    virtual std::vector<Song> FindByTitle(const std::string& title) = 0;
    virtual std::vector<Song> FindByArtist(const std::string& artist) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_ISONG_REPOSITORY_H_
