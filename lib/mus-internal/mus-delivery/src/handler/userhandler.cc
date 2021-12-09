#include "mus-delivery/handler/userhandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"

namespace music_share::delivery {

//UserHandler::UserHandler(IUserUseCase& usecase) : m_usecase(usecase) {}

void UserHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/users";

    router.GET(http::server::router::Route(
        prefix,
        [this](http::common::Request request, auto) {
            auto qs = http::common::QueryString::fromString(
                request.target()
                    .substr(request.target().find('?') + 1)
                    .to_string()
            );

            auto [beg, end] = qs.GetAll("nickname");
            std::vector<std::string> nicknames;
            std::transform(beg, end,
                           std::back_inserter(nicknames),
                           [](auto it) { return it.second; });

            auto users = GetUsers(nicknames);

            http::common::Response response;
            response.body() = nlohmann::json(users).dump();
            return response;
        }, {}
    ));

    router.POST(http::server::router::Route(
        prefix,
        [this, prefix](auto request, auto) {
            auto path = "/" + CreateUser(
                nlohmann::json::parse(request.body())
                    .template get<UserRequestDTO>()
            );

            http::common::Response response;
            response.set(http::common::header::location, prefix + path);
            return response;
        }, {}
    ));

    router.GET(http::server::router::Route(
        prefix + "/:id([0-9]+)",
        [this](auto, auto params) {
            uint32_t id = atoi(params["id"].c_str());
            auto body = GetUserById(id);

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }, {}
    ));

    router.PUT(http::server::router::Route(
        prefix + "/:id([0-9]+)",
        [this](auto, auto params) {
            uint32_t id = atoi(params["id"].c_str());
            auto body = UpdateUserById(id);

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }, {}
    ));
}

std::vector<UserResponseDTO>
UserHandler::GetUsers(const std::vector<std::string>& nicknames) {
    std::vector<UserResponseDTO> res;

    std::ranges::transform(
        nicknames,
        back_inserter(res),
        [](auto it) {
            return UserResponseDTO(1, "", it);
        }
    );

    return res;
}

std::string
UserHandler::CreateUser(const UserRequestDTO& request) {
    return request.username;
}

UserResponseDTO
UserHandler::GetUserById(uint32_t id) {
    return UserResponseDTO(id, "", "");
}

UserResponseDTO
UserHandler::UpdateUserById(uint32_t id) {
    return UserResponseDTO(id, "", "");
}

}  // namespace music_share::delivery
