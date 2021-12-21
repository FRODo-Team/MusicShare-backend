#ifndef MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_SONGHANDLER_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_SONGHANDLER_H_

#include <memory>  // std::shared_ptr
#include <optional>  // std::optional

#include "mus-iusecase/isong_use_case.h"
#include "http/server/router/router.h"

namespace music_share::delivery {

class SongHandler final {
public:
    SongHandler(ISongUseCase& usecase);
    void Config(http::server::router::Router& router);

    
    SongResponseDTO
    GetById(uint32_t id);

    std::vector<SongResponseDTO>
    GetByTitleOrArtist(const std::optional<std::string>& titles,
                       const std::optional<std::string>& artists);
private:
    [[maybe_unused]] ISongUseCase& m_usecase;
};

}  // namespace music_share::delivery

#endif  // MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_SONGHANDLER_H_
