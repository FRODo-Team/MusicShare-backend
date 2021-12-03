#include "test_user_repository_postgres.h"
#include "test_song_repository_postgres.h"
//#include "test_playlist_repository_postgres.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
