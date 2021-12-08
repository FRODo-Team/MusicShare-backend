#ifndef MUS_INTERNAL_EXCEPTION_INVALID_DATA_EXCEPTION_H_
#define MUS_INTERNAL_EXCEPTION_INVALID_DATA_EXCEPTION_H_

#include "use_case_exception.h"

namespace music_share {

    class InvalidDataException : public UseCaseException {
    public:
        InvalidDataException()
            : UseCaseException("Data doesn`t exist") { }
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_EXCEPTION_INVALID_DATA_EXCEPTION_H_
