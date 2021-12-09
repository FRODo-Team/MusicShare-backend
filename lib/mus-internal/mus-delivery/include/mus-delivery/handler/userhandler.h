#ifndef MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_USERHANDLER_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_USERHANDLER_H_

#include <memory>  // std::shared_ptr
#include <vector>  // std::vector

#include "mus-iusecase/iuser_use_case.h"
#include "http/server/router/router.h"

namespace music_share::delivery {

class UserHandler final {
public:
    //UserHandler(IUserUseCase& usecase);
    UserHandler() = default;
    void Config(http::server::router::Router& router);

    std::vector<UserResponseDTO>
    GetUsers(const std::vector<std::string>& nicknames);

    std::string
    CreateUser(const UserRequestDTO& request);

    UserResponseDTO
    GetUserById(uint32_t id);

    UserResponseDTO
    UpdateUserById(uint32_t id);
private:
    //[[maybe_unused]] IUserUseCase& m_usecase;
};

}  // namespace music_share::delivery

#endif  // MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_USERHANDLER_H_
