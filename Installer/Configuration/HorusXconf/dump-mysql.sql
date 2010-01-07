-- MySQL dump 10.11
--
-- Host: localhost    Database: horus
-- ------------------------------------------------------
-- Server version	5.0.84-log

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
-- Table structure for table `Exams`
--

DROP TABLE IF EXISTS `Exams`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Exams` (
  `id` int(11) NOT NULL auto_increment,
  `id_tree` int(11) NOT NULL,
  `comment` text NOT NULL,
  `date` date NOT NULL,
  `teacher_id` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Exams`
--

LOCK TABLES `Exams` WRITE;
/*!40000 ALTER TABLE `Exams` DISABLE KEYS */;
INSERT INTO `Exams` VALUES (1,275,'DS1','2010-01-06',53),(2,265,'DS1','2009-01-01',53),(3,263,'Trigonometrie','2010-01-07',1);
/*!40000 ALTER TABLE `Exams` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Marks`
--

DROP TABLE IF EXISTS `Marks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Marks` (
  `id` int(11) NOT NULL auto_increment,
  `exam_id` int(11) NOT NULL,
  `comment` text NOT NULL,
  `result` text NOT NULL,
  `student_id` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Marks`
--

LOCK TABLES `Marks` WRITE;
/*!40000 ALTER TABLE `Marks` DISABLE KEYS */;
INSERT INTO `Marks` VALUES (1,2,'Passable','10',79),(2,3,'Peut mieu faire','10',76),(3,3,'Pantouflard','8',79),(4,3,'A des capacitees mais ne les exploite pas.','12',82),(5,3,'A des capacitees mais ne les exploite pas.','13',85),(6,3,'A des capacitees mais ne les exploite pas.','13',88),(7,3,'A des capacitees mais ne les exploite pas.','13',91),(8,3,'A des capacitees mais ne les exploite pas.','13',94),(9,3,'A des capacitees mais ne les exploite pas.','13',97),(10,3,'A des capacitees mais ne les exploite pas.','13',100),(11,3,'A des capacitees mais ne les exploite pas.','13',103),(12,3,'A des capacitees mais ne les exploite pas.','13',106),(13,3,'A des capacitees mais ne les exploite pas.','13',109),(14,3,'A touche le fond mais creuse encore.','3',112),(15,3,'A touche le fond mais creuse encore.','4',115),(16,3,'A touche le fond mais creuse encore.','4',118);
/*!40000 ALTER TABLE `Marks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `attendance`
--

DROP TABLE IF EXISTS `attendance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `attendance` (
  `id` int(11) NOT NULL auto_increment,
  `date` date NOT NULL,
  `id_user` int(11) NOT NULL,
  `lesson` text NOT NULL,
  `type` int(11) NOT NULL,
  `start_time` time NOT NULL,
  `end_time` time NOT NULL,
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `attendance`
--

LOCK TABLES `attendance` WRITE;
/*!40000 ALTER TABLE `attendance` DISABLE KEYS */;
INSERT INTO `attendance` VALUES (1,'2010-01-07',76,'Chimie',1,'10:00:00','12:00:00'),(2,'2010-01-07',79,'Histoire',2,'14:30:00','16:30:00'),(3,'2010-01-07',97,'Chimie',1,'10:00:00','12:00:00'),(4,'2010-01-07',97,'Histoire',1,'14:30:00','16:30:00'),(6,'2010-01-05',97,'Histoire',2,'08:00:00','10:00:00'),(7,'2010-01-05',97,'Math',2,'14:00:00','17:00:00'),(8,'2010-01-05',97,'Chimie',2,'10:00:00','12:00:00');
/*!40000 ALTER TABLE `attendance` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `file`
--

DROP TABLE IF EXISTS `file`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `file` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `mime` varchar(64) NOT NULL,
  `size` int(11) NOT NULL,
  `id_tree` int(11) NOT NULL,
  `id_owner` int(11) NOT NULL,
  `hash_sha1` varchar(40) NOT NULL,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `keywords` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `id_owner` (`id_owner`),
  KEY `id_tree` (`id_tree`)
) ENGINE=MyISAM AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file`
--

LOCK TABLES `file` WRITE;
/*!40000 ALTER TABLE `file` DISABLE KEYS */;
INSERT INTO `file` VALUES (47,'album.mpg','application/octet-stream',10952704,265,1,'87496e12c03f5330f4a3eeb7e332ccc1a6b27493','2010-01-06 22:07:47',''),(48,'berlin.mp3','application/octet-stream',8265932,265,1,'ee66d4603c1633085f9f8a1f8f0233a26e640eed','2010-01-06 22:08:06',''),(42,'dates.jpg','application/octet-stream',595037,265,1,'eccde32b52ab73ea32c30cbdcfc9fdc79838178d','2010-01-06 22:05:52',''),(46,'eisenhower.mpg','application/octet-stream',5304320,265,1,'cd1a4d15205dcf30efe7137b2eddaec5ffb2f14e','2010-01-06 22:07:37',''),(43,'europe.jpg','application/octet-stream',54784,265,1,'f3e7d0d922a5b4432685957d65b5257adf3336ca','2010-01-06 22:07:07',''),(49,'map.gif','application/octet-stream',17598,265,1,'3fbeda5b8b88f08e91eea6b95d617247254f0089','2010-01-06 22:08:31',''),(44,'vietnam.jpg','application/octet-stream',41070,265,1,'df384783cda8b610b9034607065ac639035bd610','2010-01-06 22:06:11',''),(45,'wall.mpg','application/octet-stream',5601280,265,1,'75196bc6933eb2404ad29129cbadd00b41c0e06a','2010-01-06 22:07:24',''),(50,'guerre-froide.hor','x-horus/x-lesson',19432,265,121,'18fe117ecdf56981f43a0ef389354a1a24ce8288','2010-01-06 22:44:53','');
/*!40000 ALTER TABLE `file` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schedule`
--

DROP TABLE IF EXISTS `schedule`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schedule` (
  `id` int(11) NOT NULL auto_increment,
  `id_node` int(11) NOT NULL,
  `date_start` date NOT NULL,
  `date_end` date NOT NULL,
  `exception` blob,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schedule`
--

LOCK TABLES `schedule` WRITE;
/*!40000 ALTER TABLE `schedule` DISABLE KEYS */;
INSERT INTO `schedule` VALUES (1,259,'2010-01-06','2010-01-06',NULL);
/*!40000 ALTER TABLE `schedule` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schedule_event`
--

DROP TABLE IF EXISTS `schedule_event`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schedule_event` (
  `id` int(11) NOT NULL,
  `id_schedule` int(11) NOT NULL,
  `day` int(11) NOT NULL,
  `time_start` time NOT NULL,
  `time_end` time NOT NULL,
  `name` text NOT NULL,
  `detail` text NOT NULL,
  `date_start` date default NULL,
  `date_end` date default NULL,
  `modulo` int(11) default NULL,
  `exception` blob,
  `force` int(11) default NULL,
  `id_teacher` int(11) default NULL,
  `color` text
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schedule_event`
--

LOCK TABLES `schedule_event` WRITE;
/*!40000 ALTER TABLE `schedule_event` DISABLE KEYS */;
INSERT INTO `schedule_event` VALUES (10,1,5,'14:00:00','17:00:00','Math','','2010-01-07','2010-01-07',1,NULL,0,55,'Blue'),(9,1,5,'08:00:00','12:00:00','Francais','','2010-01-07','2010-01-07',1,NULL,0,55,'Yellow'),(8,1,4,'14:30:00','16:30:00','Histoire','','2010-01-07','2010-01-07',1,NULL,0,121,'Red'),(7,1,4,'10:00:00','12:00:00','Chimie','','2010-01-07','2010-01-07',1,NULL,0,57,'White'),(5,1,2,'14:00:00','17:00:00','Math','','2010-01-07','2010-01-07',1,NULL,0,55,'Blue'),(6,1,3,'08:00:00','12:00:00','Geographie','','2010-01-07','2010-01-07',1,NULL,0,66,'Green'),(2,1,1,'16:00:00','18:00:00','Geographie','','2010-01-06','2010-01-06',0,NULL,1,64,'Green'),(3,1,2,'08:00:00','10:00:00','Histoire','','2010-01-07','2010-01-07',1,NULL,0,60,'Red'),(4,1,2,'10:00:00','12:00:00','Chimie','','2010-01-07','2010-01-07',1,NULL,0,64,'White'),(1,1,1,'14:00:00','16:00:00','Francais','','2010-01-06','2010-01-06',0,NULL,1,59,'Yellow'),(0,1,1,'08:00:00','12:00:00','Math','','2010-01-06','2010-01-06',0,NULL,1,54,'Blue');
/*!40000 ALTER TABLE `schedule_event` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schedule_exception`
--

DROP TABLE IF EXISTS `schedule_exception`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schedule_exception` (
  `id_event` int(11) NOT NULL,
  `id_schedule` int(11) NOT NULL,
  `date_start` date NOT NULL,
  `date_end` date NOT NULL,
  `name` text NOT NULL,
  `type` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schedule_exception`
--

LOCK TABLES `schedule_exception` WRITE;
/*!40000 ALTER TABLE `schedule_exception` DISABLE KEYS */;
/*!40000 ALTER TABLE `schedule_exception` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `setting`
--

DROP TABLE IF EXISTS `setting`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `setting` (
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
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `setting`
--

LOCK TABLES `setting` WRITE;
/*!40000 ALTER TABLE `setting` DISABLE KEYS */;
INSERT INTO `setting` VALUES (1,'MainBoard',0,'','2010-01-06 17:33:29'),(53,'MainBoard',0,'','2010-01-06 17:33:31'),(121,'MainBoard',0,'','2010-01-06 22:42:43');
/*!40000 ALTER TABLE `setting` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tree`
--

DROP TABLE IF EXISTS `tree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tree` (
  `id` int(11) NOT NULL auto_increment,
  `typeofnode` varchar(42) NOT NULL,
  `name` varchar(128) NOT NULL,
  `user_ref` int(11) NOT NULL,
  `id_parent` int(11) NOT NULL,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=284 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tree`
--

LOCK TABLES `tree` WRITE;
/*!40000 ALTER TABLE `tree` DISABLE KEYS */;
INSERT INTO `tree` VALUES (0,'ROOT','College Vauban',0,0,'2010-01-06 16:06:04'),(259,'GRADE','6eme',54,0,'2010-01-06 17:47:56'),(260,'GRADE','5eme',55,0,'2010-01-06 17:48:05'),(261,'GRADE','4eme',60,0,'2010-01-06 17:48:16'),(262,'GRADE','3eme',57,0,'2010-01-06 17:48:22'),(263,'SUBJECT','Math',55,259,'2010-01-06 17:49:35'),(264,'SUBJECT','Francais',55,259,'2010-01-06 17:50:56'),(265,'SUBJECT','Histoire',121,259,'2010-01-06 22:24:22'),(266,'SUBJECT','Geographie',63,259,'2010-01-06 17:52:23'),(267,'SUBJECT','Chimie',62,259,'2010-01-06 17:52:59'),(268,'SUBJECT','Math',54,260,'2010-01-06 17:53:24'),(269,'SUBJECT','Francais',55,260,'2010-01-06 17:53:32'),(270,'SUBJECT','Histoire',58,260,'2010-01-06 17:53:44'),(271,'SUBJECT','Geo',61,260,'2010-01-06 17:59:51'),(272,'SUBJECT','Physique',64,260,'2010-01-06 17:55:33'),(273,'SUBJECT','Math',54,261,'2010-01-06 17:56:03'),(274,'SUBJECT','Francais',55,261,'2010-01-06 17:56:09'),(275,'SUBJECT','Anglais',63,261,'2010-01-06 17:56:50'),(276,'SUBJECT','EPS',56,261,'2010-01-06 17:57:52'),(277,'SUBJECT','Art',66,261,'2010-01-06 18:01:30'),(278,'SUBJECT','Math',54,262,'2010-01-06 18:01:44'),(279,'SUBJECT','Francais',55,262,'2010-01-06 18:01:54'),(280,'SUBJECT','Anglais',58,262,'2010-01-06 18:02:06'),(281,'SUBJECT','Chinois',60,262,'2010-01-06 18:02:20'),(282,'SUBJECT','Compta',62,262,'2010-01-06 18:03:20'),(283,'SUBJECT','Physique',57,262,'2010-01-06 18:13:00');
/*!40000 ALTER TABLE `tree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
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
  `follow_up` text,
  `comment` text,
  `born_place` varchar(32) default NULL,
  `nbr_brothers` int(11) default NULL,
  `social_insurance_nbr` varchar(32) default NULL,
  `diploma` varchar(255) default NULL,
  `contract` varchar(255) default NULL,
  `passmail` varchar(40) default NULL,
  `mtime` timestamp NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`id`),
  KEY `level` (`level`),
  KEY `login` (`login`),
  KEY `enabled` (`enabled`),
  KEY `student_class` (`student_class`),
  KEY `student` (`student`)
) ENGINE=MyISAM AUTO_INCREMENT=122 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,1,'admin',0,'d033e22ae348aeb5660fc2140aec35850c4da997',NULL,'48d306b513b2ac314636f616747c4171700133c00d335ee6a6c3a8db60bf6725','2010-01-07 12:28:13','2010-01-07 00:28:13',NULL,'Father','God',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0000-00-00 00:00:00'),(71,1,'AdrienGrandemange',1,'7b668f17b4268e341bd0f1d237692e3e31c97fb5',0,NULL,NULL,NULL,NULL,'Adrien','Grandemange','1987-04-13 22:00:00',NULL,'12 rue Emile Zola\n94100 Kremelin Bicetre','','','',NULL,0,NULL,NULL,NULL,0,'grande_a@epitech.net',NULL,0,0,0,NULL,NULL,'Reims',0,'','','','QWRyaWVuR3JhbmRlbWFuZ2U=','2010-01-06 18:10:58'),(72,1,'RomainBertholon',1,'ef82eae154d905812ae4e0db4ae0228fc483bd4b',0,NULL,NULL,NULL,NULL,'Romain','Bertholon','1984-05-15 22:00:00',NULL,'57 rue de la Soif\n75007 Paris','','','',NULL,0,NULL,NULL,NULL,0,'',NULL,0,0,0,NULL,NULL,'Saint Etienne',0,'','','','Um9tYWluQmVydGhvbG9u','2010-01-06 18:12:10'),(61,1,'MargaretTouchher',2,'132d3c7cb1c6525a26589a98eb890565456deb29',0,NULL,NULL,NULL,NULL,'Margaret','Touchher','2010-01-05 23:00:00',NULL,'3 Avenue des Champs Elysée\n75007 Paris','','','',NULL,1,NULL,NULL,NULL,0,'',NULL,0,0,0,NULL,NULL,'Sherwood',0,'','','','TWFyZ2FyZXRUb3VjaGhlcg==','2010-01-06 17:46:14'),(76,1,'PeterPan',3,'086a53b26968066405303182fb243cab637fa610',259,'81fb54dfe1bf56478788ea7ba154375b79e38e993f430da68629ff708f0509cd','2010-01-07 12:23:49','2010-01-07 00:23:49',NULL,'Peter','Pan','1993-11-14 23:00:00',NULL,'Neverland District','',NULL,'',NULL,0,NULL,NULL,'Married',0,'','',0,2010,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Shefield',2,NULL,NULL,NULL,'UGV0ZXJQYW4=','2010-01-06 21:11:51'),(79,1,'JaneDoe',3,'ccf8912c5fa556f3d512ca9135e692d2efb279c3',259,NULL,NULL,NULL,NULL,'Jane','Doe','2010-01-05 23:00:00',NULL,'32 avenue de la Comtesse\n75006 Paris','0123456789',NULL,'',NULL,1,NULL,NULL,'Married',0,'jane.doe@worldnet.com','',0,2010,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Paris',0,NULL,NULL,NULL,'SmFuZURvZQ==','2010-01-06 21:16:19'),(77,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,76,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:11:30'),(78,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,0,'',NULL,NULL,76,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:11:30'),(70,1,'AbderNanouche',1,'f2e8c14b30524f2d08da4424652ace1d52625dc5',0,NULL,NULL,NULL,NULL,'Abder','Nanouche','1986-08-19 22:00:00',NULL,'67 rue Bernard Show\n75015 Paris','0678542319','','',NULL,0,NULL,NULL,NULL,0,'nanouc_a@epitech.eu',NULL,0,0,0,NULL,NULL,'Alger',1,'','','','QWJkZXJOYW5vdWNoZQ==','2010-01-06 18:09:15'),(60,1,'DemiMoore',2,'93dc1b45a50ddd76a4341050f0ad80c8d8b7f320',0,NULL,NULL,NULL,NULL,'Demi','Moore','1975-07-22 23:00:00',NULL,'14 rue Antoine Nourdelle\n75014 Paris','','','',NULL,1,NULL,NULL,NULL,0,'',NULL,0,0,0,NULL,NULL,'NYC',0,'','','','RGVtaU1vb3Jl','2010-01-06 17:45:26'),(59,1,'SuryaBonali',2,'4aaf13b1935ce8b020fb7cc77324e61427d2a4fc',0,NULL,NULL,NULL,NULL,'Surya','Bonali','1973-12-14 23:00:00',NULL,'95 avenue du Maine\n75020 Paris','','','',NULL,1,NULL,NULL,NULL,0,'icequeen@club-internet.fr',NULL,0,0,0,NULL,NULL,'Nice',0,'','','','U3VyeWFCb25hbGk=','2010-01-06 17:44:28'),(58,1,'AaronDavis',2,'c57b875492c54d24b8fe17588934a3a0dee0ec4f',0,NULL,NULL,NULL,NULL,'Aaron','Davis','1975-12-17 23:00:00',NULL,'78 impasse de la Tourbe\n75019 Paris','','','',NULL,0,NULL,NULL,NULL,0,'aarondavis@link.eu',NULL,0,0,0,NULL,NULL,'Houston',0,'','','','QWFyb25EYXZpcw==','2010-01-06 17:41:49'),(53,1,'VidalJeremy',1,'ff42f82337017123f6442e4e262585b28092727c',0,'48d306b513b2ac314636f616747c4171700133c00d335ee6a6c3a8db60bf6725','2010-01-07 12:12:46','2010-01-07 00:12:46',NULL,'Vidal','Jeremy','1986-05-29 22:00:00',NULL,'27 rue Bombal\n19400 Argentat','0555281641','','0689539933',NULL,0,NULL,NULL,NULL,0,'vidal_j@epitech.net',NULL,0,0,0,NULL,NULL,'Aurillac',64,'','','','VmlkYWxKZXJlbXk=','2010-01-06 18:02:29'),(54,1,'FranckFarges',2,'5b396aff8f4b23708ed43632f2fae1763f5d7968',0,NULL,NULL,NULL,NULL,'Franck','Farges','0000-00-00 00:00:00',NULL,'18 avenue de la Libération\n75008 Paris','0129384756','','0656478392',NULL,0,NULL,NULL,NULL,0,'farges.franck@wanadoo.fr',NULL,0,0,0,NULL,NULL,'Tulle',0,'','','','RnJhbmNrRmFyZ2Vz','2010-01-06 17:37:13'),(55,1,'PaulGascoigne',2,'b22e95eb609d61521ce9a9d4411d1689c00ac9a6',0,NULL,NULL,NULL,NULL,'Paul','Gascoigne','0000-00-00 00:00:00',NULL,'18 Oxford Street\nLondon','00413780I089','','',NULL,0,NULL,NULL,NULL,0,'paul.gascoigne@orange.uk',NULL,0,0,0,NULL,NULL,'London',0,'','','','UGF1bEdhc2NvaWduZQ==','2010-01-06 17:39:07'),(56,1,'EricCantona',2,'2148d2c6ad2652c61b3aca1312984a57b581982a',0,NULL,NULL,NULL,NULL,'Eric','Cantona','0000-00-00 00:00:00',NULL,'4 rue Ferdinand Wisel\n75015 Paris','','','',NULL,0,NULL,NULL,NULL,0,'theking@nike.com',NULL,0,0,0,NULL,NULL,'Marseille',0,'','','','RXJpY0NhbnRvbmE=','2010-01-06 17:40:30'),(57,1,'EinsteinAlbert',2,'163ddf879bbea4d821ac3440088b06f9c368733e',0,NULL,NULL,NULL,NULL,'Einstein','Albert','0000-00-00 00:00:00',NULL,'18 rue des particules\n75000 PARIS','+451245452','','',NULL,0,NULL,NULL,NULL,0,'albert.einstein@princeton.org',NULL,0,0,0,NULL,NULL,'Wurtemberg',0,'','E=mc2','','RWluc3RlaW5BbGJlcnQ=','2010-01-06 17:40:51'),(69,1,'ValentinLeon-Bonnet',1,'6541a4daff9e1b9d047956851be28b90b6e97c6a',0,NULL,NULL,NULL,NULL,'Valentin','Leon-Bonnet','1986-05-27 22:00:00',NULL,'52 avenue du General Leclerc\n62150 Dijon','','','',NULL,0,NULL,NULL,NULL,0,'leon-b_v',NULL,0,0,0,NULL,NULL,'Dijon',0,'','','','VmFsZW50aW5MZW9uLUJvbm5ldA==','2010-01-06 18:08:13'),(68,1,'PierreLacave',1,'0e366b1632af5961cddc14b169d818923e91a9cc',0,NULL,NULL,NULL,NULL,'Pierre','Lacave','1986-11-05 23:00:00',NULL,'52 rue George Bernados\n75014 Paris','','','',NULL,0,NULL,NULL,NULL,0,'lacave_p@epitech.eu',NULL,0,0,0,NULL,NULL,'Pau',0,'','','','UGllcnJlTGFjYXZl','2010-01-06 18:05:46'),(67,1,'GildasThoraval',1,'1d204a9b19d87250c833fb76fff1dfcccedb853a',0,NULL,NULL,NULL,NULL,'Gildas','Thoraval','1984-08-16 22:00:00',NULL,'13 avenue Henry IV\n05100 Gap','0545657212','','',NULL,0,NULL,NULL,NULL,0,'thorav_g@epitech.net',NULL,0,0,0,NULL,NULL,'Gap',0,'','','','R2lsZGFzVGhvcmF2YWw=','2010-01-06 18:04:26'),(66,1,'ElliotReid',2,'7c317e29a107d4e63175521a41787f74d9231b41',0,NULL,NULL,NULL,NULL,'Elliot','Reid','1980-07-13 22:00:00',NULL,'44 avenue Eugene Lacombe\n75012 Paris','','','',NULL,1,NULL,NULL,NULL,0,'chiky@home.tz',NULL,0,0,0,NULL,NULL,'Baltimore',0,'','','','RWxsaW90UmVpZA==','2010-01-06 18:00:26'),(63,1,'HilaryCliton',2,'463151f16219de0dc48a76ad056b02eea549eaba',0,NULL,NULL,NULL,NULL,'Hilary','Cliton','0000-00-00 00:00:00',NULL,'3 rue Faux Bourg Saint Honoré\n75010 Paris','','','',NULL,1,NULL,NULL,NULL,0,'greyhouse@gov.us',NULL,0,0,0,NULL,NULL,'Washington',0,'','','','SGlsYXJ5Q2xpdG9u','2010-01-06 17:48:21'),(64,1,'PierreCury',2,'d5762d93279ac3d2f4ee2c7ca3e434e9dc8e4d58',0,NULL,NULL,NULL,NULL,'Pierre','Cury','0000-00-00 00:00:00',NULL,'18 rue Henry Barbusse\n75005 Paris','','','',NULL,0,NULL,NULL,NULL,0,'',NULL,0,0,0,NULL,NULL,'Cherbourg',0,'','','','UGllcnJlQ3VyeQ==','2010-01-06 17:53:36'),(65,1,'MarieCury',2,'edf5f78986fcfb84e5eab8ce440ce6f7a2aece0d',0,NULL,NULL,NULL,NULL,'Marie','Cury','2010-01-05 23:00:00',NULL,'18 rue Henry Barbusse\n75005 Paris','','','',NULL,1,NULL,NULL,NULL,0,'cury@tandori.in',NULL,0,0,0,NULL,NULL,'Nantes',0,'','','','TWFyaWVDdXJ5','2010-01-06 17:54:12'),(62,1,'RamakrishnanVenkatraman',2,'14ec2faaea6edce70ef3db92f8f9a29894c8550a',0,NULL,NULL,NULL,NULL,'Ramakrishnan','Venkatraman','0000-00-00 00:00:00',NULL,'INDIA','+146457456','','+634574356',NULL,0,NULL,NULL,NULL,0,'ramakrishnan@youhou.com',NULL,0,0,0,NULL,NULL,'Chidambaram',0,'','Prix nobel de Chimie 2009','','UmFtYWtyaXNobmFuVmVua2F0cmFtYW4=','2010-01-06 17:47:41'),(80,0,'PaulaDoe',4,'3e33f6674cda8a4c9105b47e468a6823a0c10ebc',0,NULL,NULL,NULL,NULL,'Paula','Doe',NULL,NULL,'','','','',NULL,1,'Cop',NULL,NULL,79,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'UGF1bGFEb2U=','2010-01-06 21:16:19'),(81,0,'PaulDoe',4,'16e456aa82254367bbac53abfdd36cf36757391b',0,NULL,NULL,NULL,NULL,'Paul','Doe',NULL,NULL,'','','','',NULL,0,'Cop',NULL,NULL,79,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'UGF1bERvZQ==','2010-01-06 21:16:19'),(82,1,'JeanAbitbol',3,'c5075d7524f0236aeb7246dbadc504335a2a7e4d',259,NULL,NULL,NULL,NULL,'Jean','Abitbol','2010-01-05 23:00:00',NULL,'34 rue des fleurs\n75020 Paris','',NULL,'0698765432',NULL,0,NULL,NULL,'Married',0,'jabitbol@usenet.net','',0,2010,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Tours',1,NULL,NULL,NULL,'SmVhbkFiaXRib2w=','2010-01-06 21:17:48'),(83,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,82,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:17:48'),(84,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,0,'',NULL,NULL,82,'',NULL,0,0,0,NULL,NULL,NULL,249,NULL,NULL,NULL,'','2010-01-06 21:17:48'),(85,1,'OlmsteadGordon',3,'1653f4ced9f77398ef6109ebd573953ac612308b',259,NULL,NULL,NULL,NULL,'Olmstead','Gordon','1974-01-05 23:00:00',NULL,'18 av secretan\n75000 PARIS','+33126543465',NULL,'+33636584257',NULL,0,NULL,NULL,'Married',0,'gordon.olmstead@orange.fr','',1,2007,2011,'','|:/:|:/||:/:|:/|1|:/:|:/|','Paris',0,NULL,NULL,NULL,'T2xtc3RlYWRHb3Jkb24=','2010-01-06 21:18:06'),(86,0,'GenevieveGordon',4,'f3bd680752745edd8779f1f746ff0774812e796e',0,NULL,NULL,NULL,NULL,'Genevieve','Gordon',NULL,NULL,'','','','',NULL,1,'Infirmiere',NULL,NULL,85,'',NULL,0,0,0,NULL,NULL,NULL,48,NULL,NULL,NULL,'R2VuZXZpZXZlR29yZG9u','2010-01-06 21:18:06'),(87,0,'HectorGordon',4,'7a631c9c688eb487413f6099c2a07dd55152b234',0,NULL,NULL,NULL,NULL,'Hector','Gordon',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33674562342',NULL,0,'Retraite',NULL,NULL,85,'gordon.hector@orange.fr',NULL,0,0,0,NULL,NULL,NULL,48,NULL,NULL,NULL,'SGVjdG9yR29yZG9u','2010-01-06 21:18:06'),(88,1,'LorenzoLama',3,'9f3a76f7a4df4b650ad3b79642bf8de6adc0a74a',259,NULL,NULL,NULL,NULL,'Lorenzo','Lama','2010-01-05 23:00:00',NULL,'23 rue du cimetière\n93210 Charleroi','',NULL,'',NULL,0,NULL,NULL,'Married',0,'','',0,2010,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Los Angeles',0,NULL,NULL,NULL,'TG9yZW56b0xhbWE=','2010-01-06 21:18:45'),(89,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,88,'',NULL,0,0,0,NULL,NULL,NULL,3,NULL,NULL,NULL,'','2010-01-06 21:18:45'),(90,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,0,'',NULL,NULL,88,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:18:45'),(91,1,'PamelaShu',3,'02a9d1a12c29f845d7f55e7af593987a0dc2e11a',259,NULL,NULL,NULL,NULL,'Pamela','Shu','2010-01-05 23:00:00',NULL,'Rue de la Gaité\n75014 Paris','',NULL,'',NULL,1,NULL,NULL,'Married',0,'','',0,2010,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','',4,NULL,NULL,NULL,'UGFtZWxhU2h1','2010-01-06 21:19:13'),(92,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,91,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:19:13'),(93,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,0,'',NULL,NULL,91,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:19:13'),(94,1,'DaveJoye',3,'1df55f6f20e051f7c681f0fb9b86b981b1efff07',259,NULL,NULL,NULL,NULL,'Dave','Joye','2010-01-05 23:00:00',NULL,'23 avenue Francis Ponge\n75017 Paris','0567895417',NULL,'',NULL,0,NULL,NULL,'Married',0,'dave_87@free.fr','',0,2010,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Limoges',0,NULL,NULL,NULL,'RGF2ZUpveWU=','2010-01-06 21:20:47'),(95,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,94,'',NULL,0,0,0,NULL,NULL,NULL,3,NULL,NULL,NULL,'','2010-01-06 21:20:47'),(96,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,0,'',NULL,NULL,94,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:20:47'),(97,1,'TimMendel',3,'1b612ebb0df716c1859a67719bb6bfa91ce4e9d6',259,NULL,NULL,NULL,NULL,'Tim','Mendel','1985-05-12 22:00:00',NULL,'18 av secretan\n75000 PARIS','+33126543465',NULL,'+33636584257',NULL,0,NULL,NULL,'Married',0,'mendel.tim@wanadoo.fr','',0,2007,2011,'','|:/:|:/|Bourse|:/:|:/|0|:/:|:/|','Paris',1,NULL,NULL,NULL,'VGltTWVuZGVs','2010-01-06 21:22:17'),(98,0,'TamMendel',4,'1769b350b7ecfd072c968e05957996ff46d8ddd2',0,NULL,NULL,NULL,NULL,'Tam','Mendel',NULL,NULL,'18 av secretan\n75000 PARIS','','','',NULL,1,'Retraite18 av secretan\n75000 PAR',NULL,NULL,97,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'VGFtTWVuZGVs','2010-01-06 21:22:17'),(99,0,'TomMendel',4,'00558ad89342d23a69c7ecf668186988b09e64b7',0,NULL,NULL,NULL,NULL,'Tom','Mendel',NULL,NULL,'18 av secretan\n75000 PARIS','+33126543465','+33253464575','+33636584257',NULL,0,'Pompier',NULL,NULL,97,'mendel.tamtom@gmail.com',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'VG9tTWVuZGVs','2010-01-06 21:22:17'),(100,1,'CarlaBruni',3,'55f1e05bc85815d7ac800f3c6ea097b399d969aa',259,NULL,NULL,NULL,NULL,'Carla','Bruni','1979-07-25 22:00:00',NULL,'18 av secretan\n75000 PARIS','+33126543465',NULL,'+33636584257',NULL,1,NULL,NULL,'Married',0,'carla.bruni@sarco.gov','',0,2006,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Paris',2,NULL,NULL,NULL,'Q2FybGFCcnVuaQ==','2010-01-06 21:25:41'),(101,0,'BrunetteBruni',4,'f022ac38b5af9c751773d866238a6559320045cf',0,NULL,NULL,NULL,NULL,'Brunette','Bruni',NULL,NULL,'','','','',NULL,1,'Danseuse',NULL,NULL,100,'',NULL,0,0,0,NULL,NULL,NULL,200,NULL,NULL,NULL,'QnJ1bmV0dGVCcnVuaQ==','2010-01-06 21:25:41'),(102,0,'BrunoBruni',4,'1c1dd45f46884c47ad4fb5a093712abe01f12327',0,NULL,NULL,NULL,NULL,'Bruno','Bruni',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33674562342',NULL,0,'Guitariste',NULL,NULL,100,'bruno@sarco.land',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'QnJ1bm9CcnVuaQ==','2010-01-06 21:25:41'),(103,1,'RemyGaillard',3,'d27a65a6c97a1f60413af5768840093b084e814b',259,NULL,NULL,NULL,NULL,'Remy','Gaillard','1982-06-09 22:00:00',NULL,'18 av secretan\n75000 PARIS','+33112335452',NULL,'+33674562342',NULL,0,NULL,NULL,'Married',0,'remy@gaillard.com','',9,2006,2011,'','|:/:|:/||:/:|:/|1|:/:|:/|','Rome',15,NULL,NULL,NULL,'UmVteUdhaWxsYXJk','2010-01-06 21:28:42'),(104,0,'GeraldineGaillard',4,'f7759f179aaa861a7f7b7aa2969ec86185e1920d',0,NULL,NULL,NULL,NULL,'Geraldine','Gaillard',NULL,NULL,'','','','',NULL,1,'None',NULL,NULL,103,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'R2VyYWxkaW5lR2FpbGxhcmQ=','2010-01-06 21:28:42'),(105,0,'CyrilGaillard',4,'1d7650e876372bb52c2bdfa968ee86a47b8840d4',0,NULL,NULL,NULL,NULL,'Cyril','Gaillard',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33636584257',NULL,0,'Cure',NULL,NULL,103,'gaillard@wanadoo.fr',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'Q3lyaWxHYWlsbGFyZA==','2010-01-06 21:28:42'),(106,1,'AlfredGuillon',3,'376c2509843beb566c3708597b1138683a0db7c5',259,NULL,NULL,NULL,NULL,'Alfred','Guillon','1995-05-13 22:00:00',NULL,'18 av secretan\n75000 PARIS','+33112335452',NULL,'+33674562342',NULL,0,NULL,NULL,'Married',0,'guillon@alfred.gov','',0,1991,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Pontoise',1,NULL,NULL,NULL,'QWxmcmVkR3VpbGxvbg==','2010-01-06 21:31:33'),(107,0,'CharlotteGuillon',4,'dfdbf0b02f354f1e9a3cfef4b3639faad26f8cac',0,NULL,NULL,NULL,NULL,'Charlotte','Guillon',NULL,NULL,'','','','',NULL,1,'Postier',NULL,NULL,106,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'Q2hhcmxvdHRlR3VpbGxvbg==','2010-01-06 21:31:33'),(108,0,'RemyGuillon',4,'7d4119e95fc00d1d611d62a654e6d215e9cda6d8',0,NULL,NULL,NULL,NULL,'Remy','Guillon',NULL,NULL,'18 av secretan\n75000 PARIS','+33126543465','+33253464575','+33674562342',NULL,0,'Retraite',NULL,NULL,106,'guillon@orange.fr',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'UmVteUd1aWxsb24=','2010-01-06 21:31:33'),(109,1,'CecilleBisson',3,'ef9e9743e06e0ec4eda846006dabbd26eb1163a7',259,NULL,NULL,NULL,NULL,'Cecille','Bisson','1983-07-09 22:00:00',NULL,'18 av secretan\n75000 PARIS','+33126543465',NULL,'+33674562342',NULL,1,NULL,NULL,'Deceaded',0,'cecile@bisson.fr','',0,2004,2011,'','|:/:|:/||:/:|:/|1|:/:|:/|','Pigalle',0,NULL,NULL,NULL,'Q2VjaWxsZUJpc3Nvbg==','2010-01-06 21:34:17'),(110,0,'',4,'da39a3ee5e6b4b0d3255bfef95601890afd80709',0,NULL,NULL,NULL,NULL,'','',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,109,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'','2010-01-06 21:34:17'),(111,0,'ArnaudBisson',4,'6911965812eea55cdeb0a1fe720e9f20ba896e2d',0,NULL,NULL,NULL,NULL,'Arnaud','Bisson',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33674562342',NULL,0,'Facteur',NULL,NULL,109,'bisson@arnaud.org',NULL,0,0,0,NULL,NULL,NULL,81,NULL,NULL,NULL,'QXJuYXVkQmlzc29u','2010-01-06 21:34:17'),(112,1,'PetterPetterson',3,'5fa0cddd81dbd86afffc14c21d08f0035ac3c45e',259,NULL,NULL,NULL,NULL,'Petter','Petterson','1997-03-04 23:00:00',NULL,'18 av secretan\n75000 PARIS','+33112335452',NULL,'+33674562342',NULL,0,NULL,NULL,'Other',0,'petter.petterson@truc.fr','',0,1992,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','St Petersbourg',0,NULL,NULL,NULL,'UGV0dGVyUGV0dGVyc29u','2010-01-06 21:39:53'),(113,0,'NanaPetterson',4,'58dd68d000f4ee0824b5f6f62c18f0eca62f4c3f',0,NULL,NULL,NULL,NULL,'Nana','Petterson',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33636584257',NULL,1,'Libraire',NULL,NULL,112,'nana@tomtom.fr',NULL,0,0,0,NULL,NULL,NULL,48,NULL,NULL,NULL,'TmFuYVBldHRlcnNvbg==','2010-01-06 21:39:53'),(114,0,'TomTomPetterson',4,'29084c964f7be72506bb806025e6932d931e30c3',0,NULL,NULL,NULL,NULL,'TomTom','Petterson',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33636584257',NULL,0,'Ecrivain',NULL,NULL,112,'tomtom@nana.fr',NULL,0,0,0,NULL,NULL,NULL,48,NULL,NULL,NULL,'VG9tVG9tUGV0dGVyc29u','2010-01-06 21:39:53'),(115,1,'VincentVan Gogh',3,'66408975e891927e38d3a15824f6ae9a39b0bd5e',259,NULL,NULL,NULL,NULL,'Vincent','Van Gogh','1999-03-07 23:00:00',NULL,'18 av secretan\n75000 PARIS','+33112335452',NULL,'+33674562342',NULL,0,NULL,NULL,'Married',0,'vincent@vangogh.com','',0,2007,2011,'','|:/:|:/||:/:|:/|0|:/:|:/|','Pise',0,NULL,NULL,NULL,'VmluY2VudFZhbiBHb2do','2010-01-06 21:42:21'),(116,0,'PauletteVan Gogh',4,'e97353ef8983dc27ba25bd0638f8550b6c8aa009',0,NULL,NULL,NULL,NULL,'Paulette','Van Gogh',NULL,NULL,'','','','',NULL,1,'Femme de menage',NULL,NULL,115,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'UGF1bGV0dGVWYW4gR29naA==','2010-01-06 21:42:21'),(117,0,'EricVan Gogh',4,'52fa096857c00be0d270dc45af5a5a3087656ef9',0,NULL,NULL,NULL,NULL,'Eric','Van Gogh',NULL,NULL,'18 av secretan\n75000 PARIS','+33126543465','+33253464575','+33674562342',NULL,0,'Artiste',NULL,NULL,115,'vangogh@horus-edu.net',NULL,0,0,0,NULL,NULL,NULL,145,NULL,NULL,NULL,'RXJpY1ZhbiBHb2do','2010-01-06 21:42:21'),(118,1,'JeannetteMorison',3,'c16d67cf6e9d92c092726b7fa0b02e98d859b53e',259,NULL,NULL,NULL,NULL,'Jeannette','Morison','1997-05-09 22:00:00',NULL,'18 av secretan\n75000 PARIS','+33112335452',NULL,'+33674562342',NULL,1,NULL,NULL,'Married',0,'jeanette@morison.com','',0,2008,2012,'','|:/:|:/||:/:|:/|0|:/:|:/|','St pantelllion',0,NULL,NULL,NULL,'SmVhbm5ldHRlTW9yaXNvbg==','2010-01-06 21:46:16'),(119,0,'JeanneMorison',4,'d1526e7b83614d67a07ca16dde0e7109d2234450',0,NULL,NULL,NULL,NULL,'Jeanne','Morison',NULL,NULL,'','','','',NULL,1,'',NULL,NULL,118,'',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'SmVhbm5lTW9yaXNvbg==','2010-01-06 21:46:16'),(120,0,'JimMorison',4,'5ae842779a3bcc9f106cefc496b5dea965bb1264',0,NULL,NULL,NULL,NULL,'Jim','Morison',NULL,NULL,'18 av secretan\n75000 PARIS','+33112335452','+33253464575','+33674562342',NULL,0,'Chanteur',NULL,NULL,118,'morison@gordon.com',NULL,0,0,0,NULL,NULL,NULL,0,NULL,NULL,NULL,'SmltTW9yaXNvbg==','2010-01-06 21:46:16'),(121,1,'profdemo',2,'c378515717cf2441c4ae7137e951fca3bd237266',0,'','0000-00-00 00:00:00','2010-01-07 00:28:04',NULL,'prof','demo','2010-01-05 23:00:00',NULL,'','','','',NULL,0,NULL,NULL,NULL,0,'',NULL,0,0,0,NULL,NULL,'',65,'','','','cHJvZmRlbW8=','2010-01-06 22:10:24');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `white_board`
--

DROP TABLE IF EXISTS `white_board`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `white_board` (
  `id_tree` int(11) NOT NULL,
  `mode` int(1) NOT NULL,
  `items` blob,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id_tree`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `white_board`
--

LOCK TABLES `white_board` WRITE;
/*!40000 ALTER TABLE `white_board` DISABLE KEYS */;
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

-- Dump completed on 2010-01-07  1:37:44
