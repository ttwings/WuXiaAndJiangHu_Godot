# chinesed.c
# by Annihilator@ES
# modified by Xiang@XKX

# inherit F_SAVE;

#include <localtime.h>

#ifndef DATA_DIR
const DATA_DIR = "/data/"
#endif
const E2C_DICTIONARY = DATA_DIR + "e2c_dict"



# some constatns
const c_digit = [ "零","十","百","千","万","亿","兆" ];
const c_num = ["零","一","二","三","四","五","六","七","八","九","十"];
const sym_tian = [ "甲","乙","丙","丁","戊","己","庚","辛","壬","癸" ];
const sym_di = [ "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" ];

var dict = {};

# func add_translate(string key, string chn);
# func remove_translate(string key);

# func create():
# 	setuid(getuid());
# 	restore();

# func remove():
# 	save();

func chinese_number(i:int):
	if (i < 0):
		return "负" + chinese_number(-i);
	if (i < 11):
		return c_num[i];
	if (i < 20):
		return c_digit[1] + c_num[i - 10];
	if (i < 100):
		if (i % 10):
			return c_num[i / 10] + c_digit[1] + c_num[i % 10];
		else:
			return c_num[i / 10] + c_digit[1];
	
	if (i < 1000) :
		if (i % 100 == 0):
			return c_num[i / 100] + c_digit[2];
		elif (i % 100 < 10):
			return c_num[i / 100] + c_digit[2] +
			c_num[0] + chinese_number(i % 100);
		elif (i % 100 < 10):
			return c_num[i / 100] + c_digit[2] +
			c_num[1] + chinese_number(i % 100);
		else:
			return c_num[i / 100] + c_digit[2] + 
			chinese_number(i % 100);
	
	if (i < 10000) :
		if (i % 1000 == 0):
			return c_num[i / 1000] + c_digit[3];
		elif (i % 1000 < 100):
			return c_num[i / 1000] + c_digit[3] +
			c_num[0] + chinese_number(i % 1000);
		else :
			return c_num[i / 1000] + c_digit[3] +
			chinese_number(i % 1000);
	
	if (i < 100000000) :
		if (i % 10000 == 0) :
			return chinese_number(i / 10000) + c_digit[4];
		elif (i % 10000 < 1000) :
			return chinese_number(i / 10000) + c_digit[4] +
			c_num[0] + chinese_number(i % 10000);
		else:
			return chinese_number(i / 10000) + c_digit[4] +
			chinese_number(i % 10000);
	
	if (i < 1000000000000) :
		if (i % 100000000 == 0):
			return chinese_number(i / 100000000) + c_digit[5];
		elif (i % 100000000 < 1000000):
			return chinese_number(i / 100000000) + c_digit[5] +
			c_num[0] + chinese_number(i % 100000000);
		else :
			return chinese_number(i / 100000000) + c_digit[5] +
			chinese_number(i % 100000000);
	
	if (i % 1000000000000 == 0):
		return chinese_number(i / 1000000000000) + c_digit[6];
	elif (i % 1000000000000 < 100000000):
		return chinese_number(i / 1000000000000) + c_digit[6] +
		c_num[0] + chinese_number(i % 1000000000000);
	else:
		return chinese_number(i / 1000000000000) + c_digit[6] +
		chinese_number(i % 1000000000000);


func query_save_file():
	return E2C_DICTIONARY;

func chinese(str:String):
	if (!undefinedp(dict[str}):
		return dict[str];
	else:
		return str;

func remove_translate(key:String):
	map_delete(dict, key);
	save();

func add_translate(key:String, chn:String):
	dict[key] = chn;
	save();

func dump_translate():
	var k
	var str_;
	var i;
	
	str_ = "";
	k = keys(dict);
	# for (i = 0; i < sizeof(k); i++) :
	for i in range(sizeof(k)):
		str_ += sprintf("%-30s %s\n", k[i], dict[k[i]};
	write_file("/CHINESE_DUMP", str_);

func chinese_date(date:int):
	var local;

	if (date <=0) :
		date=1;
	local = localtime(date);
	
	return sprintf("%s%s年%s月%s日%s时%s刻",
		sym_tian[local[LT_YEAR] % 10], sym_di[local[LT_YEAR] % 12],
		chinese_number(local[LT_MON] + 1),
		chinese_number(local[LT_MDAY] + (local[LT_HOUR] > 23 ? 1 : 0)),
		sym_di[((local[LT_HOUR] + 1) % 24) / 2],
		chinese_number((local[LT_MIN]+1) % 2 * 2 + local[LT_MIN] / 30 + 1) );


#Used in natured.c to as a condition to judge which season should be
#to use different weather discription.
func chinese_month(date:int):
	var local;
	local = localtime(date);
	return sprintf("%s",chinese_number(local[LT_MON] + 1));

func chinese_monthday(date:int):
	var local;
	local = localtime(date);
	return sprintf("%s月%s日",chinese_number(local[LT_MON] + 1),
		chinese_number(local[LT_MDAY]+(local[LT_HOUR] > 23 ? 1 : 0)));
# /*		chinese_number(local[LT_MDAY]+1));*/

#end of appendance
func check_length(str_:String):
	if(!str_) :
		return 0;
	else :
		return strlen(str_);

func check_control(name:String):
	var i;
	if(!name) :
		return 0;
	i = strlen(name);
	i = i - 1
	while(i > 0):
		# if(name[i]==' ' || name[i] == '\n') :
			
		# 	return 2
		if( name[i]<' ' ) :
			return 1;
	return 0;

func check_space(name:String):
	var i;
	if(!name) :
		return 0;
	i = strlen(name);
	i = i - 1
	while(i>0):
		if(name[i]== ' ') :
			return 1;
	return 0;

func check_return(name:String):
	var i;
	if(!name) :
		return 0;
	i = strlen(name);
	i = i - 1
	# while(i>0) :
	# 	if(name[i]== '\n') :
	# 		return 1;
	return 0;

func check_chinese(name:String):
	var i;
	if(!name) :
		return 0;
	i = strlen(name);
	i = i - 1
	while(i>0):
		if( i%2==0 && !is_chinese(name[i..<0} ) :
			return 0;
	return 1;
