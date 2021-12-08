#ifndef MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_

#include <string>
#include <vector>

#include "mus-dto/user_request_dto.h"
#include "mus-dto/user_response_dto.h"

namespace music_share {

class IUserUseCase {
public:
    IUserUseCase() = default;

    IUserUseCase(const IUserUseCase& user_use_case) = default;

    IUserUseCase& operator=(const IUserUseCase& user_use_case) = default;

    virtual uint32_t Create(const UserRequestDTO& user_dto) = 0;

    virtual UserResponseDTO Update(uint32_t user_id,
                                   const UserRequestDTO& user_dto) = 0;

    virtual UserResponseDTO GetByUsername(const std::string& username) = 0;

    virtual std::vector<UserResponseDTO> GetByNicknames(const std::vector<std::string>& nicknames) = 0;

    virtual UserResponseDTO GetById(uint32_t id) = 0;

    virtual ~IUserUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_
