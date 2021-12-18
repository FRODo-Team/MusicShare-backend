#include "mus-delivery/handler/chathandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"

namespace music_share::delivery {

ChatHandler::ChatHandler(IChatUseCase& usecase)
    : m_usecase(usecase) {}

void ChatHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/chats";

    router.GET(http::server::router::Route(
        prefix,
        [this](http::common::Request request, auto) {
            auto qs = http::common::QueryString::fromString(
                request.target()
                    .substr(request.target().find('?') + 1)
                    .to_string()
            );

            std::vector<ChatResponseDTO> body;
            auto companion_it = qs.Get("companionId");
            if (companion_it != qs.Entries().end()) {
                body = GetAll(atoi(companion_it->second.c_str())); 
            } else {
                body = GetAll();
            }

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }
    ));

    router.POST(http::server::router::Route(
        prefix,
        [this, prefix](http::common::Request request, auto params) {
            uint32_t id = Create(1,
                nlohmann::json::parse(request.body())
                    .template get<ChatRequestDTO>()
            );

            http::common::Response response;
            response.result(http::common::status::created);
            response.set(http::common::header::location,
                         prefix + "/" + std::to_string(id));
            return response;
        }
    ));
}

uint32_t
ChatHandler::Create(uint32_t user_id, const ChatRequestDTO& chat) {
    return m_usecase.Create(user_id, chat);
    //return user_id;
}

std::vector<ChatResponseDTO>
ChatHandler::GetAll(std::optional<uint32_t> companion_id) {
    if (companion_id.has_value()) {
        return {m_usecase.GetByIdOfTwoUser(1, companion_id.value())};
    }
    return m_usecase.GetByIdOfOneUser(1);
    //return {ChatResponseDTO(1, 1, companion_id.has_value() ? companion_id.value() : 1)};
}

}  // namespace music_share::delivery
