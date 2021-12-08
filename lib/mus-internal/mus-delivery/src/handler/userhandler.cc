#include "mus-delivery/handler/UserHandler.h"

#include "http/server/router.h"
#include "http/common.h"

namespace music_share::delivery {

UserHandler::UserHandler(IUserUseCase& usecase) : m_usecase(usecase) {}

void UserHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/users";

    router.GET(http::server::router::Route(
        prefix,
        [](auto, auto) {
            http::common::Response response;
            response.body() = "GET users";
            return response;
        }, {}
    ));

    router.POST(http::server::router::Route(
        prefix,
        [](auto, auto) {
            http::common::Response response;
            response.body() = "POST users";
            return response;
        }, {}
    ));

    router.GET(http::server::router::Route(
        prefix + "/:id([0-9]+)",
        [](auto, auto p) {
            http::common::Response response;
            response.body() = "GET users " + p["id"];
            return response;
        }, {}
    ));

    router.PUT(http::server::router::Route(
        prefix + "/:id([0-9]+)",
        [](auto, auto p) {
            http::common::Response response;
            response.body() = "PUT users " + p["id"];
            return response;
        }, {}
    ));
}

std::vector<UserResponseDTO>
UserHandler::GetUsers(const std::string& nickname) {
    return {UserResponseDTO(1, "", "")};
}

std::string
UserHandler::CreateUser(const UserRequestDTO& request) {
    return "";
}

UserResponseDTO
UserHandler::GetUserById(uint32_t id) {
    return UserResponseDTO(1, "", "");
}

UserResponseDTO
UserHandler::UpdateUserById(uint32_t id) {
    return UserResponseDTO(1, "", "");
}

}  // namespace music_share::delivery
