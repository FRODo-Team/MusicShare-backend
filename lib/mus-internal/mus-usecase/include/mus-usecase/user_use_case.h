// Oweners: Darya Vlaskina, ML-13
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

        UserUseCase& operator=(const UserUseCase& user_use_case);

        uint32_t Create(const UserRequestDTO& user_dto) override;

        UserResponseDTO Update(uint32_t user_id,
                               const UserRequestDTO& user_dto) override;

        UserResponseDTO GetByUsername(const std::string& username) const override;

        std::vector<UserResponseDTO> GetByNicknames(const std::vector<std::string> nicknames) const override;

        UserResponseDTO GetById(uint32_t id) const override;

        ~UserUseCase() = default;

    private:
        IUserRepository &m_user_rep;
    };

}  // namespace music_share

#endif   // MUS_INTERNAL_MUS_USECASE_USER_USE_CASE_H_
