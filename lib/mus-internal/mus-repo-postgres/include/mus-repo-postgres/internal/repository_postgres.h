#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_REPOSITORY_POSTGRES
#define MUS_INTERNAL_MUS_REPO_POSTGRES_REPOSITORY_POSTGRES

#include "mus-irepo/irepository.h"
#include "database_object.h"
#include "sql_utils.h"


namespace music_share {

/*
 * Реализация шаблонного CRUD-репозитория под postgres.
 * Все реализации репозиториев для конкретных доменных моделей
 * включают в себя (композиция) объект данного класса.
 */

/*
 * Параметр шаблона SqlMapper обязан реализовывать 2 статических метода со
 * следующими сигнатурами:
 *
 * static DomainType ToDomainObject(const pqxx::row& row);
 * static SqlObject ToSqlObject(const DomainType& domain);
 *
 * Для конвертации sql-объектов в доменные и наоборот.
 */

template<class DomainType, class SqlMapper>
class RepositoryPostgres : public IRepository<DomainType> {
public:
    RepositoryPostgres(const std::string& connection_string,
                       const std::string& table_name)
        :
        m_database(connection_string),
        m_table_name(table_name) { }

    RepositoryPostgres(const RepositoryPostgres&) = delete;
    virtual ~RepositoryPostgres() = default;

    RepositoryPostgres& operator=(const RepositoryPostgres&) = delete;

    const std::string& GetTableName() const { return m_table_name; }

    const std::string& GetConnectionString() const {
        return m_database.GetConnectionString();
    }

    pqxx::result ExecuteQuery(const std::string& query) {
        return m_database.ExecuteQuery(query);
    }

    std::optional<DomainType> Find(uint32_t id) override {
        std::string query = "SELECT * FROM " + m_table_name + " "
                            "WHERE id=" + std::to_string(id);

        auto response = m_database.ExecuteQuery(query);
        if (response.empty()) {
            return { };
        }

        return SqlMapper::ToDomainObject(response[0]);
    }

    void Insert(DomainType& out_obj) override {
        SqlObject sql_obj = SqlMapper::ToSqlObject(out_obj);
        auto[attributes, values] =
                SqlUtils::SqlObjectToQueryableInsertStrings(sql_obj);

        std::string query =
                "INSERT INTO " + m_table_name + attributes + " " +
                "VALUES " + values + " " +
                "RETURNING id";

        pqxx::result response = m_database.ExecuteQuery(query);
        assert(!response.empty());
        auto id = response[0][0].as<uint32_t>();

        DomainType inserted = DomainType(out_obj, id);
        out_obj = inserted;
    }

    void Update(const DomainType& obj) override {
        SqlObject o = SqlMapper::ToSqlObject(obj);
        std::string update_data = SqlUtils::SqlObjectToQueryableUpdateString(o);

        std::string query =
                "UPDATE " + m_table_name + " " +
                "SET " + update_data + " " +
                "WHERE id=" + o["id"];

        m_database.ExecuteQuery(query);
    }

    void Delete(const DomainType& obj) override {
        if (obj.GetId().has_value()) {
            std::string query =
                    "DELETE FROM " + m_table_name + " " +
                    "WHERE id=" + std::to_string(obj.GetId().value());

            m_database.ExecuteQuery(query);
        }
    }

protected:
    DatabaseObject m_database;
    const std::string m_table_name;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_REPOSITORY_POSTGRES
