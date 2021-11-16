#ifndef MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_

struct ChatRequestDTO {
    ChatRequestDTO(int target_id_) : target_id(target_id_) {}

    int target_id;
};

#endif  // MUS_INTERNAL_MUS_DTO_CHAT_REQUEST_DTO_H_
