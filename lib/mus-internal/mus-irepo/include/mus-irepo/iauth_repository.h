#ifndef MUS_INTERNAL_MUS_IREPO_IAUTH_REPOSITORY_H_
#define MUS_INTERNAL_MUS_IREPO_IAUTH_REPOSITORY_H_

namespace music_share {

/*
    Возможно и вовсе реализуем авторизацию через репозиторий юзера, и данный
    будет не нужен. Но, после того как определимся со спецификой.
    Пока что этот интерфейс будет пустым.
*/

class IAuthRepository {
public:
    IAuthRepository() = default;
    ~IAuthRepository() = default;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_IREPO_IAUTH_REPOSITORY_H_
