#include "mus-usecase/song_use_case.h"

#include <memory>
#include <optional>

#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::make_unique;
using std::nullopt;
using std::optional;
using std::string;
using std::vector;

namespace music_share {

    SongUseCase::SongUseCase(ISongRepository& song_rep)
                             : m_song_rep(song_rep) { }

    SongUseCase::SongUseCase(const SongUseCase& song_use_case)
                            : m_song_rep(song_use_case.m_song_rep) { }

    SongUseCase &SongUseCase::operator=(const SongUseCase& song_use_case) {
        m_song_rep = song_use_case.m_song_rep;
        return *this;
    }

    SongResponseDTO SongUseCase::GetById(uint32_t id) {
        optional<Song> song = m_song_rep.Find(id);

        if (!song) {
            throw InvalidDataException();
        }
        if (!song->GetId()) {
            throw NullPointerException();
        }

        return SongResponseDTO(*song->GetId(),
                               song->GetTitle(),
                               song->GetArtist(),
                               song->GetUrl());
    }

    vector<SongResponseDTO> SongUseCase::GetByTitle(const string& title) {
        vector<Song> songs = m_song_rep.FindByTitle(title);

        if (songs.empty()) {
            throw InvalidDataException();
        }

        vector<SongResponseDTO> songs_dto;
        songs_dto.reserve(songs.size());
        for (const Song& song : songs) {
            if (!song.GetId()) {
                throw NullPointerException();
            }
            songs_dto.emplace_back(*song.GetId(),
                                   song.GetTitle(),
                                   song.GetArtist(),
                                   song.GetUrl());
        }

        return songs_dto;
    }

    vector<SongResponseDTO> SongUseCase::GetByArtist(const string& artist) {
        vector<Song> songs = m_song_rep.FindByArtist(artist);

        if (songs.empty()) {
            throw InvalidDataException();
        }

        vector<SongResponseDTO> songs_dto;
        songs_dto.reserve(songs.size());
        for (const Song& song : songs) {
            if (!song.GetId()) {
                throw NullPointerException();
            }
            songs_dto.emplace_back(*song.GetId(),
                                   song.GetTitle(),
                                   song.GetArtist(),
                                   song.GetUrl());
        }

        return songs_dto;
    }

    uint32_t SongUseCase::Create(const SongRequestDTO& song_dto) {
        auto song = make_unique<Song>(song_dto.name,
                                      song_dto.author,
                                      song_dto.duration,
                                      song_dto.path,
                                      song_dto.year,
                                      song_dto.album,
                                      song_dto.genre);

        m_song_rep.Insert(*song);

        if (!song->GetId()) {
            throw CreateException();
        }
        return *song->GetId();
    }

    SongResponseDTO SongUseCase::Update(uint32_t song_id,
                                        const SongRequestDTO& song_dto) {
        Song song(song_dto.name,
                  song_dto.author,
                  song_dto.duration,
                  song_dto.path,
                  song_dto.year,
                  song_dto.album,
                  song_dto.genre,
                  song_id);

        m_song_rep.Update(song);

        return SongResponseDTO(song_id,
                             song_dto.name,
                             song_dto.author,
                             song_dto.path);

    }

    void SongUseCase::DeleteById(uint32_t song_id) {
        optional<Song> song = m_song_rep.Find(song_id);

        if (!song) {
            throw InvalidDataException();
        }
        if (!song->GetId()) {
            throw NullPointerException();
        }

        m_song_rep.Delete(*song);
    }

}  // namespace music_share
