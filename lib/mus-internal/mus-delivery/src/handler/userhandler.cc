// Oweners: Faris Nabiev, WEB-12
#include "mus-delivery/handler/userhandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"

namespace music_share::delivery {

UserHandler::UserHandler(IUserUseCase& usecase, IAuthUseCase& auth)
    : m_usecase(usecase)
    , m_auth(auth) {}

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
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(users).dump();
            return response;
        }, {}
    ));

    router.POST(http::server::router::Route(
        prefix,
        [this](auto request, auto) {
            std::string path = request
                .target()
                .substr(0, request.target().find('?'))
                .to_string();

            uint32_t id = CreateUser(
                nlohmann::json::parse(request.body())
                    .template get<UserRequestDTO>()
            );

            http::common::Response response;
            response.result(http::common::status::created);
            response.set(http::common::header::location,
                         path + "/" + std::to_string(id));
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
        [this](http::common::Request request, auto params) {
            uint32_t id = atoi(params["id"].c_str());
            auto body = UpdateUserById(id,
                nlohmann::json::parse(request.body())
                    .template get<UserRequestDTO>()
            );

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }, {}
    ));

    router.POST(http::server::router::Route(
        "/api/v1/auth",
        [this](http::common::Request request, auto params) {
            auto session_data = Authenticate(
                nlohmann::json::parse(request.body())
                    .template get<AuthRequestDTO>()
            );

            http::common::Response response;
            if (!session_data) {
                response.result(http::common::status::bad_request);
                return response;
            }

            auto body = GetUserById(session_data->user_id);

            http::common::SetCookie(response, "token",
                                    session_data->session_key);
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();
            return response;
        }
    ));
}

std::vector<UserResponseDTO>
UserHandler::GetUsers(const std::vector<std::string>& nicknames) {
    return m_usecase.GetByNicknames(nicknames);
}

uint32_t
UserHandler::CreateUser(const UserRequestDTO& request) {
    return m_usecase.Create(request);
}

UserResponseDTO
UserHandler::GetUserById(uint32_t id) {
    return m_usecase.GetById(id);
}

UserResponseDTO
UserHandler::UpdateUserById(uint32_t id, const UserRequestDTO& request) {
    return m_usecase.Update(id, request);
}

std::optional<IAuthUseCase::SessionData>
UserHandler::Authenticate(const AuthRequestDTO& request) {
    return m_auth.Authenticate(request);
}

}  // namespace music_share::delivery
