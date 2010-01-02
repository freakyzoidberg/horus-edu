DROP TABLE IF EXISTS `file`;
CREATE TABLE `file` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `mime` varchar(64) NOT NULL,
  `size` int(11) NOT NULL,
  `id_tree` int(11) NOT NULL,
  `id_owner` int(11) NOT NULL,
  `hash_sha1` varchar(40) NOT NULL,
	`keywords` varchar(255) NOT NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `id_ower` (`id_owner`),
  KEY `id_tree` (`id_tree`)
);



DROP TABLE IF EXISTS `setting`;
CREATE TABLE `setting` (
  `user` int(11) NOT NULL,
  `part` varchar(255) NOT NULL,
  `scope` int(1) NOT NULL,
  `value` blob,
  `mtime` timestamp NOT NULL,
  KEY `user` (`user`),
  KEY `part` (`part`),
  KEY `scope` (`scope`)
);


DROP TABLE IF EXISTS `tree`;
CREATE TABLE `tree` (
  `id` int(11) NOT NULL auto_increment,
  `typeofnode` varchar(42) NOT NULL,
  `name` varchar(128) NOT NULL,
  `user_ref` int(11) NOT NULL,
  `id_parent` int(11) NOT NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`)
);
INSERT INTO `tree` VALUES (0,'ROOT','College Vauban',0,0,'2009-10-01 08:39:47');
UPDATE `tree` set id = 0 where id = 1;
ALTER TABLE `tree` AUTO_INCREMENT=0;
INSERT INTO `tree` VALUES (1,'CLASSES','Classes',0,0,'2009-08-20 10:07:48'),(2,'GROUP','Professeurs',0,0,'2009-08-20 10:07:48'),(3,'GRADE','6eme',0,1,'2009-08-20 10:07:48'),(237,'GRADE','5eme',0,1,'2009-08-20 10:07:48'),(238,'GRADE','4eme',0,1,'2009-08-20 10:07:48'),(239,'GRADE','3eme',0,1,'2009-08-20 10:07:48'),(240,'SUBJECT','Maths',0,3,'2009-08-20 10:07:48'),(241,'SUBJECT','Histoire',0,245,'2009-08-20 10:07:48'),(242,'SUBJECT','Physique',0,3,'2009-08-20 10:07:48'),(243,'SUBJECT','Geographie',0,245,'2009-08-20 10:07:48'),(244,'SUBJECT','Francais',0,3,'2009-08-20 10:07:48'),(245,'SUBJECT','Histoire / Geo',0,3,'2009-08-20 10:07:48'),(247,'GROUP','Eleves',0,0,'2009-08-20 10:07:48'),(248,'SUBJECT','SVT',0,237,'2009-08-20 10:07:48'),(249,'SUBJECT','Sport',0,237,'2009-08-20 10:07:48'),(250,'SUBJECT','Histoire / Geo',0,237,'2009-08-20 10:07:48'),(251,'SUBJECT','Francais',0,237,'2009-08-20 10:07:48'),(252,'SUBJECT','Histoire',0,250,'2009-08-20 10:07:48'),(253,'SUBJECT','Geographie',0,250,'2009-08-20 10:07:48'),(254,'GROUP','Administration',0,0,'2009-08-20 10:07:48'),(255,'GROUP','Groups',0,0,'2009-08-20 10:07:48'),(256,'GROUP','Sortie Pedagogiques',0,255,'2009-08-20 10:07:48'),(257,'GROUP','Citee de l\'espace Avril 2009',0,256,'2009-08-20 10:07:48'),(258,'','Documents generaux',0,0,'2009-08-20 10:07:48');


DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(11) NOT NULL auto_increment,
  `enabled` tinyint(1) NOT NULL,
  `login` varchar(32) NOT NULL,
  `level` tinyint(1) NOT NULL,
  `password` char(40) NOT NULL,
  `student_class` int(11) default NULL,
  `session_key` char(64) default NULL,
  `session_end` timestamp NULL default NULL,
  `last_login` timestamp NULL default NULL,
  `language` varchar(32) default NULL,
  `surname` varchar(255) default NULL,
  `name` varchar(255) default NULL,
  `birth_date` timestamp NULL default NULL,
  `picture` blob,
  `address` varchar(255) default NULL,
  `phone1` varchar(32) default NULL,
  `phone2` varchar(32) default NULL,
  `phone3` varchar(32) default NULL,
  `country` varchar(32) default NULL,
  `gender` tinyint(1) default NULL,
  `occupation` varchar(32) default NULL,
  `pro_category` varchar(32) default NULL,
  `relationship` varchar(32) default NULL,
  `student` int(11) default NULL,
  `mail` varchar(32) default NULL,
  `subscription_reason` varchar(32) default NULL,
  `repeated_years` int(11) default NULL,
  `start_year` int(11) default NULL,
  `leave_year` int(11) default NULL,
  `follow_up` text default NULL,
  `comment` text default NULL,
  `born_place` varchar(32) default NULL,
  `nbr_brothers` int(11) default NULL,
  `social_insurance_nbr` varchar(32) default NULL,
  `diploma` varchar(255) default NULL,
  `contract` varchar(255) default NULL,
  `passmail` varchar(40) default NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `level` (`level`),
  KEY `login` (`login`),
  KEY `enabled` (`enabled`),
  KEY `student_class` (`student_class`),
  KEY `student` (`student`)
);


DROP TABLE IF EXISTS `white_board`;
CREATE TABLE `white_board` (
  `id_tree` int(11) NOT NULL,
  `mode` int(1) NOT NULL,
  `items` blob,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id_tree`)
);



DROP TABLE IF EXISTS `event`;
CREATE TABLE `event` (
  `id_tree` int(11) NOT NULL,
  `start_time` timestamp NOT NULL,
  `end_time` timestamp NOT NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id_tree`)
);


DROP TABLE IF EXISTS `attendance`;
CREATE TABLE IF NOT EXISTS `attendance` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` date NOT NULL,
  `id_user` int(11) NOT NULL,
  `id_event` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `start_time` time NOT NULL,
  `end_time` time NOT NULL,
  PRIMARY KEY  (`id`)
);


DROP TABLE IF EXISTS `mark`;
CREATE TABLE IF NOT EXISTS `mark` (
  `id` int(11) NOT NULL auto_increment,
  `id_user` int(11) NOT NULL,
  `id_event` int(11) NOT NULL,
  `quote` varchar(32) NOT NULL,
  `mark` int(11) NOT NULL,
  `date` date NOT NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`)
);


DROP TABLE IF EXISTS `schedule`;
CREATE TABLE IF NOT EXISTS `schedule` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_node` int(11) NOT NULL,
  `date_start` date NOT NULL,
  `date_end` date NOT NULL,
  `exception` blob,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;



DROP TABLE IF EXISTS `schedule_event`;
DROP TABLE IF EXISTS `schedule_exception`;
