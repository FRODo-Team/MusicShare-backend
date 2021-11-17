#ifndef MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_

#include "mus-iusecase/iuser_use_case.h"
#include "mus-irepo/iuser_repository.h"

class UserUseCase : public IUserUseCase {
public:
    UserUseCase() = delete;

    UserUseCase(music_share::IUserRepository& user_rep);

    UserUseCase(const UserUseCase& user_use_case);

    UserUseCase& operator=(const UserUseCase& user_use_case);

    std::optional<uint32_t> Create(UserRequestDTO user) override;

    std::optional<UserResponseDTO> Update(UserRequestDTO user) override;

    std::vector<UserResponseDTO> GetByUsername(std::string username) override;

    std::optional<UserResponseDTO> GetByNickname(std::string nickname) override;

    std::optional<UserResponseDTO> GetById(uint32_t id) override;

    ~UserUseCase();

private:
    music_share::IUserRepository& m_user_rep;
};

#endif   // MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
