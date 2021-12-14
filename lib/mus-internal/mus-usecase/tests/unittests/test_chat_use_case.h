#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/ichat_use_case.h"
#include "mus-irepo/ichat_repository.h"
#include "mus-usecase/chat_use_case.h"
#include "mus-dto/chat_request_dto.h"
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
using music_share::IChatRepository;
using music_share::Chat;
using music_share::ChatUseCase;

class MockChatRepository : public IChatRepository {
public:
    MOCK_METHOD1(FindByUserId, vector<Chat>(uint32_t));
    MOCK_METHOD2(FindByIdsOfUserPair, Chat(uint32_t, uint32_t));
    MOCK_METHOD1(Find, optional<Chat>(uint32_t));
    MOCK_METHOD1(Insert, void(Chat&));
    MOCK_METHOD1(Update, void(const Chat&));
    MOCK_METHOD1(Delete, void(const Chat&));
};

MATCHER_P(ChatEqualement, other, "Equality matcher for type Chat") {
    return arg.GetUserIds().first == other.GetUserIds().first;
}

class TestChatUseCase : public ::testing::Test {
protected:
    void SetUp() {
        chat_rep = make_shared<MockChatRepository>();
        chat_usecase = make_shared<ChatUseCase>(*chat_rep);
        chat = make_shared<Chat>(1, 2, 1);
        chat_request = make_shared<ChatRequestDTO>(2);
    }

    void TearDown() { }

    shared_ptr<ChatUseCase> chat_usecase;
    shared_ptr<MockChatRepository> chat_rep;
    shared_ptr<Chat> chat;
    shared_ptr<ChatRequestDTO> chat_request;
};

TEST_F(TestChatUseCase, CreateSuccess) {
    uint32_t id_expected = 1;

    EXPECT_CALL(*chat_rep, FindByIdsOfUserPair(1, 2))
            .WillOnce(Return(Chat(1, 2)));

    EXPECT_CALL(*chat_rep, Insert(ChatEqualement(*chat)))
            .WillOnce(Invoke([](Chat& chat_out) {
                chat_out = Chat(1, 2, 1);
            }));

    EXPECT_EQ(chat_usecase->Create(1, *chat_request), id_expected);
}

TEST_F(TestChatUseCase, CreateException) {
    EXPECT_CALL(*chat_rep, FindByIdsOfUserPair(1, 2))
            .WillOnce(Return(Chat(1, 2)));

    EXPECT_CALL(*chat_rep, Insert(ChatEqualement(*chat)))
            .Times(AtLeast(1));

    EXPECT_THROW(chat_usecase->Create(1, *chat_request), CreateException);
}

TEST_F(TestChatUseCase, CreateExistChat) {
    EXPECT_CALL(*chat_rep, FindByIdsOfUserPair(1, 2))
            .WillOnce(Return(*chat));

    EXPECT_THROW(chat_usecase->Create(1, *chat_request), ExistException);
}

TEST_F(TestChatUseCase, GetByIdOfOneUserSuccess) {
    ChatResponseDTO chats_response_expected(1, 1, 2);

    vector<Chat> chats;
    chats.push_back(*chat);

    EXPECT_CALL(*chat_rep, FindByUserId(1))
            .WillOnce(Return(chats));

    vector<ChatResponseDTO> chats_response = chat_usecase->GetByIdOfOneUser(1);

    EXPECT_EQ(chats_response.size(), 1);
    EXPECT_EQ(chats_response[0].chat_id, chats_response_expected.chat_id);
    EXPECT_EQ(chats_response[0].user_first_id,
              chats_response_expected.user_first_id);
    EXPECT_EQ(chats_response[0].user_second_id,
              chats_response_expected.user_second_id);
}

TEST_F(TestChatUseCase, GetByIdOfOneUserInvalidData) {
    vector<Chat> chats;

    EXPECT_CALL(*chat_rep, FindByUserId(1))
            .WillOnce(Return(chats));

    EXPECT_THROW(chat_usecase->GetByIdOfOneUser(1), InvalidDataException);
}

TEST_F(TestChatUseCase, GetByIdOfOneUserNullPointer) {
    vector<Chat> chats;
    chats.emplace_back(1, 2);

    EXPECT_CALL(*chat_rep, FindByUserId(1))
            .WillOnce(Return(chats));

    EXPECT_THROW(chat_usecase->GetByIdOfOneUser(1),
                 NullPointerException);
}

TEST_F(TestChatUseCase, GetByIdOfTwoUserSuccess) {
    ChatResponseDTO chats_response_expected(1, 1, 2);

    EXPECT_CALL(*chat_rep, FindByIdsOfUserPair(1, 2))
            .WillOnce(Return(*chat));

    ChatResponseDTO chats_response = chat_usecase->GetByIdOfTwoUser(1, 2);

    EXPECT_EQ(chats_response.chat_id, chats_response_expected.chat_id);
    EXPECT_EQ(chats_response.user_first_id, chats_response_expected.user_first_id);
    EXPECT_EQ(chats_response.user_second_id, chats_response_expected.user_second_id);
}

TEST_F(TestChatUseCase, GetByIdOfTwoUserInvalidData) {
    vector<Chat> chats;

    EXPECT_CALL(*chat_rep, FindByUserId(1))
            .WillOnce(Return(chats));

    EXPECT_THROW(chat_usecase->GetByIdOfOneUser(1), InvalidDataException);
}
