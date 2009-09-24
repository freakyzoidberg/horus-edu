CREATE TABLE files (
id int NOT NULL,
"name" varchar(255) NOT NULL,
mime varchar(64) NOT NULL,
size int NOT NULL,
id_tree int NOT NULL,
id_owner int NOT NULL,
hash_sha1 varchar(40) NOT NULL,
mtime timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY (id)
);
CREATE INDEX files_mtime_idx ON files (mtime);


INSERT INTO files (id, name, mime, size, id_tree, id_owner, hash_sha1, mtime) VALUES
(1, 'Histoire de la Chine', 'x-horus/x-lesson', 0, 241, 3, '', '2009-09-15 21:14:33'),
(2, 'Histoire de costume', 'x-horus/x-lesson', 0, 241, 3, '', '2009-09-15 21:14:33'),
(3, 'Tectonique des plaques', 'x-horus/x-lesson', 0, 243, 3, '', '2009-09-15 21:14:33'),
(4, 'Reglement interieur.pdf', 'application/pdf', 0, 258, 4, '', '2009-09-15 21:14:33'),
(5, 'Chine.pdf', 'application/pdf', 0, 0, 0, '', '2009-09-15 21:14:33'),
(6, 'Decharge de responsabilitee.pdf', 'application/pdf', 0, 256, 0, '', '2009-09-15 21:14:33'),
(7, 'Fiche descriptive.pdf', 'application/pdf', 0, 257, 0, '', '2009-09-15 21:14:33');


CREATE TABLE settings (
"user" int NOT NULL,
part varchar(255) NOT NULL,
scope int NOT NULL,
"value" bytea,
mtime timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE INDEX settings_mtime_idx ON settings (mtime);



CREATE TABLE tree (
id int NOT NULL,
typeofnode varchar(42) NOT NULL,
"name" varchar(128) NOT NULL,
user_ref int NOT NULL,
id_parent int NOT NULL,
mtime timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY (id)
);
CREATE INDEX tree_mtime_idx ON tree (mtime);


INSERT INTO tree (id, typeofnode, name, user_ref, id_parent, mtime) VALUES
(1, 'CLASSES', 'Classes', 0, 0, '2009-08-20 12:07:48'),
(2, 'GROUP', 'Professeurs', 0, 0, '2009-08-20 12:07:48'),
(3, 'GRADE', '6eme', 0, 1, '2009-08-20 12:07:48'),
(237, 'GRADE', '5eme', 0, 1, '2009-08-20 12:07:48'),
(238, 'GRADE', '4eme', 0, 1, '2009-08-20 12:07:48'),
(239, 'GRADE', '3eme', 0, 1, '2009-08-20 12:07:48'),
(240, 'SUBJECT', 'Maths', 0, 3, '2009-08-20 12:07:48'),
(241, 'SUBJECT', 'Histoire', 0, 245, '2009-08-20 12:07:48'),
(242, 'SUBJECT', 'Physique', 0, 3, '2009-08-20 12:07:48'),
(243, 'SUBJECT', 'Geographie', 0, 245, '2009-08-20 12:07:48'),
(244, 'SUBJECT', 'Francais', 0, 3, '2009-08-20 12:07:48'),
(245, 'SUBJECT', 'Histoire / Geo', 0, 3, '2009-08-20 12:07:48'),
(0, 'ROOT', 'College Vauban', 0, 0, '2009-08-20 12:07:48'),
(247, 'GROUP', 'Eleves', 0, 0, '2009-08-20 12:07:48'),
(248, 'SUBJECT', 'SVT', 0, 237, '2009-08-20 12:07:48'),
(249, 'SUBJECT', 'Sport', 0, 237, '2009-08-20 12:07:48'),
(250, 'SUBJECT', 'Histoire / Geo', 0, 237, '2009-08-20 12:07:48'),
(251, 'SUBJECT', 'Francais', 0, 237, '2009-08-20 12:07:48'),
(252, 'SUBJECT', 'Histoire', 0, 250, '2009-08-20 12:07:48'),
(253, 'SUBJECT', 'Geographie', 0, 250, '2009-08-20 12:07:48'),
(254, 'GROUP', 'Administration', 0, 0, '2009-08-20 12:07:48'),
(255, 'GROUP', 'Groups', 0, 0, '2009-08-20 12:07:48'),
(256, 'GROUP', 'Sortie Pedagogiques', 0, 255, '2009-08-20 12:07:48'),
(257, 'GROUP', 'Citee de l''espace Avril 2009', 0, 256, '2009-08-20 12:07:48'),
(258, '', 'Documents generaux', 0, 0, '2009-08-20 12:07:48');


CREATE TABLE users (
id int NOT NULL,
enabled int NOT NULL,
login varchar(32) NOT NULL,
"level" int NOT NULL,
"password" char(40) NOT NULL,
session_key char(64) DEFAULT NULL,
session_end timestamp NULL DEFAULT NULL,
last_login timestamp NULL DEFAULT NULL,
surname varchar(255) DEFAULT NULL,
"name" varchar(255) DEFAULT NULL,
birth_date timestamp NULL DEFAULT NULL,
picture bytea,
address varchar(255) DEFAULT NULL,
phone varchar(32) DEFAULT NULL,
country varchar(32) DEFAULT NULL,
"language" varchar(32) DEFAULT NULL,
id_tree int DEFAULT NULL,
mtime timestamp NOT NULL DEFAULT '1970-01-01 00:00:00+00',
PRIMARY KEY (id)
);
CREATE INDEX users_mtime_idx ON users (mtime);



CREATE TABLE user_has_group (
id_user int NOT NULL,
id_group int NOT NULL
);
CREATE INDEX user_has_group_id_group_idx ON user_has_group (id_group);