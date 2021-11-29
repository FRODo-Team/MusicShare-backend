DROP TABLE IF EXISTS mus_chat_message;
DROP TABLE IF EXISTS mus_chat;
DROP TABLE IF EXISTS mus_user_has_playlist;
DROP TABLE IF EXISTS mus_playlist_has_song;
DROP TABLE IF EXISTS mus_playlist;
DROP TABLE IF EXISTS mus_song;
DROP TABLE IF EXISTS mus_user;


CREATE TABLE IF NOT EXISTS mus_user(
    id SERIAL PRIMARY KEY,
    username VARCHAR(30),
    email VARCHAR(255),
    password_hash VARCHAR(128),
    nickname VARCHAR(30),
    access_level INT
);

CREATE TABLE IF NOT EXISTS mus_song(
    id SERIAL PRIMARY KEY,
    title VARCHAR(60),
    artist VARCHAR(60),
    duration VARCHAR(10),
    url VARCHAR(255),
    year INT,
    album VARCHAR(120),
    genre VARCHAR(30)
);

CREATE TABLE IF NOT EXISTS mus_playlist(
    id SERIAL PRIMARY KEY,
    title VARCHAR(30),
    creator_id INT,

    CONSTRAINT fk_creator
        FOREIGN KEY(creator_id) REFERENCES mus_user(id)
        ON DELETE CASCADE
);

-- Реализует связь "многие ко многим" между пользователями и плейлистами.
CREATE TABLE IF NOT EXISTS mus_user_has_playlist(
    user_id INT,
    playlist_id INT,

    CONSTRAINT fk_user
        FOREIGN KEY(user_id) REFERENCES mus_user(id)
        ON DELETE CASCADE,
    
    CONSTRAINT fk_playlist
        FOREIGN KEY(playlist_id) REFERENCES mus_playlist(id)
        ON DELETE CASCADE
);

-- Реализует связь "многие ко многим" между плейлистами и песнями.
CREATE TABLE IF NOT EXISTS mus_playlist_has_song(
    playlist_id INT,
    song_id INT,

    CONSTRAINT fk_playlist
        FOREIGN KEY(playlist_id) REFERENCES mus_playlist(id)
        ON DELETE CASCADE,
    CONSTRAINT fk_song
        FOREIGN KEY(song_id) REFERENCES mus_song(id)
        ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS mus_chat(
    id SERIAL PRIMARY KEY,
    user_id_1 INT,
    user_id_2 INT,

    CONSTRAINT fk_user_1
        FOREIGN KEY(user_id_1) REFERENCES mus_user(id)
        ON DELETE SET NULL,
    CONSTRAINT fk_user_2
        FOREIGN KEY(user_id_2) REFERENCES mus_user(id)
        ON DELETE SET NULL
);

CREATE TABLE IF NOT EXISTS mus_chat_message(
    id SERIAL PRIMARY KEY,
    sender_id INT,
    datetime TIMESTAMP,
    content VARCHAR(512),
    chat_id INT,

    CONSTRAINT fk_sender
        FOREIGN KEY(sender_id) REFERENCES mus_user(id)
        ON DELETE SET NULL,
    CONSTRAINT fk_chat
        FOREIGN KEY(chat_id) REFERENCES mus_chat(id)
        ON DELETE CASCADE
);
