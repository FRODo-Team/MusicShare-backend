#include "http/server.h"
#include "config-parser/config.h"
#include "mus-repo-postgres/user_repository_postgres.h"
#include "mus-repo-postgres/song_repository_postgres.h"
#include "mus-repo-postgres/playlist_repository_postgres.h"
#include "mus-repo-postgres/chat_repository_postgres.h"
#include "mus-repo-postgres/chat_message_repository_postgres.h"
#include "mus-usecase/user_use_case.h"
#include "mus-usecase/song_use_case.h"
#include "mus-usecase/playlist_use_case.h"
#include "mus-usecase/chat_use_case.h"
#include "mus-usecase/chat_message_use_case.h"
#include "mus-delivery/handler/userhandler.h"
#include "mus-delivery/handler/songhandler.h"
#include "mus-delivery/handler/playlisthandler.h"
#include "mus-delivery/handler/chathandler.h"
#include "mus-delivery/handler/chatmessagehandler.h"

using namespace music_share;
using namespace music_share::http::server;
using namespace music_share::http::server::middleware;

int main(void) {
    config_parser::Config conf("mus_app");
    auto db_conf = conf["db"];

    Server server(conf["host"].Get<std::string>(), conf["port"].Get<std::string>());

    std::string c = DatabaseObject::MakeConnectionString(
        db_conf["host"].Get<std::string>(),
        db_conf["port"].Get<int>(),
        db_conf["user"].Get<std::string>(),
        db_conf["password"].Get<std::string>(),
        db_conf["database"].Get<std::string>()
    );
    //config_parser::Config conf("mus_app");

    //Server server(conf["host"].Get<std::string>(), conf["port"].Get<std::string>());

    //std::string c = DatabaseObject::MakeConnectionString(
        //"localhost",
        //5432,
        //"program",
        //"test",
        //"mus_test"
    //);

    UserRepositoryPostgres user_repo(c);
    SongRepositoryPostgres song_repo(c);
    PlaylistRepositoryPostgres playlist_repo(c);
    ChatRepositoryPostgres chat_repo(c);
    ChatMessageRepositoryPostgres chat_message_repo(c);

    UserUseCase user_usecase(user_repo);
    SongUseCase song_usecase(song_repo);
    PlaylistUseCase playlist_usecase(playlist_repo);
    ChatUseCase chat_usecase(chat_repo);
    ChatMessageUseCase chat_message_usecase(chat_message_repo);

    server.Router().Require(MiddlewareBuilder<InternalServerError>::Create());
    server.Router().Require(MiddlewareBuilder<MethodNotAllowed>::Create());
    server.Router().Require(MiddlewareBuilder<NotFound>::Create());

    delivery::UserHandler user_handler(user_usecase);
    delivery::SongHandler song_handler(song_usecase);
    delivery::PlaylistHandler playlist_handler(playlist_usecase);
    delivery::ChatHandler chat_handler(chat_usecase);
    delivery::ChatMessageHandler chat_message_handler(chat_message_usecase);

    user_handler.Config(server.Router());
    song_handler.Config(server.Router());
    playlist_handler.Config(server.Router());
    chat_handler.Config(server.Router());
    chat_message_handler.Config(server.Router());

    server.Run();

    return 0;
}
