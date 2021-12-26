#ifndef MUS_INTERNAL_MOCK_MOCK_USER_USECAS_H
#define MUS_INTERNAL_MOCK_MOCK_USER_USECAS_H

#include <gmock/gmock.h>
#include <optional>
#include <cstdint>
#include <string>
#include <vector>

#include "mus-irepo/iuser_repository.h"
#include "mus-models/user.h"

using std::string;
using std::optional;
using std::vector;

using music_share::IUserRepository;
using music_share::User;

class MockUserRepository : public IUserRepository {
public:
    MOCK_METHOD1(FindByNickname, vector<User>(const string&));
    MOCK_METHOD1(FindByUsername, optional<User>(const string&));
    MOCK_METHOD1(FindByEmail, optional<User>(const string&));
    MOCK_METHOD1(Find, optional<User>(uint32_t));
    MOCK_METHOD1(Insert, void(User&));
    MOCK_METHOD1(Update, void(const User&));
    MOCK_METHOD1(Delete, void(const User&));
    MOCK_METHOD1(FetchAll, vector<User>(optional<uint32_t>));
};

#endif  // MUS_INTERNAL_MOCK_MOCK_USER_USECAS_H
