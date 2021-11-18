#ifndef TESTS_INTTESTS_TEST_CHAT_USE_CASE_H_
#define TESTS_INTTESTS_TEST_CHAT_USE_CASE_H_

#include "gtest/gtest.h"

#include <memory>
#include <vector>

#include "mus-irepo/ichat_repository.h"
#include "mus-usecase/chat_use_case.h"
#include "mus-dto/chat_request_dto.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using music_share::IChatRepository;
using music_share::IChatMessageRepository;
using std::optional;
using std::nullopt;
using music_share::ChatUseCase;

class TestChatUseCase : public ::testing::Test {
protected:
    void SetUp() {
        shared_ptr<IChatRepository> chat_rep = make_shared<ChatRepositoryPostgres>(connection_to_database);
        shared_ptr<IChatMessageRepository> chat_message_rep = make_shared<ChatMessageRepositoryPostgres>(connection_to_database);
        m_chat_use_case = make_shared<ChatUseCase>(*chat_rep, *chat_message_rep);
        m_chat_request = make_shared<ChatRequestDTO>(2);
        m_id = m_chat_use_case->Create(1, *m_chat_request);
    }
    void TearDown() { }

    shared_ptr<IChatUseCase> m_chat_use_case;
    shared_ptr<ChatRequestDTO> m_chat_request;
    optional<uint32_t> m_id;
};

TEST_F(TestChatUseCase, Create) {
    optional<uint32_t> id = m_chat_use_case->Create(3, *m_chat_request);

    optional<ChatResponseDTO> chat_response = nullopt;
    if (id) {
        chat_response = m_chat_use_case->GetByIdOfTwoUser(1, m_chat_request->target_id);
    }
    if (chat_response) {
        EXPECT_EQ(chat_response->user_first_id, 3);
        EXPECT_EQ(chat_response->user_second_id, m_chat_request->target_id);
    }
}

TEST_F(TestChatUseCase, SendMessage) {
    MessageRequestDTO message("Hello!");

    if (m_id) {
         EXPECT_TRUE(m_chat_use_case->SendMessage(message, *m_id, 1));
    }

    vector<MessageResponseDTO> messages;
    if (m_id) {
        messages = m_chat_use_case->GetUserMessages(1, *m_id);
    }
    EXPECT_EQ(message, messages[0].content);
}

TEST_F(TestChatUseCase, GetUserMessages) {
    MessageRequestDTO message("Hello!");
    bool result = m_chat_use_case->SendMessage(message, *m_id, 1);
    vector<MessageResponseDTO> messages;

    if (result) {
        messages = m_chat_use_case->GetUserMessages(1, *m_id);
    }

    EXPECT_EQ(messages[0].content, message.content);
    EXPECT_EQ(messages[0].chat_id, *m_id);
    EXPECT_EQ(messages[0].sender_id, 1);
    EXPECT_EQ(messages[0].sender_id, 1);
}

TEST_F(TestChatUseCase, GetByIdOfOneUser) {
    vector<ChatResponseDTO> chats = m_chat_use_case->GetByIdOfOneUser(1);

    EXPECT_EQ(chats[0].user_first_id, 1);
    EXPECT_EQ(chats[0].chat_id, *m_id);
    EXPECT_EQ(chats[0].user_second_id, 2);
}

TEST_F(TestChatUseCase, GetByIdOfTwoUser) {
    optional<ChatResponseDTO> chat = m_chat_use_case->GetByIdOfTwoUser(1, 2);

    if (chat) {
        EXPECT_EQ(chat->user_first_id, 1);
        EXPECT_EQ(chat->chat_id, *m_id);
        EXPECT_EQ(chat->user_second_id, 2);
    }
}

#endif  // TESTS_INTTESTS_TEST_CHAT_USE_CASE_H_
