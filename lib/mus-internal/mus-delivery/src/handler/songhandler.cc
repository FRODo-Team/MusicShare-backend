#include "mus-delivery/handler/songhandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"

namespace music_share::delivery {

SongHandler::SongHandler(ISongUseCase& usecase)
    : m_usecase(usecase) {}

void SongHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/songs";

    router.GET(http::server::router::Route(
        prefix,
        [this](http::common::Request request, auto) {
            auto qs = http::common::QueryString::fromString(
                request.target()
                    .substr(request.target().find('?') + 1)
                    .to_string()
            );

            std::vector<std::string> titles;
            auto [tbeg, tend] = qs.GetAll("title");
            std::transform(tbeg, tend,
                           std::back_inserter(titles),
                           [](auto it) { return it.second; });

            std::vector<std::string> artists;
            auto [abeg, aend] = qs.GetAll("artist");
            std::transform(abeg, aend,
                           std::back_inserter(artists),
                           [](auto it) { return it.second; });

            auto body = GetByTitleOrArtist(titles, artists);
            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }
    ));

    router.GET(http::server::router::Route(
        prefix + "/:id([0-9]+)",
        [this](auto, auto params) {
            uint32_t id = atoi(params["id"].c_str());
            auto body = GetById(id);

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }
    ));
}

SongResponseDTO
SongHandler::GetById(uint32_t id) {
    return SongResponseDTO(id, "", "", "");
}

std::vector<SongResponseDTO>
SongHandler::GetByTitleOrArtist(const std::vector<std::string>& titles,
                                const std::vector<std::string>& artists) {
    return {SongResponseDTO(1, "", "", "")};
}

}  // namespace music_share::delivery
