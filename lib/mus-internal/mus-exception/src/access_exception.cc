#include "mus-exception/access_exception.h"

namespace music_share {

    AccessException::AccessException()
        : UseCaseException("No data access") { }

}  // namespace music_share
