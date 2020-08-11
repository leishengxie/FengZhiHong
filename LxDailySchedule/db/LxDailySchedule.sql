/*
 Navicat MySQL Data Transfer

 Source Server         : 本地mysql
 Source Server Type    : MySQL
 Source Server Version : 50537
 Source Host           : localhost:3306
 Source Schema         : LxDailySchedule

 Target Server Type    : MySQL
 Target Server Version : 50537
 File Encoding         : 65001

 Date: 09/08/2020 10:54:23
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for tDailySchedule
-- ----------------------------
DROP TABLE IF EXISTS `tDailySchedule`;
CREATE TABLE `tDailySchedule`  (
  `id` int(11) NOT NULL,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `create_date_time` datetime NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for tDailyScheduleBook
-- ----------------------------
DROP TABLE IF EXISTS `tDailyScheduleBook`;
CREATE TABLE `tDailyScheduleBook`  (
  `id` int(11) NOT NULL,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `create_date_time` datetime NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for tScheduleItem
-- ----------------------------
DROP TABLE IF EXISTS `tScheduleItem`;
CREATE TABLE `tScheduleItem`  (
  `id` int(11) NOT NULL,
  `schedule_id` int(11) NOT NULL,
  `start_time` time NULL DEFAULT NULL,
  `end_time` time NULL DEFAULT NULL,
  `content` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `use_alarm_clock` tinyint(1) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_schedule_id`(`schedule_id`) USING BTREE,
  CONSTRAINT `fk_schedule_id` FOREIGN KEY (`schedule_id`) REFERENCES `tdailyschedule` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

SET FOREIGN_KEY_CHECKS = 1;
