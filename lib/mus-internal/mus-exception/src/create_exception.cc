#include "mus-exception/create_exception.h"

namespace music_share {

    CreateException::CreateException()
        : UseCaseException("Can't create") { }

}  // namespace music_share
