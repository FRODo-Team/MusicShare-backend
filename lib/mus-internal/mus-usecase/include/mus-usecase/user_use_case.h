#ifndef MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_

#include "iuser_use_case.h"
#include "iuser_reprositoriy.h"

class UserUseCase : IUserUseCase {
public:
    UserUseCase() = delete;

    UserUseCase(IUserReprository& user_rep);

    UserUseCase(const UserUseCase& user_use_case);

    UserUseCase& operator=(const UserUseCase& user_use_case);

    bool Create(UserRequestDTO user) override;

    std::optional<UserResponseDTO> Update(UserRequestDTO user) override;

    std::vector<UserResponseDTO> GetByName(std::string name) override;

    std::vector<UserResponseDTO> GetBySurname(strd::string surname) override;

    UserResponseDTO GetByNickname(std::string nickname) override;

    std::optional<UserResponseDTO> GetById(int id) override;

    ~UserUseCase();

private:
    IUserReprositoriy& m_user_rep;
};

#endif   // MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
