#ifndef MUS_INTERNAL_MUS_DTO_CHAT_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_CHAT_RESPONSE_DTO_H_

struct ChatResponseDTO {
    ChatResponseDTO(int chat_id_, int user_first_id_, int user_second_id_):
                    chat_id(chat_id_), user_first_id(user_first_id_),
                    user_second_id(user_second_id_) {}

    int chat_id;
    int user_first_id;
    int user_second_id;
};

#endif  // MUS_INTERNAL_MUS_DTO_CHAT_RESPONSE_DTO_H_
