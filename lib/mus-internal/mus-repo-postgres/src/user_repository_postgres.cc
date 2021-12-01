#include <cassert>
#include "mus-repo-postgres/user_repository_postgres.h"


namespace music_share {

UserRepositoryPostgres::UserRepositoryPostgres(const std::string& connection)
        : m_database(connection) { }

std::optional<User> UserRepositoryPostgres::Find(uint32_t id) {
    std::string query = "SELECT * FROM " + std::string(kTableName) + " "
                        "WHERE id=" + std::to_string(id);

    auto response = m_database.ExecuteQuery(query);
    if (response.empty()) {
        return std::nullopt;
    }

    return Mapper::ToDomainObject(response[0]);
}

void UserRepositoryPostgres::Insert(User& out_user) {
    SqlObject o = Mapper::ToSqlObject(out_user);
    auto[attributes, values] = DbUtils::SqlObjectToQueryableInsertStrings(o);

    std::string query =
            "INSERT INTO " + std::string(kTableName) + attributes + " " +
            "VALUES " + values;

   m_database.ExecuteQuery(query);

   /* TODO (sunz):
    * По хорошему, нужно сделать SQL-транзакцию в рамках этого метода, и следующим
    * запросом достать ID последней добавленной записи.
    * В случае с пользователем, можно сделать запрос по никнейму, т.к он уникален,
    * но не все таблицы имеют уникальные параметры, соответственно с ними так
    * не получится. */

    query = "SELECT id FROM " + std::string(kTableName) + " " +
            "WHERE username=" +
            DbUtils::ValueToSqlFormat(out_user.GetUsername());

    auto result = m_database.ExecuteQuery(query);
    assert(!result.empty());

    auto id = result[0][0].as<uint32_t>();
    User updated = User(out_user, id);
    out_user = updated;
}

void UserRepositoryPostgres::Update(const User& user) {
    SqlObject o = Mapper::ToSqlObject(user);
    std::string update_data = DbUtils::SqlObjectToQueryableUpdateString(o);

    std::string query =
            "UPDATE " + std::string(kTableName) + " "
            "SET " + update_data + " " +
            "WHERE id=" + o["id"];

    m_database.ExecuteQuery(query);
}

void UserRepositoryPostgres::Delete(const User& user) {
    if (user.GetId().has_value()) {
        std::string query =
                "DELETE FROM " + std::string(kTableName) + " "
                "WHERE id=" + std::to_string(user.GetId().value());

        m_database.ExecuteQuery(query);
    }
}

std::vector<User> UserRepositoryPostgres::FindByNickname(
        const std::string& nickname)
{
    std::string query =
            "SELECT * FROM " + std::string(kTableName) + " " +
            "WHERE nickname=" + DbUtils::ValueToSqlFormat(nickname);

    pqxx::result response = m_database.ExecuteQuery(query);

    std::vector<User> result;
    for (const auto& row: response) {
        User u = Mapper::ToDomainObject(row);
        result.push_back(u);
    }

    return result;
}

std::optional<User> UserRepositoryPostgres::FindByUsername(
        const std::string& username)
{
    std::string query =
            "SELECT * FROM " + std::string(kTableName) + " " +
            "WHERE username=" + DbUtils::ValueToSqlFormat(username);

    pqxx::result response = m_database.ExecuteQuery(query);
    if (response.empty()) {
        return std::nullopt;
    }

    return Mapper::ToDomainObject(response[0]);
}

std::optional<User> UserRepositoryPostgres::FindByEmail(
        const std::string& email)
{
    std::string query =
            "SELECT * FROM " + std::string(kTableName) + " " +
            "WHERE email=" + DbUtils::ValueToSqlFormat(email);

    pqxx::result response = m_database.ExecuteQuery(query);
    if (response.empty()) {
        return std::nullopt;
    }

    return Mapper::ToDomainObject(response[0]);

}

User UserRepositoryPostgres::Mapper::ToDomainObject(const pqxx::row& record) {
    uint32_t id;
    std::string nickname;
    std::string email;
    std::string username;
    std::string password_hash;
    User::AccessLevel access_level;

    for (const auto& column: record) {
        if (column.name() == std::string{ "id" }) {
            id = column.as<uint32_t>();
        } else if (column.name() == std::string{ "nickname" }) {
            nickname = column.as<std::string>();
        } else if (column.name() == std::string{ "email" }) {
            email = column.as<std::string>();
        } else if (column.name() == std::string{ "username" }) {
            username = column.as<std::string>();
        } else if (column.name() == std::string{ "password_hash" }) {
            password_hash = column.as<std::string>();
        } else if (column.name() == std::string{ "access_level" }) {
            access_level = static_cast<User::AccessLevel>(column.as<int>());
        }
    }

    return { nickname, email, username, password_hash, access_level, id };
}

SqlObject UserRepositoryPostgres::Mapper::ToSqlObject(const User& domain) {
    SqlObject result;

    if (domain.GetId().has_value()) {
        result["id"] = DbUtils::ValueToSqlFormat(domain.GetId().value());
    }
    result["nickname"] = DbUtils::ValueToSqlFormat(domain.GetNickname());
    result["email"] = DbUtils::ValueToSqlFormat(domain.GetEmail());
    result["username"] = DbUtils::ValueToSqlFormat(domain.GetUsername());
    result["password_hash"] =
            DbUtils::ValueToSqlFormat(domain.GetPasswordHash());
    result["access_level"] =
            DbUtils::ValueToSqlFormat(static_cast<int>(domain.GetAccessLevel()));

    return result;
}

} // namespace music_share
