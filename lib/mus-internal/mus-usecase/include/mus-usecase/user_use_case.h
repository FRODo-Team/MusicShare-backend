#ifndef MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_

#include "mus-iusecase/iuser_use_case.h"
#include "mus-irepo/iuser_repository.h"

namespace music_share {

class UserUseCase : public IUserUseCase {
public:
    UserUseCase() = delete;

    UserUseCase(IUserRepository &user_rep);

    UserUseCase(const UserUseCase &user_use_case);

    UserUseCase &operator=(const UserUseCase &user_use_case);

    std::optional<uint32_t> Create(UserRequestDTO user) override;

    std::optional<UserResponseDTO> Update(uint32_t user_id, UserRequestDTO user) override;

    std::vector<UserResponseDTO> GetByUsername(std::string username) override;

    std::optional<UserResponseDTO> GetByNickname(std::string nickname) override;

    std::optional<UserResponseDTO> GetById(uint32_t id) override;

    ~UserUseCase();

private:
    IUserRepository &m_user_rep;
};

} // namespace music_share

#endif   // MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
