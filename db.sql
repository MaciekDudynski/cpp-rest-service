DROP TABLE sessions;
DROP TABLE users;

CREATE TABLE users
(
 id       bigserial PRIMARY KEY,
 login    varchar(30) UNIQUE NOT NULL,
 password varchar(30) NOT NULL
);

CREATE TABLE sessions
(
 id      bigserial PRIMARY KEY,
 token   varchar(30) UNIQUE NOT NULL,
 user_id bigint NOT NULL REFERENCES users(id),
 ip      varchar(15) NOT NULL,
 time    bigint NOT NULL
);

