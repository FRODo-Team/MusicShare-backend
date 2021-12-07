#ifndef MUS_INTERNAL_MUS_EXCEPTION_CREATE_EXCEPTION_H_
#define MUS_INTERNAL_MUS_EXCEPTION_CREATE_EXCEPTION_H_

#include "use_case_exception.h"

namespace music_share {

    class CreateException : public UseCaseException {
    public:
        CreateException();
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_EXCEPTION_CREATE_EXCEPTION_H_
