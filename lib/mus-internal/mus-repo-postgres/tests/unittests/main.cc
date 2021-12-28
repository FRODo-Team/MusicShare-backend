// Owners: Rostislav Vivcharuk, WEB-12
#include "test_user_repository_postgres.h"
#include "test_song_repository_postgres.h"
#include "test_playlist_repository_postgres.h"
#include "test_chat_repository_postgres.h"
#include "test_chat_message_repository_postgres.h"
#include "test_session_repository_postgres.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
