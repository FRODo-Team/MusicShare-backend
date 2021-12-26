#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/ichat_message_use_case.h"
#include "mus-irepo/ichat_message_repository.h"
#include "mus-irepo/ichat_repository.h"
#include "mus-usecase/chat_message_use_case.h"
#include "mus-dto/message_request_dto.h"
#include "mus-dto/message_response_dto.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"
#include "matcher/nullopt_matcher.h"
#include "mock/mock_chat_repository.h"
#include "mock/mock_chat_message_repository.h"

using ::testing::AtLeast;
using testing::Invoke;
using testing::Return;

using std::make_shared;
using std::nullopt;
using std::optional;
using std::shared_ptr;
using std::string;
using std::vector;
using std::make_pair;

using music_share::CreateException;
using music_share::ExistException;
using music_share::InvalidDataException;
using music_share::NullPointerException;
using music_share::IChatMessageRepository;
using music_share::ChatMessage;
using music_share::ChatMessageUseCase;
using music_share::IChatRepository;
using music_share::Chat;

MATCHER_P(ChatMessageEqualement, other,
          "Equality matcher for type ChatMessage") {
    return arg.GetSenderId() == other.GetSenderId();
}

class TestChatMessageUseCase : public ::testing::Test {
protected:
    void SetUp() {
        chat_message_rep = make_shared<MockChatMessageRepository>();
        chat_rep = make_shared<MockChatRepository>();
        chat_message_usecase = make_shared<ChatMessageUseCase>(*chat_message_rep,
                                                               *chat_rep);
        chat_message = make_shared<ChatMessage>(1, "datetime",
                                                "message", 1, 1);
        message_request = make_shared<MessageRequestDTO>("message");
    }

    void TearDown() { }

    shared_ptr<ChatMessageUseCase> chat_message_usecase;
    shared_ptr<MockChatMessageRepository> chat_message_rep;
    shared_ptr<MockChatRepository> chat_rep;
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

TEST_F(TestChatMessageUseCase, SendMessageEmptyDate) {
    uint32_t id_expected = 1;

    EXPECT_CALL(*chat_message_rep, Insert(ChatMessageEqualement(*chat_message)))
            .WillOnce(Invoke([this](ChatMessage& chat_message_out) {
                chat_message_out = *this->chat_message;
            }));

    EXPECT_EQ(chat_message_usecase->SendMessage(*message_request,
                                                1,1,
                                                nullopt), id_expected);
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
    Chat chat(make_pair(1, 2), 1);

    EXPECT_CALL(*chat_message_rep, FindByChatId(1))
            .WillOnce(Return(messages));
    EXPECT_CALL(*chat_rep, Find(1))
            .WillOnce(Return(chat));

    vector<MessageResponseDTO> message_response = chat_message_usecase->GetUserMessages(1,
                                                                                        1);

    EXPECT_EQ(message_response.size(), 1);
    EXPECT_EQ(message_response[0].datetime, message_response_expected.datetime);
    EXPECT_EQ(message_response[0].id, message_response_expected.id);
    EXPECT_EQ(message_response[0].chat_id, message_response_expected.chat_id);
    EXPECT_EQ(message_response[0].content, message_response_expected.content);
}

TEST_F(TestChatMessageUseCase, GetUserMessagesInvalidData) {
    vector<ChatMessage> messages;
    Chat chat(make_pair(1, 2), 1);

    EXPECT_CALL(*chat_message_rep, FindByChatId(1))
            .WillOnce(Return(messages));
    EXPECT_CALL(*chat_rep, Find(1))
            .WillOnce(Return(chat));

    vector<MessageResponseDTO> messages_response = chat_message_usecase->GetUserMessages(1,
                                                                                         1);

    EXPECT_TRUE(messages_response.empty());
}

TEST_F(TestChatMessageUseCase, GetUserMessagesNullPointer) {
    vector<ChatMessage> messages;
    messages.emplace_back(1, "datetime",
                          "message", 1,
                          nullopt);
    Chat chat(make_pair(1, 2), 1);

    EXPECT_CALL(*chat_rep, Find(1))
            .WillOnce(Return(chat));
    EXPECT_CALL(*chat_message_rep, FindByChatId(1))
            .WillOnce(Return(messages));

    EXPECT_THROW(chat_message_usecase->GetUserMessages(1, 1),
                 NullPointerException);
}

TEST_F(TestChatMessageUseCase, GetByUserIdSuccess) {
    MessageResponseDTO message_response_expected(1, 1,
                                                 1, "message",
                                                 "datetime");
    vector<ChatMessage> messages;
    messages.push_back(*chat_message);

    EXPECT_CALL(*chat_message_rep, FindByUserId(1,
                                                NulloptEqualement(nullopt)))
            .WillOnce(Return(messages));

    vector<MessageResponseDTO> message_response = chat_message_usecase->GetByUserId(1,
                                                                                    nullopt);

    EXPECT_EQ(message_response.size(), 1);
    EXPECT_EQ(message_response[0].datetime, message_response_expected.datetime);
    EXPECT_EQ(message_response[0].id, message_response_expected.id);
    EXPECT_EQ(message_response[0].chat_id, message_response_expected.chat_id);
    EXPECT_EQ(message_response[0].content, message_response_expected.content);
}

TEST_F(TestChatMessageUseCase, GetByUserIdInvalidData) {
    vector<ChatMessage> messages;

    EXPECT_CALL(*chat_message_rep, FindByUserId(1,
                                                NulloptEqualement(nullopt)))
            .WillOnce(Return(messages));

    vector<MessageResponseDTO> messages_response = chat_message_usecase->GetByUserId(1,
                                                                                     nullopt);

    EXPECT_TRUE(messages_response.empty());
}

TEST_F(TestChatMessageUseCase, GetByUserIdNullPointer) {
    vector<ChatMessage> messages;
    messages.emplace_back(1, "datetime",
                          "message", 1,
                          nullopt);

    EXPECT_CALL(*chat_message_rep, FindByUserId(1,
                                                NulloptEqualement(nullopt)))
                .WillOnce(Return(messages));

    EXPECT_THROW(chat_message_usecase->GetByUserId(1, nullopt),
                 NullPointerException);
}
