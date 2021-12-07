#ifndef MUS_INTERNAL_MUS_EXCEPTION_NULL_POINTER_EXCEPTION_H_
#define MUS_INTERNAL_MUS_EXCEPTION_NULL_POINTER_EXCEPTION_H_

#include "use_case_exception.h"

namespace music_share {

    class NullPointerException : public UseCaseException {
    public:
        NullPointerException();
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_EXCEPTION_NULL_POINTER_EXCEPTION_H_
