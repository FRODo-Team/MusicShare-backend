#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/ichat_message_use_case.h"
#include "mus-irepo/ichat_message_repository.h"
#include "mus-usecase/chat_message_use_case.h"
#include "mus-dto/message_request_dto.h"
#include "mus-dto/message_response_dto.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using ::testing::AtLeast;
using testing::Invoke;
using testing::Return;

using std::make_shared;
using std::nullopt;
using std::optional;
using std::shared_ptr;
using std::string;
using std::vector;

using music_share::CreateException;
using music_share::ExistException;
using music_share::InvalidDataException;
using music_share::NullPointerException;
using music_share::IChatMessageRepository;
using music_share::ChatMessage;
using music_share::ChatMessageUseCase;

class MockChatMessageRepository : public IChatMessageRepository {
public:
    MOCK_METHOD1(FindByChatId, vector<ChatMessage>(uint32_t));
    MOCK_METHOD1(Find, optional<ChatMessage>(uint32_t));
    MOCK_METHOD1(Insert, void(ChatMessage&));
    MOCK_METHOD1(Update, void(const ChatMessage&));
    MOCK_METHOD1(Delete, void(const ChatMessage&));
};

MATCHER_P(ChatMessageEqualement, other,
          "Equality matcher for type ChatMessage") {
    return arg.GetSenderId() == other.GetSenderId();
}

class TestChatMessageUseCase : public ::testing::Test {
protected:
    void SetUp() {
        chat_message_rep = make_shared<MockChatMessageRepository>();
        chat_message_usecase = make_shared<ChatMessageUseCase>(*chat_message_rep);
        chat_message = make_shared<ChatMessage>(1, "datetime",
                                                "message", 1, 1);
        message_request = make_shared<MessageRequestDTO>("message");
    }

    void TearDown() { }

    shared_ptr<ChatMessageUseCase> chat_message_usecase;
    shared_ptr<MockChatMessageRepository> chat_message_rep;
    shared_ptr<ChatMessage> chat_message;
    shared_ptr<MessageRequestDTO> message_request;
};

TEST_F(TestChatMessageUseCase, SendMessageSuccess) {
    uint32_t id_expected = 1;

    EXPECT_CALL(*chat_message_rep, Insert(ChatMessageEqualement(*chat_message)))
            .WillOnce(Invoke([this](ChatMessage& chat_message_out) {
                chat_message_out = *this->chat_message;
            }));

    EXPECT_EQ(chat_message_usecase->SendMessage(*message_request,
                                                1,1,
                                                "datetime"), id_expected);
}

TEST_F(TestChatMessageUseCase, SendMessageException) {
    EXPECT_CALL(*chat_message_rep, Insert(ChatMessageEqualement(*chat_message)))
            .Times(AtLeast(1));

    EXPECT_THROW(chat_message_usecase->SendMessage(*message_request,
                                                   1, 1,
                                                   "datetime"), CreateException);
}

TEST_F(TestChatMessageUseCase, GetUserMessagesSuccess) {
    MessageResponseDTO message_response_expected(1, 1,
                                                 1, "message",
                                                 "datetime");
    vector<ChatMessage> messages;
    messages.push_back(*chat_message);

    EXPECT_CALL(*chat_message_rep, FindByChatId(1))
            .WillOnce(Return(messages));

    vector<MessageResponseDTO> message_response = chat_message_usecase->GetUserMessages(1, 1);

    EXPECT_EQ(message_response.size(), 1);
    EXPECT_EQ(message_response[0].datetime, message_response_expected.datetime);
    EXPECT_EQ(message_response[0].id, message_response_expected.id);
    EXPECT_EQ(message_response[0].chat_id, message_response_expected.chat_id);
    EXPECT_EQ(message_response[0].content, message_response_expected.content);
}

TEST_F(TestChatMessageUseCase, GetUserMessagesInvalidData) {
    vector<ChatMessage> messages;

    EXPECT_CALL(*chat_message_rep, FindByChatId(1))
            .WillOnce(Return(messages));

    EXPECT_THROW(chat_message_usecase->GetUserMessages(1, 1),
                 InvalidDataException);
}

TEST_F(TestChatMessageUseCase, GetUserMessagesNullPointer) {
    vector<ChatMessage> messages;
    messages.emplace_back(1, "datetime",
                          "message", 1,
                          nullopt);

    EXPECT_CALL(*chat_message_rep, FindByChatId(1))
            .WillOnce(Return(messages));

    EXPECT_THROW(chat_message_usecase->GetUserMessages(1, 1),
                 NullPointerException);
}