#ifndef MUS_INTERNAL_MOCK_MOCK_CHAT_REPOSITORY_H
#define MUS_INTERNAL_MOCK_MOCK_CHAT_REPOSITORY_H

#include <gmock/gmock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "mus-irepo/ichat_repository.h"
#include "mus-models/chat.h"

using music_share::IChatRepository;
using music_share::Chat;
using std::string;
using std::optional;
using std::vector;

class MockChatRepository : public IChatRepository {
public:
    MOCK_METHOD1(FindByUserId, vector<Chat>(uint32_t));
    MOCK_METHOD2(FindByIdsOfUserPair, optional<Chat>(uint32_t, uint32_t));
    MOCK_METHOD1(Find, optional<Chat>(uint32_t));
    MOCK_METHOD1(Insert, void(Chat&));
    MOCK_METHOD1(Update, void(const Chat&));
    MOCK_METHOD1(Delete, void(const Chat&));
};

#endif  // MUS_INTERNAL_MOCK_MOCK_CHAT_REPOSITORY_H
