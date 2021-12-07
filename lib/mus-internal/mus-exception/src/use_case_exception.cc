#include "mus-exception/use_case_exception.h"

namespace music_share {

    UseCaseException::UseCaseException(const std::string& error)
                                        : m_error(error) {}

    const char* UseCaseException::what() const noexcept {
        return m_error.c_str();
    }

}  // namespace music_share