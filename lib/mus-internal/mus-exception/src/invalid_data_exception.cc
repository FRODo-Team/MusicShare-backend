#include "mus-exception/invalid_data_exception.h"

namespace music_share {

    InvalidDataException::InvalidDataException()
        : UseCaseException("Data doesn`t exist") { }

}  // namespace music_share
