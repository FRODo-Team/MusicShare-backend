// Oweners: Faris Nabiev, WEB-12
#include "mus-delivery/handler/chathandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"
#include "mus-delivery/middleware/authrequiredmiddleware.h"

namespace music_share::delivery {

ChatHandler::ChatHandler(IChatUseCase& usecase, IAuthUseCase& auth)
    : m_usecase(usecase)
    , m_auth(auth) {}

void ChatHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/chats";

    router.GET(http::server::router::Route(
        prefix,
        [this](http::common::Request request, auto params) {
            uint32_t user_id = ::atoi(params["user_id"].c_str());

            auto qs = http::common::QueryString::fromString(
                request.target()
                    .substr(request.target().find('?') + 1)
                    .to_string()
            );

            std::vector<ChatResponseDTO> body;
            auto companion_it = qs.Get("companionId");
            if (companion_it != qs.Entries().end()) {
                body = GetAll(user_id, atoi(companion_it->second.c_str())); 
            } else {
                body = GetAll(user_id);
            }

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }, { middleware::AuthRequiredMiddlewareBuilder::Create(m_auth) }
    ));

    router.POST(http::server::router::Route(
        prefix,
        [this](http::common::Request request, auto params) {
            std::string path = request
                .target()
                .substr(0, request.target().find('?'))
                .to_string();

            uint32_t id = Create(
                ::atoi(params["user_id"].c_str()),
                nlohmann::json::parse(request.body())
                    .template get<ChatRequestDTO>()
            );

            http::common::Response response;
            response.result(http::common::status::created);
            response.set(http::common::header::location,
                         path + "/" + std::to_string(id));
            return response;
        }, { middleware::AuthRequiredMiddlewareBuilder::Create(m_auth) }
    ));
}

uint32_t
ChatHandler::Create(uint32_t user_id, const ChatRequestDTO& chat) {
    return m_usecase.Create(user_id, chat);
    //return user_id;
}

std::vector<ChatResponseDTO>
ChatHandler::GetAll(uint32_t user_id, std::optional<uint32_t> companion_id) {
    if (companion_id.has_value()) {
        return {m_usecase.GetByIdOfTwoUser(user_id, companion_id.value())};
    }
    return m_usecase.GetByIdOfOneUser(user_id);
    //return {ChatResponseDTO(1, 1, companion_id.has_value() ? companion_id.value() : 1)};
}

}  // namespace music_share::delivery
