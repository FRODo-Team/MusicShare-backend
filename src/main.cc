#include "http/server.h"
#include "mus-repo-postgres/user_repository_postgres.h"
#include "mus-repo-postgres/song_repository_postgres.h"
#include "mus-repo-postgres/chat_repository_postgres.h"
#include "mus-repo-postgres/chat_message_repository_postgres.h"
#include "mus-usecase/user_use_case.h"
#include "mus-usecase/song_use_case.h"
#include "mus-usecase/chat_use_case.h"
#include "mus-usecase/chat_message_use_case.h"
#include "mus-delivery/handler/userhandler.h"
#include "mus-delivery/handler/songhandler.h"
#include "mus-delivery/handler/chathandler.h"
#include "mus-delivery/handler/chatmessagehandler.h"

using namespace music_share;
using namespace music_share::http::server;
using namespace music_share::http::server::middleware;

int main(void) {
    Server server("localhost", "8080");

    std::string c = DatabaseObject::MakeConnectionString(
        "localhost",
        5432,
        "program",
        "test",
        "mus_test"
    );

    UserRepositoryPostgres user_repo(c);
    SongRepositoryPostgres song_repo(c);
    ChatRepositoryPostgres chat_repo(c);
    ChatMessageRepositoryPostgres chat_message_repo(c);

    UserUseCase user_usecase(user_repo);
    SongUseCase song_usecase(song_repo);
    ChatUseCase chat_usecase(chat_repo);
    ChatMessageUseCase chat_message_usecase(chat_message_repo);

    server.Router().Require(MiddlewareBuilder<InternalServerError>::Create());
    server.Router().Require(MiddlewareBuilder<MethodNotAllowed>::Create());
    server.Router().Require(MiddlewareBuilder<NotFound>::Create());

    delivery::UserHandler user_handler(user_usecase);
    user_handler.Config(server.Router());
    delivery::SongHandler song_handler(song_usecase);
    song_handler.Config(server.Router());
    delivery::ChatHandler chat_handler(chat_usecase);
    chat_handler.Config(server.Router());
    delivery::ChatMessageHandler chat_message_handler(chat_message_usecase);
    chat_message_handler.Config(server.Router());

    server.Run();

    return 0;
}
