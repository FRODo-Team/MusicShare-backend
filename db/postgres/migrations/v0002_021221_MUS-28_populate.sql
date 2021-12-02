INSERT INTO mus_user(username, email, password_hash, nickname, access_level)
VALUES
    ('username1', 'username1@mail.ru', 'hashed123123', 'nick1', 1),
    ('username2', 'username2@mail.ru', 'hashed123123', 'nick2', 1),
    ('username3', 'username3@mail.ru', 'hashed123123', 'nick3', 1),
    ('username4', 'username4@mail.ru', 'hashed123123', 'nick4', 1),
    ('username5', 'username5@mail.ru', 'hashed123123', 'nick5', 1);

INSERT INTO mus_song(title, artist, duration, url, year, album, genre)
VALUES
    ('sometitle1', 'artist1', '3.15', '/somepath/to/song1', 2000, 'unknown1', 'metalcore'),
    ('sometitle2', 'artist2', '2.15', '/somepath/to/song1', 2001, 'unknown2', 'pop'),
    ('sometitle3', 'artist3', '1.15', '/somepath/to/song1', 2002, 'unknown3', 'hip-hop'),
    ('sometitle4', 'artist4', '10.0', '/somepath/to/song1', 2003, 'unknown4', 'dubstep'),
    ('sometitle5', 'artist5', '3.0', '/somepath/to/song1', 2004, 'unknown5', 'progressive house'),
    ('sometitle6', 'artist6', '4.35', '/somepath/to/song1', 2005, 'unknown6', 'trap'),
    ('sometitle7', 'artist7', '2.17', '/somepath/to/song1', 2006, 'unknown7', 'underground');

INSERT INTO mus_playlist(title, creator_id)
VALUES
    ('playlist1', 1),
    ('playlist2', 1),
    ('playlist3', 1),
    ('playlist4', 2),
    ('playlist5', 3),
    ('playlist6', 4),
    ('playlist7', 2);

INSERT INTO mus_user_has_playlist(user_id, playlist_id)
VALUES
    (1, 1),
    (1, 2),
    (1, 3),
    (2, 1),
    (3, 1),
    (4, 5);

INSERT INTO mus_playlist_has_song(playlist_id, song_id)
VALUES
    (1, 1),
    (1, 2),
    (1, 3),
    (1, 5),
    (2, 1),
    (2, 2),
    (2, 3),
    (3, 1),
    (3, 2),
    (3, 3),
    (4, 1),
    (4, 2),
    (4, 5),
    (5, 3);

INSERT INTO mus_chat(user_id_1, user_id_2)
VALUES
    (1, 2),
    (2, 3),
    (1, 3),
    (3, 4);

INSERT INTO mus_chat_message(sender_id, datetime, content, chat_id)
VALUES
    (1, '2018-1-05 14:01:10-08', 'look at this duuuuude', 1),
    (1, '2019-3-05 14:01:10-08', 'look at this dude again', 1),
    (1, '2020-7-05 14:01:10-08', 'look at this dude', 3),
    (1, '2021-10-05 14:01:10-08', 'DUUUUUUUUUUDE!', 3),
    (3, '2021-10-05 14:01:10-08', 'this if fine playlist though', 4),
    (3, '2021-10-05 14:01:10-08', 'look at this duuuuuuuuude', 3),
    (3, '2021-8-05 14:01:10-08', 'i am not a big fun of this genre, you know...', 3),
    (1, '2021-8-05 14:01:10-08', 'bruh....', 1),
    (4, '2021-8-05 14:01:10-08', 'look at this duuuuuuuuude', 4);
