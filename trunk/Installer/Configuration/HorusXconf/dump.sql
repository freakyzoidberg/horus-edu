
DROP TABLE IF EXISTS `files`;
CREATE TABLE `files` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `mime` varchar(64) NOT NULL,
  `size` int(11) NOT NULL,
  `id_tree` int(11) NOT NULL,
  `id_owner` int(11) NOT NULL,
  `hash_sha1` varchar(40) NOT NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `id_ower` (`id_owner`),
  KEY `id_tree` (`id_tree`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
INSERT INTO `files` VALUES (1,'Histoire de la Chine','x-horus/x-lesson',0,241,3,'','2009-09-15 21:14:33'),(2,'Histoire de costume','x-horus/x-lesson',0,241,3,'','2009-09-15 21:14:33'),(3,'Tectonique des plaques','x-horus/x-lesson',0,243,3,'','2009-09-15 21:14:33'),(4,'Reglement interieur.pdf','application/pdf',0,258,4,'','2009-09-15 21:14:33'),(5,'Chine.pdf','application/pdf',0,0,0,'','2009-09-15 21:14:33'),(6,'Decharge de responsabilitee.pdf','application/pdf',0,256,0,'','2009-09-15 21:14:33'),(7,'Fiche descriptive.pdf','application/pdf',0,257,0,'','2009-09-15 21:14:33');

DROP TABLE IF EXISTS `settings`;
CREATE TABLE `settings` (
  `user` int(11) NOT NULL,
  `part` varchar(255) NOT NULL,
  `scope` int(1) NOT NULL,
  `value` blob,
  `mtime` timestamp NOT NULL,
  KEY `user` (`user`),
  KEY `part` (`part`),
  KEY `scope` (`scope`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tree`;
CREATE TABLE `tree` (
  `id` int(11) NOT NULL auto_increment,
  `typeofnode` varchar(42) NOT NULL,
  `name` varchar(128) NOT NULL,
  `user_ref` int(11) NOT NULL,
  `id_parent` int(11) NOT NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM AUTO_INCREMENT=259 DEFAULT CHARSET=utf8;
INSERT INTO `tree` VALUES (1,'CLASSES','Classes',0,0,'2009-08-20 12:07:48'),(2,'GROUP','Professeurs',0,0,'2009-08-20 12:07:48'),(3,'GRADE','6eme',0,1,'2009-08-20 12:07:48'),(237,'GRADE','5eme',0,1,'2009-08-20 12:07:48'),(238,'GRADE','4eme',0,1,'2009-08-20 12:07:48'),(239,'GRADE','3eme',0,1,'2009-08-20 12:07:48'),(240,'SUBJECT','Maths',0,3,'2009-08-20 12:07:48'),(241,'SUBJECT','Histoire',0,245,'2009-08-20 12:07:48'),(242,'SUBJECT','Physique',0,3,'2009-08-20 12:07:48'),(243,'SUBJECT','Geographie',0,245,'2009-08-20 12:07:48'),(244,'SUBJECT','Francais',0,3,'2009-08-20 12:07:48'),(245,'SUBJECT','Histoire / Geo',0,3,'2009-08-20 12:07:48'),(0,'ROOT','College Vauban',0,0,'2009-08-20 12:07:48'),(247,'GROUP','Eleves',0,0,'2009-08-20 12:07:48'),(248,'SUBJECT','SVT',0,237,'2009-08-20 12:07:48'),(249,'SUBJECT','Sport',0,237,'2009-08-20 12:07:48'),(250,'SUBJECT','Histoire / Geo',0,237,'2009-08-20 12:07:48'),(251,'SUBJECT','Francais',0,237,'2009-08-20 12:07:48'),(252,'SUBJECT','Histoire',0,250,'2009-08-20 12:07:48'),(253,'SUBJECT','Geographie',0,250,'2009-08-20 12:07:48'),(254,'GROUP','Administration',0,0,'2009-08-20 12:07:48'),(255,'GROUP','Groups',0,0,'2009-08-20 12:07:48'),(256,'GROUP','Sortie Pedagogiques',0,255,'2009-08-20 12:07:48'),(257,'GROUP','Citee de l\'espace Avril 2009',0,256,'2009-08-20 12:07:48'),(258,'','Documents generaux',0,0,'2009-08-20 12:07:48');

DROP TABLE IF EXISTS `user_has_group`;
CREATE TABLE `user_has_group` (
  `id_user` int(11) NOT NULL,
  `id_group` int(11) NOT NULL,
  KEY `id_user` (`id_user`),
  KEY `id_group` (`id_group`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(11) NOT NULL auto_increment,
  `enabled` tinyint(1) NOT NULL,
  `login` varchar(32) NOT NULL,
  `level` tinyint(1) NOT NULL,
  `password` char(40) NOT NULL,
  `session_key` char(64) NULL,
  `session_end` timestamp NULL,
  `last_login` timestamp NULL,
  `surname` varchar(255) NULL,
  `name` varchar(255) NULL,
  `birth_date` timestamp NULL,
  `picture` blob NULL,
  `address` varchar(255) NULL,
  `phone` varchar(32) NULL,
  `country` varchar(32) NULL,
  `language` varchar(32) NULL,
  `id_tree` int(11) NULL,
  `mtime` timestamp NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `level` (`level`),
  KEY `login` (`login`),
  KEY `enabled` (`enabled`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
