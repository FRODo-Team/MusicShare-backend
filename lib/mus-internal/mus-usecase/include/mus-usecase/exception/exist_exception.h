#ifndef MUS_INTERNAL_EXCEPTION_EXIST_EXCEPTION_H_
#define MUS_INTERNAL_EXCEPTION_EXIST_EXCEPTION_H_

#include "use_case_exception.h"

namespace music_share {

    class ExistException : public UseCaseException {
    public:
        ExistException()
                : UseCaseException("Data already exist") { }
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_EXCEPTION_EXIST_EXCEPTION_H_
