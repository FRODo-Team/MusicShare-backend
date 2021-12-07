#include "mus-exception/null_pointer_exception.h"

namespace music_share {

    NullPointerException::NullPointerException()
        : UseCaseException("Dereferencing a null pointer") { }

}  // namespace music_share
