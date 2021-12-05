#ifndef MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_

#include <string>
#include <vector>

#include "mus-iusecase/iuser_use_case.h"
#include "mus-irepo/iuser_repository.h"

namespace music_share {

    class UserUseCase : public IUserUseCase {
    public:
        UserUseCase() = delete;

        explicit UserUseCase(IUserRepository& user_rep);

        UserUseCase(const UserUseCase& user_use_case);

        UserUseCase &operator=(const UserUseCase& user_use_case);

        uint32_t Create(const UserRequestDTO& user_dto) override;

        UserResponseDTO Update(uint32_t user_id,
                               const UserRequestDTO& user_dto) override;

        UserResponseDTO GetByUsername(const std::string& username) override;

        std::vector<UserResponseDTO> GetByNickname(const std::string& nickname) override;

        UserResponseDTO GetByEmail(const std::string& email) override;

        UserResponseDTO GetById(uint32_t id) override;

        void DeleteById(uint32_t id) override;

        ~UserUseCase() = default;

    private:
        IUserRepository &m_user_rep;
    };

}  // namespace music_share

#endif   // MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
