DROP TABLE users;

CREATE TABLE users
(
 id       serial PRIMARY KEY,
 login    varchar(30) UNIQUE NOT NULL,
 password varchar(30) NOT NULL
);

