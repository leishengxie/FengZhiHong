/*
Navicat MySQL Data Transfer

Source Server         : localTest
Source Server Version : 50537
Source Host           : localhost:3306
Source Database       : lxdairy

Target Server Type    : MYSQL
Target Server Version : 50537
File Encoding         : 65001

Date: 2019-12-27 19:24:31
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for tapasswd
-- ----------------------------
DROP TABLE IF EXISTS `tapasswd`;
CREATE TABLE `tapasswd` (
  `aid` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `item` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `account` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `passwd` varchar(16) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`aid`),
  KEY `fk_tAPasswd_uid` (`uid`),
  CONSTRAINT `fk_tAPasswd_uid` FOREIGN KEY (`uid`) REFERENCES `tuser` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of tapasswd
-- ----------------------------

-- ----------------------------
-- Table structure for tdairy
-- ----------------------------
DROP TABLE IF EXISTS `tdairy`;
CREATE TABLE `tdairy` (
  `did` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `title` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `wirte_datetime` datetime DEFAULT NULL,
  `weather` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `tag` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `content` text COLLATE utf8_bin,
  PRIMARY KEY (`did`),
  KEY `fk_tDairy_uid` (`uid`),
  CONSTRAINT `fk_tDairy_uid` FOREIGN KEY (`uid`) REFERENCES `tuser` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of tdairy
-- ----------------------------

-- ----------------------------
-- Table structure for tjoke
-- ----------------------------
DROP TABLE IF EXISTS `tjoke`;
CREATE TABLE `tjoke` (
  `jid` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(32) COLLATE utf8_bin NOT NULL,
  `create_datetime` datetime DEFAULT NULL,
  `content` text COLLATE utf8_bin,
  `original` tinyint(4) NOT NULL,
  `up_uid` int(11) NOT NULL,
  `nickname` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `total_rating_people` int(11) DEFAULT '0',
  `total_rating_score` double DEFAULT '0',
  `average_rating_score` double DEFAULT '0',
  PRIMARY KEY (`jid`),
  KEY `fk_tJoke_up_uid` (`up_uid`),
  CONSTRAINT `fk_tJoke_up_uid` FOREIGN KEY (`up_uid`) REFERENCES `tuser` (`uid`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of tjoke
-- ----------------------------
INSERT INTO `tjoke` VALUES ('2', 'hello', '2019-12-24 18:08:43', 0x6162636465666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, '0', '1', 'leisx', '1', '2.05', '2.05');
INSERT INTO `tjoke` VALUES ('3', '12345', '2019-12-25 14:48:48', 0x6861707079206E6577207965617221, '0', '1', 'leisx', '1', '3.9', '3.9');
INSERT INTO `tjoke` VALUES ('4', '12345', '2019-12-25 14:51:00', 0x6861707079206E6577207965617221, '0', '1', 'leisx', '1', '5', '5');
INSERT INTO `tjoke` VALUES ('5', '很好', '2019-12-25 15:23:43', 0xE4BB8AE5A4A9E5A4A9E6B094E5BE88E5A5BD, '0', '1', 'leisx', '1', '3.05', '3.05');
INSERT INTO `tjoke` VALUES ('6', '1', '2019-12-25 17:38:03', 0x313131, '0', '1', 'leisx', '1', '2.85', '2.85');
INSERT INTO `tjoke` VALUES ('7', '6', '2019-12-27 18:32:56', 0x3636, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('8', '7', '2019-12-27 18:33:06', 0x3737, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('9', '8', '2019-12-27 18:33:17', 0x3737, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('10', '也一样', '2019-12-27 18:33:28', 0x3737, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('11', '啦啦啦', '2019-12-27 18:33:39', 0x3737, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('12', '哈哈哈', '2019-12-27 18:33:48', 0x3737, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('13', '12', '2019-12-27 18:36:18', 0x35353535, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('14', '333', '2019-12-27 18:38:31', 0x35353535, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('15', '1444', '2019-12-27 18:39:10', 0x3333, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('16', '66', '2019-12-27 18:39:23', 0x3333, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('17', '9999', '2019-12-27 18:45:06', 0x39393939, '0', '1', 'leisx', '0', '0', '0');
INSERT INTO `tjoke` VALUES ('18', '1000', '2019-12-27 18:45:33', 0x39393939, '0', '1', 'leisx', '1', '3.4', '3.4');
INSERT INTO `tjoke` VALUES ('19', '999', '2019-12-27 18:54:21', 0x3636, '0', '1', 'leisx', '1', '2.25', '2.25');

-- ----------------------------
-- Table structure for tjokerating
-- ----------------------------
DROP TABLE IF EXISTS `tjokerating`;
CREATE TABLE `tjokerating` (
  `jid` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `rating` double(11,0) NOT NULL,
  PRIMARY KEY (`jid`,`uid`),
  KEY `fk_tJokeRating_uid` (`uid`),
  CONSTRAINT `fk_tJokeRating_jid` FOREIGN KEY (`jid`) REFERENCES `tjoke` (`jid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_tJokeRating_uid` FOREIGN KEY (`uid`) REFERENCES `tuser` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of tjokerating
-- ----------------------------
INSERT INTO `tjokerating` VALUES ('2', '1', '2');
INSERT INTO `tjokerating` VALUES ('3', '1', '4');
INSERT INTO `tjokerating` VALUES ('4', '1', '5');
INSERT INTO `tjokerating` VALUES ('5', '1', '3');
INSERT INTO `tjokerating` VALUES ('6', '1', '3');
INSERT INTO `tjokerating` VALUES ('18', '1', '3');
INSERT INTO `tjokerating` VALUES ('19', '1', '2');

-- ----------------------------
-- Table structure for tuser
-- ----------------------------
DROP TABLE IF EXISTS `tuser`;
CREATE TABLE `tuser` (
  `uid` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(32) COLLATE utf8_bin NOT NULL,
  `passwd` varchar(16) COLLATE utf8_bin NOT NULL,
  `nick_name` varchar(32) COLLATE utf8_bin DEFAULT NULL,
  `phone_no` varchar(16) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of tuser
-- ----------------------------
INSERT INTO `tuser` VALUES ('1', 'leisx', '0406aaaaa', 'leisx', null);

-- ----------------------------
-- Procedure structure for proc_joke_rating
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_joke_rating`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `proc_joke_rating`(IN `i_jid` int,IN `i_uid` int,IN `i_rating` double)
BEGIN
	#Routine body goes here...
DECLARE bExist TINYINT default 0;
DECLARE var_total_rating_people int default 0;
DECLARE var_total_rating_score double default 0;
DECLARE var_average_rating_score double default 0;

DECLARE t_error int DEFAULT 0;
DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET t_error=1;

	select count(1) into bExist from tjokerating where jid=i_jid and uid=i_uid;
# 开始事务
START TRANSACTION; 
	if bExist
	then
	update tJokeRating set rating=i_rating where jid=i_jid and uid=i_uid;
else
INSERT INTO tJokeRating(jid, uid, rating) VALUES(i_jid, i_uid, i_rating);

end if;

# select COUNT(1) into var_total_rating_people from tjokerating where jid=i_jid;
#	set @var_total_rating_score = (select SUM(rating) from tjokerating where jid=i_jid);
#	set @var_average_rating_score = var_total_rating_people / var_total_rating_score;
update tJoke, (select COUNT(1) as r_count from tjokerating where jid=i_jid) as t1, (select SUM(rating) as r_rating from tjokerating where jid=i_jid) as t2 set total_rating_people=t1.r_count, total_rating_score=t2.r_rating, average_rating_score = r_rating / r_count WHERE jid=i_jid;

IF t_error = 1 THEN    
            ROLLBACK;    
        ELSE    
            COMMIT;    
        END IF;

END
;;
DELIMITER ;
