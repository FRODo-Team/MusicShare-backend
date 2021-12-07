#ifndef MUS_INTERNAL_MUS_EXCEPTION_USE_CASE_EXCEPTION_H_
#define MUS_INTERNAL_MUS_EXCEPTION_USE_CASE_EXCEPTION_H_

#include <exception>
#include <string>

namespace music_share {

    class UseCaseException : public std::exception {
    public:
        UseCaseException() = default;

        explicit UseCaseException(const std::string& error);

        const char* what() const noexcept override;

    protected:
        std::string m_error;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_EXCEPTION_USE_CASE_EXCEPTION_H_
