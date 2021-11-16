#ifndef MUS_INTERNAL_MUS_IREPO_IREPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IREPOSITORY_H_

namespace music_share {

template<class T>
class IRepository {
public:
    virtual std::optional<T> Find(uint32_t id) = 0;

    /* В процессе вставки объекта-сущности в базу данных, предполагается, что
     * идентификатор объекта будет задан СУБД автоматически (AUTOINCREMENT).
     * Полученный идентификатор будет занесен в поле m_id текущего c++ объекта,
     * поэтому аргумент передается по неконстантной ссылке.
     */
    virtual void Insert(T& out_entity) = 0;

    virtual void Update(const T&) = 0;
    virtual void Delete(const T&) = 0;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IREPOSITORY_H_
