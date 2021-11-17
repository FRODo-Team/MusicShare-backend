#ifndef MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_

#include <vector>
#include <string>
#include <optional>

#include "mus-dto/user_request_dto.h"
#include "mus-dto/user_response_dto.h"

namespace music_share {

class IUserUseCase {
public:
    IUserUseCase() = default;

    IUserUseCase(const IUserUseCase& user_use_case) = default;

    IUserUseCase& operator=(const IUserUseCase& user_use_case) = default;

    virtual std::optional<uint32_t> Create(UserRequestDTO user) = 0;

    virtual std::optional<UserResponseDTO> Update(UserRequestDTO user) = 0;

    virtual std::vector<UserResponseDTO> GetByUsername(std::string username) = 0;

    virtual std::optional<UserResponseDTO> GetByNickname(std::string nickname) = 0;

    virtual std::optional<UserResponseDTO> GetById(uint32_t id) = 0;

    virtual ~IUserUseCase() {};
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_