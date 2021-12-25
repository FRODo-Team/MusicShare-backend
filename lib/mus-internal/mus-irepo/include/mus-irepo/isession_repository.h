#ifndef MUS_INTERNAL_MUS_IREPO_ISESSION_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_ISESSION_REPOSITORY_H_

#include <optional>
#include "mus-models/session.h"
#include "mus-irepo/irepository.h"

namespace music_share {

class ISessionRepository : public IRepository<Session> {
public:
    virtual ~ISessionRepository() = default;

    virtual std::optional<Session> FindBySessionKey(const std::string& key) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_ISESSION_REPOSITORY_H_
