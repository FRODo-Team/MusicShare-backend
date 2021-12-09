#include "http/server.h"
#include "mus-delivery/handler/userhandler.h"
#include "mus-delivery/handler/songhandler.h"
#include "mus-delivery/handler/chathandler.h"
#include "mus-delivery/handler/chatmessagehandler.h"

using namespace music_share;
using namespace music_share::http::server;
using namespace music_share::http::server::middleware;

int main(void) {
    Server server("localhost", "8080");

    server.Router().Require(MiddlewareBuilder<InternalServerError>::Create());
    server.Router().Require(MiddlewareBuilder<MethodNotAllowed>::Create());
    server.Router().Require(MiddlewareBuilder<NotFound>::Create());

    delivery::UserHandler user_handler;
    user_handler.Config(server.Router());
    delivery::SongHandler song_handler;
    song_handler.Config(server.Router());
    delivery::ChatHandler chat_handler;
    chat_handler.Config(server.Router());
    delivery::ChatMessageHandler chat_message_handler;
    chat_message_handler.Config(server.Router());

    server.Run();

    return 0;
}
