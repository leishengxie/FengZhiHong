/*
Navicat SQLite Data Transfer

Source Server         : LxDairy
Source Server Version : 30808
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30808
File Encoding         : 65001

Date: 2019-12-09 18:21:18
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for sqlite_sequence
-- ----------------------------
DROP TABLE IF EXISTS "main"."sqlite_sequence";
CREATE TABLE sqlite_sequence(name,seq);

-- ----------------------------
-- Records of sqlite_sequence
-- ----------------------------
INSERT INTO "main"."sqlite_sequence" VALUES ('_tUser_old_20190912', 0);
INSERT INTO "main"."sqlite_sequence" VALUES ('tUser', 2);
INSERT INTO "main"."sqlite_sequence" VALUES ('_tDairy_old_20190918_1', 0);
INSERT INTO "main"."sqlite_sequence" VALUES ('_tDairy_old_20190918_2', 0);
INSERT INTO "main"."sqlite_sequence" VALUES ('_tDairy_old_20190919', 0);
INSERT INTO "main"."sqlite_sequence" VALUES ('tDairy', 0);

-- ----------------------------
-- Table structure for tDairy
-- ----------------------------
DROP TABLE IF EXISTS "main"."tDairy";
CREATE TABLE "tDairy" (
"did"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1,
"uid"  INTEGER NOT NULL,
"title"  TEXT,
"datetime"  TEXT,
"weather"  TEXT,
"tag"  TEXT,
"content"  TEXT,
CONSTRAINT "fk_user_uid" FOREIGN KEY ("uid") REFERENCES "tUser" ("uid") ON DELETE CASCADE ON UPDATE CASCADE
);

-- ----------------------------
-- Records of tDairy
-- ----------------------------

-- ----------------------------
-- Table structure for tJoke
-- ----------------------------
DROP TABLE IF EXISTS "main"."tJoke";
CREATE TABLE "tJoke" (
"jid"  INTEGER NOT NULL,
"title"  TEXT NOT NULL,
"datetime"  TEXT NOT NULL,
"content"  TEXT NOT NULL,
"original"  BLOB NOT NULL,
"up_uid"  INTEGER,
"nickname"  TEXT NOT NULL,
"total_rating_people"  INTEGER,
"total_rating_score"  REAL,
"average_rating_score"  REAL,
PRIMARY KEY ("jid" ASC)
);

-- ----------------------------
-- Records of tJoke
-- ----------------------------

-- ----------------------------
-- Table structure for tJokeRating
-- ----------------------------
DROP TABLE IF EXISTS "main"."tJokeRating";
CREATE TABLE "tJokeRating" (
"jid"  INTEGER NOT NULL,
"uid"  INTEGER NOT NULL,
"rating"  REAL NOT NULL,
PRIMARY KEY ("jid", "uid" ASC),
CONSTRAINT "fk_jid" FOREIGN KEY ("jid") REFERENCES "tJoke" ("jid") ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT "fk_uid" FOREIGN KEY ("uid") REFERENCES "tUser" ("uid") ON DELETE CASCADE ON UPDATE CASCADE
);

-- ----------------------------
-- Records of tJokeRating
-- ----------------------------

-- ----------------------------
-- Table structure for tUser
-- ----------------------------
DROP TABLE IF EXISTS "main"."tUser";
CREATE TABLE "tUser" (
"uid"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1,
"user_name"  TEXT(32) NOT NULL,
"passwd"  TEXT(16) NOT NULL
);

-- ----------------------------
-- Records of tUser
-- ----------------------------

-- ----------------------------
-- Table structure for _tDairy_old_20190918
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tDairy_old_20190918";
CREATE TABLE "_tDairy_old_20190918" (
"Did"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"title"  TEXT,
"weather"  TEXT,
"tag"  TEXT,
"content"  TEXT
);

-- ----------------------------
-- Records of _tDairy_old_20190918
-- ----------------------------

-- ----------------------------
-- Table structure for _tDairy_old_20190918_1
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tDairy_old_20190918_1";
CREATE TABLE "_tDairy_old_20190918_1" (
"did"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"title"  TEXT,
"weather"  TEXT,
"tag"  TEXT,
"content"  TEXT
);

-- ----------------------------
-- Records of _tDairy_old_20190918_1
-- ----------------------------

-- ----------------------------
-- Table structure for _tDairy_old_20190918_2
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tDairy_old_20190918_2";
CREATE TABLE "_tDairy_old_20190918_2" (
"did"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"title"  TEXT,
"datetime"  TEXT,
"weather"  TEXT,
"tag"  TEXT,
"content"  TEXT
);

-- ----------------------------
-- Records of _tDairy_old_20190918_2
-- ----------------------------

-- ----------------------------
-- Table structure for _tDairy_old_20190919
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tDairy_old_20190919";
CREATE TABLE "_tDairy_old_20190919" (
"did"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"uid"  INTEGER NOT NULL,
"title"  TEXT,
"datetime"  TEXT,
"weather"  TEXT,
"tag"  TEXT,
"content"  TEXT,
CONSTRAINT "fk_user_uid" FOREIGN KEY ("uid") REFERENCES "tUser" ("uid") ON DELETE CASCADE ON UPDATE CASCADE
);

-- ----------------------------
-- Records of _tDairy_old_20190919
-- ----------------------------

-- ----------------------------
-- Table structure for _tJokeRating_old_20191209
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tJokeRating_old_20191209";
CREATE TABLE "_tJokeRating_old_20191209" (
"rid"  INTEGER NOT NULL,
"uid"  INTEGER NOT NULL,
"rating"  REAL NOT NULL,
PRIMARY KEY ("rid", "uid")
);

-- ----------------------------
-- Records of _tJokeRating_old_20191209
-- ----------------------------

-- ----------------------------
-- Table structure for _tJoke_old_20191209
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tJoke_old_20191209";
CREATE TABLE "_tJoke_old_20191209" (
"jid"  INTEGER NOT NULL,
"title"  TEXT,
"datetime"  TEXT,
"content"  TEXT,
"up_uid"  INTEGER,
"nickname"  TEXT,
"total_rating_people"  INTEGER,
"total_rating_score"  REAL,
"average_rating_score"  REAL,
PRIMARY KEY ("jid")
);

-- ----------------------------
-- Records of _tJoke_old_20191209
-- ----------------------------

-- ----------------------------
-- Table structure for _tUser_old_20190912
-- ----------------------------
DROP TABLE IF EXISTS "main"."_tUser_old_20190912";
CREATE TABLE "_tUser_old_20190912" (
"uid"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"user_name"  TEXT(32) NOT NULL,
"passwd"  TEXT(16) NOT NULL
);

-- ----------------------------
-- Records of _tUser_old_20190912
-- ----------------------------
