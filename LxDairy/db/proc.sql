SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Procedure structure for addcoin4800
-- ----------------------------
DROP PROCEDURE IF EXISTS `addcoin4800`;
delimiter ;;
CREATE PROCEDURE `addcoin4800`(IN `var_phone` varchar(32))
BEGIN

	DECLARE bExist TINYINT default 0;
	SELECT COUNT(1) into bExist FROM user_table WHERE phone_no=var_phone;
	
	if bExist
	then
	insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());

		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set bless_air_used = 4800, last_consume_air=4800, blessAir=0, this_consume_air=0, blessCoin = t.r where phone_no_bind= var_phone;
end if;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for addcoin4800new
-- ----------------------------
DROP PROCEDURE IF EXISTS `addcoin4800new`;
delimiter ;;
CREATE PROCEDURE `addcoin4800new`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for delete_coin
-- ----------------------------
DROP PROCEDURE IF EXISTS `delete_coin`;
delimiter ;;
CREATE PROCEDURE `delete_coin`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
	DELETE FROM bless_coin WHERE belongs_phone_no=var_phone and create_datetime > '2018-06-10 00:00:00';
END
;;
delimiter ;

-- ----------------------------
-- Function structure for fn_active
-- ----------------------------
DROP FUNCTION IF EXISTS `fn_active`;
delimiter ;;
CREATE FUNCTION `fn_active`()
 RETURNS int(11)
BEGIN
	#Routine body goes here...

	RETURN 0;
END
;;
delimiter ;

-- ----------------------------
-- Function structure for fn_now
-- ----------------------------
DROP FUNCTION IF EXISTS `fn_now`;
delimiter ;;
CREATE FUNCTION `fn_now`()
 RETURNS varchar(30) CHARSET utf8
BEGIN
	#Routine body goes here...
	RETURN DATE_FORMAT(NOW(),'%Y年%m月%d日:%H时:%i分:%s秒');
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for NewProc
-- ----------------------------
DROP PROCEDURE IF EXISTS `NewProc`;
delimiter ;;
CREATE PROCEDURE `NewProc`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for Proc_active
-- ----------------------------
DROP PROCEDURE IF EXISTS `Proc_active`;
delimiter ;;
CREATE PROCEDURE `Proc_active`()
BEGIN
	#除池
	#Routine body goes here...
	declare var_phone varchar(32) default "";
	declare nblessAir int default 0;
	declare nPool int default 0;
	declare nUsed int default 0;
	
-- 	DECLARE cur_phone cursor for SELECT a.* FROM(
--     SELECT belongs_phone_no as p from bless_coin WHERE create_datetime > '2018-06-10 00:00:00'
--     UNION ALL
--     SELECT phone_no as p from user_table WHERE this_consume_air >= 4800 or (this_consume_air > 2000 and blessAir > (4800 - this_consume_air) and clearing_datetime < '2018-07-17 00:00:00')
-- )a GROUP BY a.p HAVING COUNT(a.p)=1;

DECLARE cur_phone cursor for SELECT phone_no, blessAir, dig_coin_surplus_value, this_consume_air from user_table WHERE (this_consume_air>4800 or (this_consume_air > 1000 and (blessAir+this_consume_air+dig_coin_surplus_value) > 4800)) and clearing_datetime < '2018-07-17 00:00:00' and not EXISTS(SELECT belongs_phone_no from bless_coin WHERE create_datetime > '2018-06-10 00:00:00' and bless_coin.belongs_phone_no=user_table.phone_no);

DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_phone;

OPEN cur_phone;

REPEAT
FETCH cur_phone INTO var_phone, nblessAir, nPool, nUsed;
insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());
if nUsed > 4800
	then
	update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set  blessCoin = t.r where phone_no_bind= var_phone;
	ELSEIF nUsed + nblessAir < 4800
	THEN
update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir =0, dig_coin_surplus_value= 4800-blessAir-this_consume_air, bless_air_used = 4800, this_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone;
	ELSE
	update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir = blessAir - (4800-this_consume_air), bless_air_used = 4800, this_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone;
	END IF;

UNTIL 0 END REPEAT;

CLOSE cur_phone;

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_active_a2
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_active_a2`;
delimiter ;;
CREATE PROCEDURE `proc_active_a2`()
BEGIN
	#池
	#Routine body goes here...
	declare var_phone varchar(32) default "";
	
-- 	DECLARE cur_phone cursor for SELECT a.* FROM(
--     SELECT belongs_phone_no as p from bless_coin WHERE create_datetime > '2018-06-10 00:00:00'
--     UNION ALL
--     SELECT phone_no as p from user_table WHERE this_consume_air >= 4800 or (this_consume_air > 2000 and blessAir > (4800 - this_consume_air) and clearing_datetime < '2018-07-17 00:00:00')
-- )a GROUP BY a.p HAVING COUNT(a.p)=1;

DECLARE cur_phone cursor for SELECT phone_no from user_table WHERE (this_consume_air > 1000 and  blessAir > (4800-this_consume_air-dig_coin_surplus_value) and blessAir < (4800-this_consume_air) and clearing_datetime < '2018-07-17 00:00:00') and not EXISTS(SELECT belongs_phone_no from bless_coin WHERE create_datetime > '2018-06-10 00:00:00' and bless_coin.belongs_phone_no=user_table.phone_no);

DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_phone;

OPEN cur_phone;

REPEAT
FETCH cur_phone INTO var_phone;
insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());
update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir =0, dig_coin_surplus_value= 4800-blessAir-this_consume_air, bless_air_used = 4800, this_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone and this_consume_air < 4800;
UNTIL 0 END REPEAT;

CLOSE cur_phone;

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_apply_money
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_apply_money`;
delimiter ;;
CREATE PROCEDURE `proc_apply_money`()
BEGIN
	#Routine body goes here...
		declare var_phone varchar(32) default "";
	declare nExist int default 0;
	declare nGet int default 0;
	
	DECLARE cur_phone cursor for SELECT belongs_phone_no, exist_days, get_count FROM bless_coin WHERE create_datetime > '2018-07-30 00:00:00';
	
	DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_phone;
	
	OPEN cur_phone;
	
	REPEAT
	FETCH cur_phone INTO var_phone, nExist, nGet;
	
 update user_table set status_apply_money=1, blessTreasure=blessTreasure+(nExist-nGet)*30, week_work_hour=week_work_hour+(nExist-nGet) where phone_no_bind = var_phone;
											
UNTIL 0 END REPEAT;

CLOSE cur_phone;
	
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_change_exist_day
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_change_exist_day`;
delimiter ;;
CREATE PROCEDURE `proc_change_exist_day`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
		declare var_phone varchar(32) default "";
	declare nExist int default 0;
	declare nGet int default 0;
	
	DECLARE cur_phone cursor for SELECT belongs_phone_no, exist_days, get_count FROM bless_coin WHERE create_datetime > '2018-07-30 00:00:00';
	
	DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_phone;
	
	OPEN cur_phone;
	
	REPEAT
	FETCH cur_phone INTO var_phone, nExist, nGet;
	UPDATE bless_coin set exist_days = 7 WHERE belongs_phone_no = var_phone and create_datetime > '2018-08-28 00:00:00';
	
--  update user_table set status_apply_money=1, blessTreasure=blessTreasure+(nExist-nGet)*30, week_work_hour=week_work_hour+(nExist-nGet) where phone_no_bind = var_phone;
											
UNTIL 0 END REPEAT;

CLOSE cur_phone;
	
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_getcoin
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_getcoin`;
delimiter ;;
CREATE PROCEDURE `proc_getcoin`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
#insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());
update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir = 0, bless_air_used = 4800, last_consume_air=4800, dig_coin_surplus_value=0, blessCoin = t.r where phone_no_bind= var_phone and bless_reason_used=4800;

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_getcoin03
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_getcoin03`;
delimiter ;;
CREATE PROCEDURE `proc_getcoin03`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
	#Routine body goes here...
		declare nblessAir int default 0;
	declare nPool int default 0;
	declare nUsed int default 0;
	DECLARE bExist TINYINT default 0;
	SELECT COUNT(1) into bExist FROM user_table WHERE phone_no=var_phone;
	
	if bExist
	then
	insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());

		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir = 0, dig_coin_surplus_value=0, bless_air_used = 4800, last_consume_air=4800, bless_reason_used = 4800, this_consume_air=0, blessCoin = t.r where phone_no_bind= var_phone;
end if;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_getcoin0814
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_getcoin0814`;
delimiter ;;
CREATE PROCEDURE `proc_getcoin0814`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
	#Routine body goes here...
		declare nblessAir int default 0;
	declare nPool int default 0;
	declare nUsed int default 0;
	DECLARE bExist TINYINT default 0;
	SELECT COUNT(1) into bExist FROM user_table WHERE phone_no=var_phone;
	
	if bExist
	then
	insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());

		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set bless_air_used = 5000-blessAir, last_consume_air=5000-blessAir, blessReason=5000, bless_reason_used = 5000, this_consume_air=0, blessCoin = t.r where phone_no_bind= var_phone;
end if;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_getcoinnew
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_getcoinnew`;
delimiter ;;
CREATE PROCEDURE `proc_getcoinnew`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
		declare nblessAir int default 0;
	declare nPool int default 0;
	declare nUsed int default 0;

	SELECT blessAir, dig_coin_surplus_value, last_consume_air into nblessAir, nPool, nUsed from user_table WHERE phone_no=var_phone;
	
	if (nblessAir+nPool+nUsed) > 4800
	then
	insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());
		if (nblessAir+nUsed) < 4800
		then
		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir =0, dig_coin_surplus_value= dig_coin_surplus_value-(4800-blessAir-last_consume_air), bless_air_used = bless_air_used+(4800-last_consume_air), last_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone;
		else
				#实际消耗4800-last_consume_air
		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir = blessAir - (4800-last_consume_air), bless_air_used = bless_air_used+(4800-last_consume_air), last_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone;
		end if;
	END IF;

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_getcoinnew_copy1
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_getcoinnew_copy1`;
delimiter ;;
CREATE PROCEDURE `proc_getcoinnew_copy1`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
		declare nblessAir int default 0;
	declare nPool int default 0;
	declare nUsed int default 0;

	SELECT blessAir, dig_coin_surplus_value, last_consume_air into nblessAir, nPool, nUsed from user_table WHERE phone_no=var_phone;
	
	if (nblessAir+nPool+nUsed) > 4800
	then
	insert into bless_coin(belongs_phone_no, create_datetime) values(var_phone, now());
		if (nblessAir+nUsed) < 4800
		then
		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir =0, dig_coin_surplus_value= dig_coin_surplus_value-(4800-blessAir-last_consume_air), bless_air_used = bless_air_used+(4800-last_consume_air), last_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone;
		else
				#实际消耗4800-last_consume_air
		update user_table, (select count(belongs_phone_no) as r from bless_coin where belongs_phone_no = var_phone and get_count < 101) as t set blessAir = blessAir - (4800-last_consume_air), bless_air_used = bless_air_used+(4800-last_consume_air), last_consume_air=4800, blessCoin = t.r where phone_no_bind= var_phone;
		end if;
	END IF;

END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_liuyongling
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_liuyongling`;
delimiter ;;
CREATE PROCEDURE `proc_liuyongling`(IN `var_phone` varchar(32))
BEGIN
	#Routine body goes here...
update user_table set this_consume_air=0 where phone_no_bind= var_phone;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for proc_not
-- ----------------------------
DROP PROCEDURE IF EXISTS `proc_not`;
delimiter ;;
CREATE PROCEDURE `proc_not`()
BEGIN
	#Routine body goes here...
	declare var_phone varchar(32) default "";
DECLARE cur_phone cursor for SELECT a.* FROM(
    SELECT belongs_phone_no as p from bless_coin WHERE create_datetime > '2018-06-10 00:00:00'
    UNION ALL
    SELECT phone_no from user_table WHERE this_consume_air > 2000 and this_consume_air<4800 and blessAir < (4800-this_consume_air) and clearing_datetime < '2018-07-17 00:00:00' and EXISTS(SELECT belongs_phone_no from bless_coin WHERE create_datetime > '2018-06-10 00:00:00' and bless_coin.belongs_phone_no=user_table.phone_no)
)a GROUP BY a.p HAVING COUNT(a.p)=1;

DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_phone;
OPEN cur_phone;

REPEAT
FETCH cur_phone INTO var_phone;
SELECT phone_no, blessAir, this_consume_air FROM user_table WHERE phone_no=var_phone;

UNTIL 0 END REPEAT;

CLOSE cur_phone;

END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;