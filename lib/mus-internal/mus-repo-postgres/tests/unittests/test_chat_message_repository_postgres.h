#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>

#include "mus-repo-postgres/chat_message_repository_postgres.h"

using music_share::ChatMessageRepositoryPostgres;
using music_share::ChatMessage;
using music_share::DatabaseObject;

class TestChatMessageRepositoryPostgres : public ::testing::Test {
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

const std::string TestChatMessageRepositoryPostgres::s_ConnectionString =
        DatabaseObject::MakeConnectionString("localhost", 5432, "sunz", "123123123", "mus_test_chat_message");

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestChatMessageRepositoryPostgres::s_TestDatabaseInitSqlScripts = {
        std::string{ "/home/sunz/uni/MusicShare-backend/db/postgres/migrations/v0001_021221_MUS-28_create_tables.sql" },
        std::string{ "/home/sunz/uni/MusicShare-backend/db/postgres/migrations/v0002_021221_MUS-28_populate.sql" }
};

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestChatMessageRepositoryPostgres::s_TestDatabaseDeinitSqlScripts = {
        std::string{ "/home/sunz/uni/MusicShare-backend/db/postgres/migrations/u0001_021221_MUS-28_create_tables.sql" }
};

TEST_F(TestChatMessageRepositoryPostgres, FindNotExistingChatMessage) {
    // arrange
    uint32_t message_id_to_find = 1028374;

    // act
    auto repo = std::make_unique<ChatMessageRepositoryPostgres>(s_ConnectionString);
    std::optional<ChatMessage> actual_msg = repo->Find(message_id_to_find);

    // assert
    ASSERT_FALSE(actual_msg.has_value());
}

TEST_F(TestChatMessageRepositoryPostgres, Insert) {
    ChatMessage msg_to_insert(1, "2018-1-05 14:01:10-08", "look at this duuuuude", 1);
    ChatMessage expected_msg(1, "2018-1-05 14:01:10-08", "look at this duuuuude", 1, 10);

    auto repo = std::make_unique<ChatMessageRepositoryPostgres>(s_ConnectionString);
    repo->Insert(msg_to_insert);

    ASSERT_EQ(expected_msg.GetId(), msg_to_insert.GetId());
    ASSERT_EQ(expected_msg.GetChatId(), msg_to_insert.GetChatId());
    ASSERT_STREQ(expected_msg.GetContent().c_str(), msg_to_insert.GetContent().c_str());
    ASSERT_STREQ(expected_msg.GetDatetime().c_str(), msg_to_insert.GetDatetime().c_str());
    ASSERT_EQ(expected_msg.GetSenderId(), msg_to_insert.GetSenderId());
}

TEST_F(TestChatMessageRepositoryPostgres, Find) {
    uint32_t id = 1;
    ChatMessage expected_msg(1, "2018-01-05 14:01:10", "look at this duuuuude", 1, id);

    auto repo = std::make_unique<ChatMessageRepositoryPostgres>(s_ConnectionString);
    auto actual_msg = repo->Find(id);

    ASSERT_TRUE(actual_msg.has_value()) ;
    if (actual_msg.has_value()) {
        const auto& msg = actual_msg.value();
        ASSERT_EQ(expected_msg.GetId(), msg.GetId());
        ASSERT_EQ(expected_msg.GetChatId(), msg.GetChatId());
        ASSERT_STREQ(expected_msg.GetContent().c_str(), msg.GetContent().c_str());
        ASSERT_STREQ(expected_msg.GetDatetime().c_str(), msg.GetDatetime().c_str());
        ASSERT_EQ(expected_msg.GetSenderId(), msg.GetSenderId());
    }
}
