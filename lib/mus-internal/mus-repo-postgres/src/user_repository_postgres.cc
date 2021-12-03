#include <cassert>
#include "mus-repo-postgres/user_repository_postgres.h"


namespace music_share {

UserRepositoryPostgres::UserRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, "mus_user"),
        m_table_name(m_crud_repository.GetTableName()) { }


std::optional<User> UserRepositoryPostgres::Find(uint32_t id) {
    return m_crud_repository.Find(id);
}

void UserRepositoryPostgres::Insert(User& out_obj) {
    return m_crud_repository.Insert(out_obj);
}

void UserRepositoryPostgres::Update(const User& obj) {
    return m_crud_repository.Update(obj);
}

void UserRepositoryPostgres::Delete(const User& obj) {
    return m_crud_repository.Delete(obj);
}

std::optional<User> UserRepositoryPostgres::FindByUsername(
        const std::string& username)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE username=" + SqlUtils::ValueToSqlFormat(username);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    if (response.empty()) {
        return { };
    }

    return SqlMapper::ToDomainObject(response[0]);
}

std::optional<User> UserRepositoryPostgres::FindByEmail(
        const std::string& email)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE email=" + SqlUtils::ValueToSqlFormat(email);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    if (response.empty()) {
        return { };
    }

    return SqlMapper::ToDomainObject(response[0]);
}

std::vector<User> UserRepositoryPostgres::FindByNickname(
        const std::string& nickname)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE nickname=" + SqlUtils::ValueToSqlFormat(nickname);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<User> result;
    for (const auto& row: response) {
        User u = SqlMapper::ToDomainObject(row);
        result.push_back(u);
    }

    return result;
}

User UserRepositoryPostgres::SqlMapper::ToDomainObject(const pqxx::row& row) {
    std::string username;
    std::string email;
    std::string password_hash;
    std::string nickname;
    User::AccessLevel access_level;
    uint32_t id;

    for (const auto& field: row) {
        if (field.name() == std::string{ "id" }) {
            id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "nickname" }) {
            nickname = field.as<std::string>();
        } else if (field.name() == std::string{ "email" }) {
            email = field.as<std::string>();
        } else if (field.name() == std::string{ "username" }) {
            username = field.as<std::string>();
        } else if (field.name() == std::string{ "password_hash" }) {
            password_hash = field.as<std::string>();
        } else if (field.name() == std::string{ "access_level" }) {
            access_level = static_cast<User::AccessLevel>(field.as<int>());
        }
    }

    return { username, email, password_hash, nickname, access_level, id };
}

SqlObject UserRepositoryPostgres::SqlMapper::ToSqlObject(const User& domain) {
    SqlObject result;

    result["nickname"] = SqlUtils::ValueToSqlFormat(domain.GetNickname());
    result["email"] = SqlUtils::ValueToSqlFormat(domain.GetEmail());
    result["username"] = SqlUtils::ValueToSqlFormat(domain.GetUsername());
    result["password_hash"] =
            SqlUtils::ValueToSqlFormat(domain.GetPasswordHash());
    result["access_level"] =
            SqlUtils::ValueToSqlFormat(static_cast<int>(domain.GetAccessLevel()));
    if (domain.GetId().has_value()) {
        result["id"] = SqlUtils::ValueToSqlFormat(domain.GetId().value());
    }

    return result;
}

} // namespace music_share
