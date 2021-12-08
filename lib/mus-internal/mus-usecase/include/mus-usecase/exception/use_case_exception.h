#ifndef MUS_INTERNAL_EXCEPTION_USE_CASE_EXCEPTION_H_
#define MUS_INTERNAL_EXCEPTION_USE_CASE_EXCEPTION_H_

#include <exception>
#include <string>

namespace music_share {

    class UseCaseException : public std::exception {
    public:
        explicit UseCaseException(const std::string& error)
                                    : m_error(error) { };

        const char* what() const noexcept override {
            return m_error.c_str();
        }

    protected:
        std::string m_error;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_EXCEPTION_USE_CASE_EXCEPTION_H_
