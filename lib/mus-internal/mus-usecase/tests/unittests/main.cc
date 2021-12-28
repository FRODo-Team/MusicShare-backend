// Oweners: Darya Vlaskina, ML-13
#include <gtest/gtest.h>

#include "test_chat_message_use_case.h"
#include "test_chat_use_case.h"
#include "test_playlist_use_case.h"
#include "test_song_use_case.h"
#include "test_user_use_case.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
