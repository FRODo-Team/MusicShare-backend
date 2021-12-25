#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>

#include "mus-repo-postgres/session_repository_postgres.h"

using music_share::DatabaseObject;
using music_share::SessionRepositoryPostgres;
using music_share::Session;

class TestSessionRepositoryPostgres : public ::testing::Test {
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

const std::string TestSessionRepositoryPostgres::s_ConnectionString =
        DatabaseObject::MakeConnectionString("localhost", 5432, "sunz", "123123123", "mus_test_session");

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestSessionRepositoryPostgres::s_TestDatabaseInitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0001_021221_MUS-28_create_tables.sql" },
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0002_021221_MUS-28_populate.sql" }
};

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestSessionRepositoryPostgres::s_TestDatabaseDeinitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/u0001_021221_MUS-28_create_tables.sql" }
};

TEST_F(TestSessionRepositoryPostgres, Insert) {
    // arrange
    Session s(1, "Sesskey", "2020-07-05 14:01:10");

    // act
    auto repo = std::make_unique<SessionRepositoryPostgres>(s_ConnectionString);
    repo->Insert(s);

    // assert
    ASSERT_TRUE(s.GetId().has_value());
}

TEST_F(TestSessionRepositoryPostgres, FindBySessionKey) {
    const std::string sesskey = "Sesskey";

    auto repo = std::make_unique<SessionRepositoryPostgres>(s_ConnectionString);
    auto session = repo->FindBySessionKey(sesskey);

    ASSERT_TRUE(session.has_value());
}