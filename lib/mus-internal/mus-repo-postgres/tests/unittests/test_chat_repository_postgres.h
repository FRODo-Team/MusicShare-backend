#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>

#include "mus-repo-postgres/chat_repository_postgres.h"

using music_share::ChatRepositoryPostgres;
using music_share::Chat;
using music_share::DatabaseObject;

class TestChatRepositoryPostgres : public ::testing::Test {
public:
    static void SetUpTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseInitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test database setup script");
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string query = buffer.str();
            dbo.ExecuteQuery(query);
        }
    }

    static void TearDownTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseDeinitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test database teardown script");
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string query = buffer.str();
            dbo.ExecuteQuery(query);
        }
    }

protected:
    static const std::string s_ConnectionString;
    static const std::vector<std::string> s_TestDatabaseInitSqlScripts;
    static const std::vector<std::string> s_TestDatabaseDeinitSqlScripts;
};

const std::string TestChatRepositoryPostgres::s_ConnectionString =
        DatabaseObject::MakeConnectionString("localhost", 5432, "sunz", "123123123", "mus_test_chat");

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestChatRepositoryPostgres::s_TestDatabaseInitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0001_021221_MUS-28_create_tables.sql" },
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0002_021221_MUS-28_populate.sql" }
};

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestChatRepositoryPostgres::s_TestDatabaseDeinitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/u0001_021221_MUS-28_create_tables.sql" }
};


TEST_F(TestChatRepositoryPostgres, FindNotExistingChat) {
    // arrange
    uint32_t chat_id_to_find = 1028374;

    // act
    auto repo = std::make_unique<ChatRepositoryPostgres>(s_ConnectionString);
    std::optional<Chat> actual_chat = repo->Find(chat_id_to_find);

    // assert
    ASSERT_FALSE(actual_chat.has_value());
}

TEST_F(TestChatRepositoryPostgres, Insert) {
    Chat expected_chat(1, 5, 5);
    Chat chat_to_insert(std::make_pair(1, 5));

    auto repo = std::make_unique<ChatRepositoryPostgres>(s_ConnectionString);
    repo->Insert(chat_to_insert);

    // assert
    ASSERT_EQ(expected_chat.GetUserIds().first,
              chat_to_insert.GetUserIds().first);

    ASSERT_EQ(expected_chat.GetUserIds().second,
              chat_to_insert.GetUserIds().second);

    ASSERT_EQ(expected_chat.GetId(), chat_to_insert.GetId());
}

TEST_F(TestChatRepositoryPostgres, Find) {
    const uint32_t id = 5;
    Chat expected_chat(1, 5, id);

    auto repo = std::make_unique<ChatRepositoryPostgres>(s_ConnectionString);
    auto actual_chat = repo->Find(id);

    ASSERT_TRUE(actual_chat.has_value());
    if (actual_chat.has_value()) {
        ASSERT_EQ(expected_chat.GetUserIds().first,
                  actual_chat->GetUserIds().first);

        ASSERT_EQ(expected_chat.GetUserIds().second,
                  actual_chat->GetUserIds().second);

        ASSERT_EQ(expected_chat.GetId(), actual_chat->GetId());
    }
}

TEST_F(TestChatRepositoryPostgres, Delete) {
    const uint32_t id = 5;
    Chat chat_to_delete(1, 5, id);

    auto repo = std::make_unique<ChatRepositoryPostgres>(s_ConnectionString);
    repo->Delete(chat_to_delete);

    auto actual_chat = repo->Find(id);
    ASSERT_FALSE(actual_chat.has_value());
}

TEST_F(TestChatRepositoryPostgres, FindByUserId) {
    const uint32_t user_id = 2;

    std::vector<Chat> expected_chats = {
            Chat(1, 2, 1),
            Chat(2, 3, 2)
    };

    auto repo = std::make_unique<ChatRepositoryPostgres>(s_ConnectionString);
    std::vector<Chat> actual_chats = repo->FindByUserId(user_id);

    ASSERT_TRUE(actual_chats.size() == 2);
    for (size_t i = 0; i < actual_chats.size(); ++i) {
        const auto& expected_chat = actual_chats[i];
        const auto& actual_chat = expected_chats[i];

        ASSERT_EQ(expected_chat.GetUserIds().first,
                  actual_chat.GetUserIds().first);

        ASSERT_EQ(expected_chat.GetUserIds().second,
                  actual_chat.GetUserIds().second);

        ASSERT_EQ(expected_chat.GetId(), actual_chat.GetId());
    }
}

TEST_F(TestChatRepositoryPostgres, FindByIdsOfUserPair) {
    const Chat expected_chat(1, 3, 3);

    auto repo = std::make_unique<ChatRepositoryPostgres>(s_ConnectionString);
    std::optional<Chat> actual_chat = repo->FindByIdsOfUserPair(1, 3);

    ASSERT_TRUE(actual_chat.has_value());
    if (actual_chat.has_value()) {
        if (actual_chat.has_value()) {
            ASSERT_EQ(expected_chat.GetUserIds().first,
                      actual_chat->GetUserIds().first);

            ASSERT_EQ(expected_chat.GetUserIds().second,
                      actual_chat->GetUserIds().second);

            ASSERT_EQ(expected_chat.GetId(), actual_chat->GetId());
        }
    }
}
