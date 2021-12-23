// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_IREPO_IUSER_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IUSER_REPOSITORY_H_

#include <vector>

#include "mus-models/user.h"
#include "irepository.h"

namespace music_share {

class IUserRepository : public IRepository<User> {
public:
    virtual ~IUserRepository() = default;
    virtual std::vector<User> FetchAll(std::optional<uint32_t> limit = { }) = 0;
    virtual std::vector<User> FindByNickname(const std::string& nickname) = 0;
    virtual std::optional<User> FindByUsername(const std::string& username) = 0;
    virtual std::optional<User> FindByEmail(const std::string& email) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IUSER_REPOSITORY_H_
