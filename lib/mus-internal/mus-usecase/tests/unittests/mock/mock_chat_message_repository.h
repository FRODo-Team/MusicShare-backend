#ifndef MUS_INTERNAL_MOCK_MOCK_CHAT_MESSAGE_REPOSITORY_H
#define MUS_INTERNAL_MOCK_MOCK_CHAT_MESSAGE_REPOSITORY_H

#include <gmock/gmock.h>
#include <optional>
#include <cstdint>
#include <string>
#include <vector>

#include "mus-irepo/ichat_message_repository.h"
#include "mus-models/chat_message.h"

using music_share::IChatMessageRepository;
using music_share::ChatMessage;
using std::string;
using std::optional;
using std::vector;

class MockChatMessageRepository : public IChatMessageRepository {
public:
    MOCK_METHOD1(FindByChatId, vector<ChatMessage>(uint32_t));
    MOCK_METHOD1(Find, optional<ChatMessage>(uint32_t));
    MOCK_METHOD1(Insert, void(ChatMessage&));
    MOCK_METHOD1(Update, void(const ChatMessage&));
    MOCK_METHOD1(Delete, void(const ChatMessage&));
    MOCK_METHOD2(FindByUserId, vector<ChatMessage>(uint32_t, optional<string>));
};

#endif  // MUS_INTERNAL_MOCK_MOCK_CHAT_MESSAGE_REPOSITORY_H
