// Oweners: Faris Nabiev, WEB-12
#include "mus-delivery/handler/chatmessagehandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"
#include "mus-delivery/middleware/authrequiredmiddleware.h"

namespace music_share::delivery {

ChatMessageHandler::ChatMessageHandler(IChatMessageUseCase& usecase,
                                       IAuthUseCase& auth)
    : m_usecase(usecase)
    , m_auth(auth) {}

void ChatMessageHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/chats/:chat_id([0-9]+)/messages";

    router.GET(http::server::router::Route(
        prefix,
        [this](auto, auto params) {
            auto body = GetUserMessages(
                ::atoi(params["user_id"].c_str()),
                ::atoi(params["chat_id"].c_str())
            );

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
            (void)SendMessage(
                nlohmann::json::parse(request.body())
                    .template get<MessageRequestDTO>(),
                ::atoi(params["chat_id"].c_str()),
                ::atoi(params["user_id"].c_str())
            );

            http::common::Response response;
            return response;
        }, { middleware::AuthRequiredMiddlewareBuilder::Create(m_auth) }
    ));

    router.GET(http::server::router::Route(
        "/api/v1/users/messages",
        [this](http::common::Request request, auto params) {
            auto qs = http::common::QueryString::fromString(
                request.target()
                    .substr(request.target().find('?') + 1)
                    .to_string()
            );

            std::vector<std::string> since_dates;
            auto [tbeg, tend] = qs.GetAll("since");
            std::transform(tbeg, tend,
                           std::back_inserter(since_dates),
                           [](auto it) { return it.second; });

            std::optional<std::string> since_date;
            if (!since_dates.empty()) {
                since_date = since_dates[0];
            }

            auto body = GetMessagesByUser(
                ::atoi(params["user_id"].c_str()),
                since_date
            );

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();
            return response;
        }, { middleware::AuthRequiredMiddlewareBuilder::Create(m_auth) }
    ));
}

uint32_t
ChatMessageHandler::SendMessage(const MessageRequestDTO& message,
                              uint32_t chat_id, uint32_t user_id) {
    return m_usecase.SendMessage(message, chat_id, user_id);
}

std::vector<MessageResponseDTO>
ChatMessageHandler::GetUserMessages(uint32_t user_id,
                                    uint32_t chat_id) {
    return m_usecase.GetUserMessages(user_id, chat_id);
}

std::vector<MessageResponseDTO>
ChatMessageHandler::GetMessagesByUser(uint32_t user_id,
                                      std::optional<std::string> since_date) {
    return m_usecase.GetByUserId(user_id, since_date);
}

}  // namespace music_share::delivery
