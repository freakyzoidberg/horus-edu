-- MySQL dump 10.11
--
-- Host: localhost    Database: chier
-- ------------------------------------------------------
-- Server version	5.0.75-0ubuntu10.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `files`
--

DROP TABLE IF EXISTS `files`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `files` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `mime` varchar(64) NOT NULL,
  `size` int(11) NOT NULL,
  `id_tree` int(11) NOT NULL,
  `id_owner` int(11) NOT NULL,
  `hash_sha1` varchar(40) NOT NULL,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`),
  KEY `id_ower` (`id_owner`),
  KEY `id_tree` (`id_tree`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `files`
--

LOCK TABLES `files` WRITE;
/*!40000 ALTER TABLE `files` DISABLE KEYS */;
INSERT INTO `files` VALUES (1,'Histoire de la Chine','x-horus/x-lesson',0,241,1,'','2009-10-01 08:48:14'),(2,'Histoire de costume','x-horus/x-lesson',0,241,1,'','2009-10-01 08:48:14'),(3,'Tectonique des plaques','x-horus/x-lesson',0,243,1,'','2009-10-01 08:48:14'),(4,'Reglement interieur.pdf','application/pdf',0,258,1,'','2009-10-01 08:48:14'),(5,'Chine.pdf','application/pdf',0,0,1,'','2009-10-01 08:48:14'),(6,'Decharge de responsabilitee.pdf','application/pdf',0,256,1,'','2009-10-01 08:48:14'),(7,'Fiche descriptive.pdf','application/pdf',0,257,1,'','2009-10-01 08:48:14'),(16,'','x-horus/x-lesson',0,241,1,'','2009-10-01 08:49:52'),(15,'','',0,0,0,'','2009-10-01 10:05:33');
/*!40000 ALTER TABLE `files` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `settings`
--

DROP TABLE IF EXISTS `settings`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `settings` (
  `user` int(11) NOT NULL,
  `part` varchar(255) NOT NULL,
  `scope` int(1) NOT NULL,
  `value` blob,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  KEY `user` (`user`),
  KEY `part` (`part`),
  KEY `scope` (`scope`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `settings`
--

LOCK TABLES `settings` WRITE;
/*!40000 ALTER TABLE `settings` DISABLE KEYS */;
/*!40000 ALTER TABLE `settings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tree`
--

DROP TABLE IF EXISTS `tree`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `tree` (
  `id` int(11) NOT NULL auto_increment,
  `typeofnode` varchar(42) NOT NULL,
  `name` varchar(128) NOT NULL,
  `user_ref` int(11) NOT NULL,
  `id_parent` int(11) NOT NULL,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM AUTO_INCREMENT=260 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `tree`
--

LOCK TABLES `tree` WRITE;
/*!40000 ALTER TABLE `tree` DISABLE KEYS */;
INSERT INTO `tree` VALUES (0,'ROOT','College Vauban',0,0,'2009-10-01 08:39:47'),(1,'CLASSES','Classes',0,0,'2009-08-20 10:07:48'),(2,'GROUP','Professeurs',0,0,'2009-08-20 10:07:48'),(3,'GRADE','6eme',0,1,'2009-08-20 10:07:48'),(237,'GRADE','5eme',0,1,'2009-08-20 10:07:48'),(238,'GRADE','4eme',0,1,'2009-08-20 10:07:48'),(239,'GRADE','3eme',0,1,'2009-08-20 10:07:48'),(240,'SUBJECT','Maths',0,3,'2009-08-20 10:07:48'),(241,'SUBJECT','Histoire',0,245,'2009-08-20 10:07:48'),(242,'SUBJECT','Physique',0,3,'2009-08-20 10:07:48'),(243,'SUBJECT','Geographie',0,245,'2009-08-20 10:07:48'),(244,'SUBJECT','Francais',0,3,'2009-08-20 10:07:48'),(245,'SUBJECT','Histoire / Geo',0,3,'2009-08-20 10:07:48'),(247,'GROUP','Eleves',0,0,'2009-08-20 10:07:48'),(248,'SUBJECT','SVT',0,237,'2009-08-20 10:07:48'),(249,'SUBJECT','Sport',0,237,'2009-08-20 10:07:48'),(250,'SUBJECT','Histoire / Geo',0,237,'2009-08-20 10:07:48'),(251,'SUBJECT','Francais',0,237,'2009-08-20 10:07:48'),(252,'SUBJECT','Histoire',0,250,'2009-08-20 10:07:48'),(253,'SUBJECT','Geographie',0,250,'2009-08-20 10:07:48'),(254,'GROUP','Administration',0,0,'2009-08-20 10:07:48'),(255,'GROUP','Groups',0,0,'2009-08-20 10:07:48'),(256,'GROUP','Sortie Pedagogiques',0,255,'2009-08-20 10:07:48'),(257,'GROUP','Citee de l\'espace Avril 2009',0,256,'2009-08-20 10:07:48'),(258,'','Documents generaux',0,0,'2009-08-20 10:07:48');
/*!40000 ALTER TABLE `tree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_has_group`
--

DROP TABLE IF EXISTS `user_has_group`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user_has_group` (
  `id_user` int(11) NOT NULL,
  `id_group` int(11) NOT NULL,
  KEY `id_user` (`id_user`),
  KEY `id_group` (`id_group`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `user_has_group`
--

LOCK TABLES `user_has_group` WRITE;
/*!40000 ALTER TABLE `user_has_group` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_has_group` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `users` (
  `id` int(11) NOT NULL auto_increment,
  `enabled` tinyint(1) NOT NULL,
  `login` varchar(32) NOT NULL,
  `level` tinyint(1) NOT NULL,
  `password` char(40) NOT NULL,
  `session_key` char(64) default NULL,
  `session_end` timestamp NULL default NULL,
  `last_login` timestamp NULL default NULL,
  `surname` varchar(255) default NULL,
  `name` varchar(255) default NULL,
  `birth_date` timestamp NULL default NULL,
  `picture` blob,
  `address` varchar(255) default NULL,
  `phone` varchar(32) default NULL,
  `country` varchar(32) default NULL,
  `language` varchar(32) default NULL,
  `id_tree` int(11) default NULL,
  `mtime` timestamp NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`id`),
  KEY `level` (`level`),
  KEY `login` (`login`),
  KEY `enabled` (`enabled`),
  KEY `mtime` (`mtime`)
) ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `white_board`
--

DROP TABLE IF EXISTS `white_board`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `white_board` (
  `id_tree` int(11) NOT NULL,
  `mode` int(1) NOT NULL,
  `items` blob,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id_tree`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `white_board`
--

LOCK TABLES `white_board` WRITE;
/*!40000 ALTER TABLE `white_board` DISABLE KEYS */;
INSERT INTO `white_board` VALUES (245,1,NULL,'2009-10-01 08:47:46'),(243,40,NULL,'2009-10-01 09:48:23'),(253,0,'\0\0\0\0\0\0Ö\0\0\0Æ\0\0\0Ö\0\0\0)\0','2009-10-01 10:06:35'),(239,40,NULL,'2009-10-01 08:52:35'),(252,0,NULL,'2009-10-01 10:11:33'),(250,40,NULL,'2009-10-01 09:25:47'),(251,0,NULL,'2009-10-01 10:01:01'),(249,0,NULL,'2009-10-01 10:13:36'),(3,0,NULL,'2009-10-01 11:01:22'),(240,0,NULL,'2009-10-01 11:05:23');
/*!40000 ALTER TABLE `white_board` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2009-10-01 11:38:52

DROP TABLE IF EXISTS `event`;
CREATE TABLE `event` (
  `id_tree` int(11) NOT NULL,
  `start_time` timestamp NOT NULL,
  `end_time` timestamp NOT NULL,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id_tree`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
