#ifndef MUS_INTERNAL_MUS_IREPO_IUSER_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IUSER_REPOSITORY_H_

#include <vector>

#include "mus-models/user.h"
#include "irepository.h"

namespace music_share {

class IUserRepository : public IRepository<User> {
public:
    virtual std::vector<User> FindByNickname(const std::string& nickname) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IUSER_REPOSITORY_H_
