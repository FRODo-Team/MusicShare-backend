#ifndef MUS_INTERNAL_MUS_EXCEPTION_NO_ACCESS_EXCEPTION_H_
#define MUS_INTERNAL_MUS_EXCEPTION_NO_ACCESS_EXCEPTION_H_

#include "use_case_exception.h"

namespace music_share {

    class AccessException : public UseCaseException {
    public:
        AccessException();
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_EXCEPTION_NO_ACCESS_EXCEPTION_H_
