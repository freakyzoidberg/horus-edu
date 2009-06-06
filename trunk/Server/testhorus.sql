-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Serveur: localhost
-- Généré le : Sam 06 Juin 2009 à 16:27
-- Version du serveur: 5.0.70
-- Version de PHP: 5.2.9-pl2-gentoo

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `testhorus`
--

-- --------------------------------------------------------

--
-- Structure de la table `files`
--

CREATE TABLE IF NOT EXISTS `files` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `mime` varchar(64) NOT NULL,
  `size` int(11) NOT NULL,
  `id_tree` int(11) NOT NULL,
  `id_owner` int(11) NOT NULL,
  `ctime` timestamp NOT NULL default '0000-00-00 00:00:00',
  `mtime` timestamp NOT NULL default '0000-00-00 00:00:00',
  `hash_sha1` varchar(40) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `id_ower` (`id_owner`),
  KEY `id_tree` (`id_tree`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=261 ;

--
-- Contenu de la table `files`
--

INSERT INTO `files` (`id`, `name`, `mime`, `size`, `id_tree`, `id_owner`, `ctime`, `mtime`, `hash_sha1`) VALUES
(1, 'Histoire de la Chine', 'x-horus/x-lesson', 0, 241, 3, '2009-06-01 07:15:40', '2009-06-01 07:15:40', ''),
(2, 'Histoire de costume', 'x-horus/x-lesson', 0, 241, 3, '2009-06-01 17:38:29', '2009-06-01 17:38:29', ''),
(3, 'Tectonique des plaques', 'x-horus/x-lesson', 0, 243, 3, '2009-06-01 17:39:57', '2009-06-01 17:39:57', ''),
(4, 'Reglement interieur.pdf', 'application/pdf', 0, 258, 4, '2009-06-06 11:44:20', '2009-06-06 11:44:20', ''),
(259, 'Decharge de responsabilitee.pdf', 'application/pdf', 0, 256, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', ''),
(260, 'Fiche descriptive.pdf', 'application/pdf', 0, 257, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', ''),
(42, 'Chine.pdf', 'application/pdf', 0, 3, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', '');

-- --------------------------------------------------------

--
-- Structure de la table `settings`
--

CREATE TABLE IF NOT EXISTS `settings` (
  `user` int(11) NOT NULL,
  `plugin` varchar(255) NOT NULL,
  `scope` int(1) NOT NULL,
  `value` blob,
  KEY `user` (`user`),
  KEY `module` (`plugin`),
  KEY `scope` (`scope`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `settings`
--

INSERT INTO `settings` (`user`, `plugin`, `scope`, `value`) VALUES
(3, 'test', 0, 0x0000000a00000000080074006500730074),
(4, '', 0, 0x0000000a0000000000);

-- --------------------------------------------------------

--
-- Structure de la table `tree`
--

CREATE TABLE IF NOT EXISTS `tree` (
  `id` int(11) NOT NULL auto_increment,
  `typeofnode` varchar(42) NOT NULL,
  `name` varchar(128) NOT NULL,
  `user_ref` int(11) NOT NULL default '0',
  `id_parent` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=259 ;

--
-- Contenu de la table `tree`
--

INSERT INTO `tree` (`id`, `typeofnode`, `name`, `user_ref`, `id_parent`) VALUES
(1, 'CLASSES', 'Classes', 0, 0),
(2, 'GROUP', 'Professeurs', 0, 0),
(3, 'GRADE', '6eme', 0, 1),
(237, 'GRADE', '5eme', 0, 1),
(238, 'GRADE', '4eme', 0, 1),
(239, 'GRADE', '3eme', 0, 1),
(240, 'SUBJECT', 'Maths', 0, 3),
(241, 'SUBJECT', 'Histoire', 0, 245),
(242, 'SUBJECT', 'Physique', 0, 3),
(243, 'SUBJECT', 'Geographie', 0, 245),
(244, 'SUBJECT', 'Francais', 0, 3),
(245, 'SUBJECT', 'Histoire / Geo', 0, 3),
(0, 'ROOT', 'College Vauban', 0, 0),
(247, 'GROUP', 'Eleves', 0, 0),
(248, 'SUBJECT', 'SVT', 0, 237),
(249, 'SUBJECT', 'Sport', 0, 237),
(250, 'SUBJECT', 'Histoire / Geo', 0, 237),
(251, 'SUBJECT', 'Francais', 0, 237),
(252, 'SUBJECT', 'Histoire', 0, 250),
(253, 'SUBJECT', 'Geographie', 0, 250),
(254, 'GROUP', 'Administration', 0, 0),
(255, 'GROUP', 'Groups', 0, 0),
(256, 'GROUP', 'Sortie Pedagogiques', 0, 255),
(257, 'GROUP', 'Citee de l''espace Avril 2009', 0, 256),
(258, '', 'Documents generaux', 0, 0);

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL auto_increment,
  `enabled` tinyint(1) NOT NULL default '1',
  `login` varchar(32) NOT NULL,
  `level` tinyint(1) NOT NULL,
  `password` char(40) NOT NULL,
  `session_key` char(64) default NULL,
  `session_end` timestamp NULL default NULL,
  `last_login` timestamp NULL default NULL,
  `surname` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `birth_date` timestamp NOT NULL default '0000-00-00 00:00:00',
  `picture` blob NOT NULL,
  `address` varchar(255) NOT NULL,
  `phone` varchar(32) NOT NULL,
  `country` varchar(32) NOT NULL,
  `language` varchar(32) NOT NULL,
  `id_tree` int(11) NOT NULL default '-1',
  PRIMARY KEY  (`id`),
  KEY `level` (`level`),
  KEY `login` (`login`),
  KEY `enabled` (`enabled`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=83 ;

--
-- Contenu de la table `users`
--

INSERT INTO `users` (`id`, `enabled`, `login`, `level`, `password`, `session_key`, `session_end`, `last_login`, `surname`, `name`, `birth_date`, `picture`, `address`, `phone`, `country`, `language`, `id_tree`) VALUES
(4, 1, 'toto', 0, '0b9c2625dc21ef05f6ad4ddf47c5f203837aa32c', 'e89df03f04b5d4cd347ca2caa36414871fa46ae3cc7c7d739d3e9263820cf31e', '0000-00-00 00:00:00', '0000-00-00 00:00:00', 'sdfsdfsdfsdf', 'sfdsfdsfdsfs', '2009-06-06 00:00:00', 0x76696465, 'sdfsdfsdf', 'dfsdfsdfsd', 'ssdfsdfsdfsdf', 'sd', 0),
(5, 1, 'val', 0, '39f69c278f46165447f30d10acf54277aaa3d5fc', '413f8ba5a7647fece38e8621f876f02422f37cf078eee4fc531c1944716a4d25', '0000-00-00 00:00:00', NULL, '', '', '0000-00-00 00:00:00', '', '90p9p09', '90p90', '90p90p', 'p0', 0),
(6, 1, 'git', 0, '46f1a0bd5592a2f9244ca321b129902a06b53e03', 'ddb3f408c77a519ae38b0e9d49f95ffd6db3f58d534a94af837866b4be610d03', '0000-00-00 00:00:00', NULL, '', '', '0000-00-00 00:00:00', '', '', '', '', '', 0),
(7, 1, 'pierre', 4, 'pierre', NULL, '2009-06-05 20:36:00', NULL, '', '', '0000-00-00 00:00:00', '', '25, rue du cul', '0612542323', 'China', 'ch', 9),
(32, 1, 'Valentin', 3, '39f69c278f46165447f30d10acf54277aaa3d5fc', NULL, '2009-06-06 15:23:06', NULL, 'Val', 'Entin', '2009-06-06 00:00:00', 0x76696465, '25, rue machin', '0123456789', 'Chine', 'Chongqinghua', 3),
(54, 1, 'AbdEr', 3, 'c374c48b268e999230e206a5ed840004a9926148', 'd861660d2a81b6b11267b6baa2c8cb9cfce5dceeacef09b4b22d1d6160dec399', '2009-06-06 15:23:19', NULL, 'Abder', 'N', '2009-06-06 00:00:00', 0x76696465, '25, rue convention', '0142424242', 'France', 'Chinois', 3),
(55, 1, 'Professeur', 2, 'e718ab41a00fe697cc1973be2104f5df4ed0b538', NULL, NULL, NULL, 'Jean', 'Luc', '2009-06-06 00:00:00', 0x76696465, '25, rue toto', '0123454565', 'France', 'Francais', 9),
(64, 1, 'Mamadou', 3, 'd3febce94dd80a8620557479f409dc8a5594b510', NULL, NULL, NULL, 'Mamadou', 'Mamadou', '2009-06-06 00:00:00', 0x76696465, 'Mamadou', 'Mamadou', 'Mamadou', 'Mamadou', 0),
(56, 1, 'Pierre', 2, '8ce4081e7eea6ace8332c7eb78415c57ec6ef2e3', NULL, NULL, NULL, 'Pierre', 'Pierre', '2009-06-06 00:00:00', 0x76696465, 'Pierre', 'Pierre', 'Pierre', 'Pierre', 9),
(58, 1, 'Jerem', 2, '8d65594256bf4c57aa9778a78fc5b08e975f8040', NULL, NULL, NULL, 'Jerem', 'Jerem', '2009-06-06 00:00:00', 0x76696465, 'Jerem', 'Jerem', 'Jerem', 'Jerem', 9),
(59, 1, 'Roumain', 2, 'e29a872af4795a630b7a7621ca4d99fcfb1151e7', NULL, NULL, NULL, 'Roumain', 'Roumain', '2009-06-06 00:00:00', 0x76696465, 'Roumain', 'Roumain', 'Roumain', 'Roumain', 9),
(60, 1, 'adrien', 2, '4d10829f147c13c63c4579f5297a87efba1143a3', NULL, NULL, NULL, 'adrien', 'adrien', '2009-06-06 00:00:00', 0x76696465, 'adrien', 'adrien', 'adrien', 'adrien', 9),
(61, 1, 'gildas', 2, '368a5a5d095c9a1a6aef9c51517545cc126e6142', NULL, NULL, NULL, 'gildas', 'gildas', '2009-06-06 00:00:00', 0x76696465, 'gildas', 'gildas', 'gildas', 'gildas', 9),
(62, 1, 'Jean', 2, 'f7ed376ba27377ae2680fafe1a67037df80b7e36', NULL, NULL, NULL, 'Jean', 'Jean', '2009-06-06 00:00:00', 0x76696465, 'Jean', 'Jean', 'Jean', 'Jean', 9),
(63, 1, 'lacave', 2, '2d015eca25fd336891782abaf1f41ed563d68732', NULL, NULL, NULL, 'lacave', 'lacave', '2009-06-06 00:00:00', 0x76696465, 'lacave', 'lacave', 'lacave', 'lacave', 9),
(65, 1, 'Mouloud', 2, '079649a62b156d1619e03fa518867684a5119991', NULL, NULL, NULL, 'Mouloud', 'Mouloud', '2009-06-06 00:00:00', 0x76696465, 'Mouloud', 'Mouloud', 'Mouloud', 'Mouloud', 9),
(67, 1, 'nanouc_a', 2, 'fe3e2ee496e39e843ae8180479432c240c88190e', NULL, NULL, NULL, 'nanouc_a', 'nanouc_a', '2009-06-06 00:00:00', 0x76696465, 'nanouc_a', 'nanouc_a', 'nanouc_a', 'nanouc_a', 9),
(68, 1, 'vidal', 2, '5431a5ce02fa3c14c98aa025fc8454045c65b65d', NULL, NULL, NULL, 'vidal', 'vidal', '2009-06-06 00:00:00', 0x76696465, 'vidal', 'vidal', 'vidal', 'vidal', 9),
(69, 1, 'etud6', 3, '2c404ec3d3eb2a922a8e301a1f237ad1e7f7eb58', NULL, '2009-06-06 15:23:28', NULL, 'Etudiant', '6eme', '0000-00-00 00:00:00', '', '', '', '', '', 237),
(70, 1, 'etud5', 3, '99bf77682cc85d95068b537948e43eff99d7b6f3', NULL, '2009-06-06 14:47:47', NULL, 'Etudiant', '5eme', '2009-06-06 00:00:00', 0x76696465, 'sqdqsdsqd', 'qsdsqdqsdqsdqs', 'qdqsd', 'sqsdsqdqsdq', 237),
(71, 1, 'TEST', 3, '984816fd329622876e14907634264e6f332e9fb3', NULL, NULL, NULL, 'TEST', 'TEST', '2009-06-06 00:00:00', 0x76696465, 'TEST', 'TEST', 'TEST', 'TEST', 0),
(72, 1, 'qdsqdqsd', 3, 'd51ea2ad79b66fe22badd2f47f988c015b0b7d2d', NULL, NULL, NULL, 'dsqdsqdsq', 'dsqdqsds', '2009-06-06 00:00:00', 0x76696465, 'sqdqsdqs', 'qdsqdd', 'dsqdqsd', 'qsdqsdqsdqs', 238),
(73, 0, 'sqdsqdqsd', 3, 'bb6cd1c6aad310e67daa039eb5411e0156429fcd', NULL, NULL, NULL, 'dqsdqsdsq', 'dqsdqsd', '2009-06-06 00:00:00', 0x76696465, 'dqsdqsd', 'qsdqsdqsd', 'dqsdsqdsqd', 'qsdqsdqsd', 237),
(74, 0, 'qdsqdqsdq', 3, 'f3034542e6d5b4eb7d18030b57299f881614303a', NULL, NULL, NULL, 'sqdsq', 'dqsdqsd', '2009-06-06 00:00:00', 0x76696465, 'qsdqsdqsdsqdqsd', 'qsdsqd', 'sqdqsdqsd', 'sqdqsdqs', 74),
(75, 1, 'dqsdsqd', 3, '4452dfc3ae28e5216d5c7db327414aa50b1d61b1', NULL, NULL, NULL, 'qsddqsdqsd', 'qsdqsd', '2009-06-06 00:00:00', 0x76696465, 'qsdsqdqdsq', 'sdqsdsqd', 'dqsdsqd', 'qsdqs', 239),
(76, 1, 'sqdqsd', 3, '9e4b431b136ff19ade660348d358622e16c58e10', NULL, NULL, NULL, 'dqsdsqdsq', 'dsqdsq', '2009-06-06 00:00:00', 0x76696465, 'qsdsq', 'dqsdsqd', 'dqsdsqdqs', 'qsdsqdqq', 238),
(77, 1, 'sdqsdsq', 2, '1149237dabc45f6388ae870d4cc5c15ebc0353da', NULL, NULL, NULL, 'sqdsqdqs', 'sqdqsdsqd', '2009-06-06 00:00:00', 0x76696465, 'dsqdqs', 'qsdqsdqs', 'dsqdqsd', 'sqdqsdqsdqsd', 9),
(78, 1, 'qsdqsdqsdqsqsd', 2, 'd51ea2ad79b66fe22badd2f47f988c015b0b7d2d', NULL, NULL, NULL, 'sdqsdsqd', 'qsdqsdqsd', '2009-06-06 00:00:00', 0x76696465, 'qsdqsdqsd', 'qsdsqdssdqdsqd', 'dsqdqsdsqd', 'sqdsqd', 9),
(79, 1, 'gfdgfdhgfhgfjfjhgjgh', 2, '1a6aabef5068ae5669ab009cdcb98d3426b8520f', NULL, NULL, NULL, 'hjghjghjg', 'hjghjghjg', '2009-06-06 00:00:00', 0x76696465, 'hjghjghjg', 'hjghjghjg', 'hjghjghjg', 'hjghjghjg', 9),
(80, 1, 'qsdsqdsq', 2, 'e3bd07ef265d649332334e4f6a9ca49b9c894a3e', NULL, NULL, NULL, 'dqsdqsdsqdsqd', 'sqdsqdqsd', '2009-06-06 00:00:00', 0x76696465, 'dsqdqsdsq', 'sqdsqdsqdsqdsqd', 'dsqdsqdsq', 'dsqdqsdsqdqsd', 9),
(81, 1, 'sqdsqdsqdqs', 3, '64cb8701814cd4bd4a8ba8e75acd4169777d209b', NULL, NULL, NULL, 'dqdsqdsq', 'dqsdqsdsqd', '2009-06-06 00:00:00', 0x76696465, 'dqsdqsdqs', 'sqdsqdqs', 'dqsdsq', 'dqsdqsdqsd', 239),
(82, 1, 'qsdsqdsqd', 2, '2e6c9bb179482ebd59cb07e49ac42a75790434ad', NULL, NULL, NULL, 'dsqdsqqsdqsdqsdqsdqsdqsdqsqsdsqdqsd', 'qsdqdqsdsq', '2009-06-06 00:00:00', 0x76696465, 'sqdsqdsqd', 'dsqdsqd', 'sqdqdsqdsqd', 'sqdsqdsqdq', 9);

-- --------------------------------------------------------

--
-- Structure de la table `user_has_group`
--

CREATE TABLE IF NOT EXISTS `user_has_group` (
  `id_user` int(11) NOT NULL,
  `id_group` int(11) NOT NULL,
  KEY `id_user` (`id_user`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `user_has_group`
--

INSERT INTO `user_has_group` (`id_user`, `id_group`) VALUES
(3, 6);
