#ifndef MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_

#include <vector>
#include <string>

#include "user_request_dto.h"
#include "user_response_dto.h"

class IUserUseCase {
public:
    IUserUseCase() = default;

    IUserUseCase(const IUserUseCase& user_use_case) = default;

    IUserUseCase& operator=(const IUserUseCase& user_use_case) = default;

    virtual bool Create(UserRequestDTO user) = 0;

    virtual std::optional<UserResponseDTO> Update(UserRequestDTO user) = 0;

    virtual std::vector<UserResponseDTO> GetByName(std::string name) = 0;

    virtual std::vector<UserResponseDTO> GetBySurname(strd::string surname) = 0;

    virtual UserResponseDTO GetByNickname(std::string nickname) = 0;

    virtual std::optional<UserResponseDTO> GetById(int id) = 0;

    virtual ~IUserUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_IUSER_USE_CASE_H_
