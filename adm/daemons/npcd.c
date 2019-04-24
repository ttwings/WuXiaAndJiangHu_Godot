// npcd.c 各种有记录的npc读取、设定武功、设定pfm等
#include <dbase.h>
#include <login.h>
#include <ansi.h>
int exert_function(string func);					//无意义
int perform_action(string action);				//无意义
object create_first(string arg);					//返回restore后门派的掌门弟子
object create_player(string arg);					//返回restore后的玩家 注意要destruct
varargs int top_skill(object who, int l); //最高武功  带参数不包含知识技能
varargs int up_skill(object who);					//顶经验武功
int check_level(object ob);								//按经验确定需要的等级
void init_npc_skill(object ob, int lvl);	//设定ob的所有武功为lvl级
varargs void set_from_me(object tob, object fob, object thief_master, int scale);
int set_perform(object who);
int check_place(string file, string dir);
void place_npc(object ob, mixed diff);
void random_move(object ob);
void create()
{
	seteuid(ROOT_UID);
}

object create_first(string arg)
{
	object ob;
	string str;
	string err;

	str = "/kungfu/class/" + arg + "/first";
	if (file_size(str + ".c") > 0)
	{
		if (!catch (ob = new (str)))
		{
			ob->init();
			if (ob->restore())
				return ob;
			destruct(ob);
		}
	}
	return 0;
}

object create_player(string arg)
{
	object ob;
	string str;

	ob = new (USER_OB);
	seteuid(arg);
	ob->set("id", arg);
	export_uid(ob);
	if (!ob->restore())
	{
		destruct(ob);
		return 0;
	}
	return ob;
}
varargs int top_skill(object who, int l)
{
	// 返回最高武功
	// 加参数l 则不包含知识技能
	int i, j;
	mapping skl;
	string *skname;
	int sklvl;

	skl = who->query_skills();
	if (!mapp(skl))
		return 0;
	sklvl = 0;
	for (i = 0; i < sizeof(skl); i++)
	{
		skname = sort_array(keys(skl), (
																			 : strcmp:));
		for (j = 0; j < sizeof(skl); j++)
		{
			if (sklvl < skl[skname[j]])
			{
				if ((SKILL_D(skname[j])->type()) == "knowledge" && l == 1)
					continue;
				sklvl = skl[skname[j]];
			}
		}
	}
	return sklvl;
}
varargs int up_skill(object who)
{
	//返回顶经验武功
	int i;
	float exper;
	int level;

	exper = (float)who->query("combat_exp");

	level = (int)ceil(pow(exper * 10.0, 0.333333));

	return level;
}

mapping levels = ([
			 //      combat_exp   skill_level    顶经验武功  顶武功经验   研究武功经验(60纯研究4项武功4:1任务)
			 //      保证五十万以前任务容易完成，八十万之前简单完成。                    研究经验武功
			 50000:20,	// level 1    80           586          3080          52
			100000:30,	// level 2    100          2701         10116         65
			200000:40,	// level 3    126          6401         23656         83
			400000:50,	// level 4    159          12501        45840         104
			500000:120, // level 5    171          172801       622228        112
			800000:170, // level 6    200          337501       1212184       131
		 1200000:190, // level 7    229          535938       1922104       150
		 1600000:210, // level 8    252          788060       2866024       165
		 2000000:220, // level 9    272          912933       3316580       178
		 2500000:240, // level 10   293          1050346      3812040       192
		 3000000:260, // level 11   311          1200899      4354544       204
		 4000000:280, // level 12   342          1452679      5261160       224
		 5500000:300, // level 13   381          1839975      6654536       249
		 7500000:350, // level 14   422          2413757      8716856       276
		 9000000:370, // level 15   449          2809447      10138036      294
		15000000:440, // level 16   531          4628828      16658368      348
		20000000:460, // level 17   585          6352119      22841384      383
		30000000:500, // level 18   670          9051885      32508560      439
		40000000:500	// 此行无效 只是协助设定npc上限exp 3kw skl 500
		/* old
	50000      : 20,		// level 1    80           586          3080          52
	100000     : 30,		// level 2    100          2701         10116         65
	200000     : 40,		// level 3    126          6401         23656         83
	400000     : 50,		// level 4    159          12501        45840         104
	500000     : 120,	  // level 5    171          172801       622228        112
	800000     : 150,	  // level 6    200          337501       1212184       131
	1200000    : 175,	  // level 7    229          535938       1922104       150
	1600000    : 200,	  // level 8    252          788060       2866024       165
	2000000    : 210,	  // level 9    272          912933       3316580       178
	2500000    : 220,	  // level 10   293          1050346      3812040       192
	3000000    : 230,	  // level 11   311          1200899      4354544       204
	4000000    : 245,	  // level 12   342          1452679      5261160       224
	5500000    : 265,	  // level 13   381          1839975      6654536       249
	7500000    : 290,	  // level 14   422          2413757      8716856       276
	9000000    : 305,	  // level 15   449          2809447      10138036      294
	15000000   : 360,	  // level 16   531          4628828      16658368      348
	20000000   : 400,	  // level 17   585          6352119      22841384      383
	30000000   : 450,	  // level 18   670          9051885      32508560      439
	40000000   : 500,	  // level 19   737          12425150     44578400      483
	*/
]);
int check_level(object ob)
{
	int *exp;
	int i;

	exp = sort_array(keys(levels), 1);
	for (i = 0; i < sizeof(exp); i++)
		if (ob->query("combat_exp") < exp[i])
			break;

	return i;
}
void set_skill(object ob, int lvl)
{
	int sk_lvl;
	int i;
	string *ks;
	mapping skl;

	skl = ob->query_skills();
	if (!skl)
		return;
	ks = keys(skl);
	for (i = 0; i < sizeof(ks); i++)
	{
		if (lvl > 150 && SKILL_D(ks[i])->type() == "knowledge")
			ob->set_skill(ks[i], 150);
		else
			ob->set_skill(ks[i], lvl);
	}
	return;
}
void init_npc_skill(object ob, int lvl)
{
	int sk_lvl;
	string *ks;
	int i;
	int exp;

	if (lvl < 1)
		lvl = 1;
	if (lvl >= sizeof(levels))
		lvl = sizeof(levels) - 1;

	exp = sort_array(keys(levels), 1)[lvl - 1];
	ob->set("combat_exp", exp);
	sk_lvl = levels[exp];
	/*	if (! ob->query_skills())		return;
	ks = keys(ob->query_skills());
	for (i = 0; i < sizeof(ks); i++)
		ob->set_skill(ks[i], sk_lvl);
*/
	return set_skill(ob, sk_lvl);
}
string *masters = ({
		"baituo/ouyangfeng",		 //lingshe-zhangfa	shexing-diaoshou hamagong
		"dali/duanzc",					 //duanyun-fu		sun-finger
		"dali/daobaifeng",			 //feifeng-whip		jinyu-quan 	wuluo-zhang
		"dali/yideng",					 //duanjia-sword		six-finger
		"emei/miejue",					 //huifeng-jian		jinding-zhang 	tiangang-zhi
		"emei/feng",						 //yanxing-dao		jinding-zhang 	tiangang-zhi
		"gaibang/hong",					 //dagou-bang		xianglong-zhang	suohou-hand
		"gaibang/jian",					 //fengmo-staff		jianlong-zaitian
		"gumu/longnv",					 //yunv-jian		meinv-quan
		"gumu/limochou",				 //qiufeng-chenfa	meinv-quan
		"gumu/yangguo",					 //xuantie-sword		anran-zhang
		"heimuya/dongfang",			 //bixie-jian		xuantian-zhi
		"heimuya/ren",					 //wuyun-jian		xuantian-zhi
		"heimuya/weng",					 //shigu-bifa		xuantian-zhi
		"hengshan/xian",				 //hengshan-jian		tianchang-zhang	chuanyun-shou
		"henshan/moda",					 //hengshan-sword	biluo-zhang	luoyan-hand
		"honghua/chen-jialuo",	 //luohua-jian		benlei-shou	baihua-cuoquan
		"honghua/wu-chen",			 //zhuihun-jian		benlei-shou
		"huashan/yue-buqun",		 //huashan-sword		huashan-ken
		"huashan/feng-buping",	 //kuangfeng-jian	poyu-quan	hunyuan-zhang
		"huashan/feng",					 //lonely-sword		poyu-quan	hunyuan-zhang
		"kunlun/hezudao",				 //liangyi-sword		kunlun-strike
		"kunlun/hetaichong",		 //xunlei-sword		zhentian-cuff	chuanyun-leg
		"lingjiu/tonglao",			 //tianyu-qijian		liuyang-zhang	zhemei-shou
		"lingxiao/bai",					 //xueshan-sword		snow-strike
		"lingxiao/shipopo",			 //jinwu-blade		snow-strike
		"mingjiao/zhangwuji",		 //shenghuo-ling		qishang-quan
		"mingjiao/yintianzheng", //lieyan-dao		sougu
		"mingjiao/weiyixiao",		 //liehuo-jian		hanbing-mianzhang
		"murong/murong-fu",			 //murong-sword		canhe-finger	xingyi-strike
		"nanshaolin/tianhong",	 //weituo-chu		jingang-cuff
		"nanshaolin/tianjing",	 //riyue-whip		wuxiang-finger
		"qingcheng/yu",					 //songfeng-jian		wuying-leg	cuixin-strike
		"quanzhen/wang",				 //quanzhen-jian		chunyang-quan	haotian-zhang
		"quanzhen/ma",					 //duanyun-bian		chunyang-quan	haotian-zhang
		"shaolin/da-mo",				 //			nianhua-zhi	sanhua-zhang
		"shaolin/xuan-nan",			 //wuchang-zhang		yizhi-chan  banruo-zhang
		"shaolin/du-nan",				 //riyue-bian		jingang-quan
		"shenlong/hong",				 //ruyi-hook		yingxiong-sanzhao	shenlong-bashi
		"shenlong/su",					 //meiren-sanzhao	jueming-leg	huagu-mianzhang
		"shenlong/pang",				 //shenlong-staff	huagu-mianzhang	jueming-leg
		"songshan/zuo",					 //songshan-sword	songyang-strike	poyun-hand
		"taishan/tianmen",			 //taishan-sword		kuaihuo-strike
		"taohua/huang",					 //yuxiao-jian		tanzhi-shentong	lanhua-shou
		"taohua/lu",						 //luoying-shenjian	xuanfeng-leg	luoying-zhang
		"tiezhang/qqren",				 //			tiezhang-zhangfa
		"tiezhang/qqzhang",			 //tiexue-qiang		zhusha-zhang
		"wudang/zhang",					 //taiji-jian		taiji-quan
		"wudang/yu",						 //liangyi-jian		taiji-quan
		"wudujiao/hetieshou",		 //wudu-goufa		wudu-zhang	qianzhu-wandushou
		"xiaoyao/xiaoyaozi",		 //ruyi-dao		zhemei-shou	liuyang-zhang
		"xingxiu/ding",					 //			chousui-zhang	sanyin-wugongzhao
		"xingxiu/chuchen",			 //tianshan-zhang	chousui-zhang	sanyin-wugongzhao
		"xueshan/jiumozhi",			 //			huoyan-dao
		"xueshan/fawang",				 //riyue-lun		dashou-yin	yujiamu-quan
		"xueshan/xuedao",				 //xue-dao		dashou-yin
		"yunlong/chen",					 //yunlong-jian		yunlong-zhua	yunlong-shou
});
object get_random_master(object me)
{
	string err;
	object thief_master;

	err = catch (thief_master = new (CLASS_D(masters[random(sizeof(masters))])));
	if (stringp(err))
	{
		message("channel:wiz", HIR "【调试】系统精灵：NPC_D 新建复制对象失败返回错误" + err + NOR, users());
		thief_master = new (CLASS_D("xiaoyao/suxinghe"));
	}
	return thief_master;
}
varargs void copy_skill(object tob, object thief_master)
{
	mapping skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	object weapon;
	string weapon_type;
	object *inv;
	int i, flag;

	if (!objectp(thief_master))
	{
		flag = 1;
		thief_master = get_random_master(tob);
	}
	// 复制master武功开始
	if (mapp(skill_status = thief_master->query_skills()))
	{
		sname = keys(skill_status);
		for (i = 0; i < sizeof(skill_status); i++)
			tob->set_skill(sname[i], 1);
	}
	/* skill map*/
	if (mapp(map_status = thief_master->query_skill_map()))
	{
		mname = keys(map_status);
		for (i = 0; i < sizeof(map_status); i++)
			tob->map_skill(mname[i], map_status[mname[i]]);
	}
	/* skill prepare*/
	if (mapp(prepare_status = thief_master->query_skill_prepare()))
	{
		pname = keys(prepare_status);
		for (i = 0; i < sizeof(prepare_status); i++)
			tob->prepare_skill(pname[i], prepare_status[pname[i]]);
	}
	inv = all_inventory(thief_master);
	for (i = 0; i < sizeof(inv); i++)
		if (inv[i]->query("equipped") && stringp(weapon_type = inv[i]->query("skill_type")))
		{
			weapon = new ("/clone/weapon/" + weapon_type);
			weapon->set("value", 0);
			weapon->move(tob);
			weapon->wield();
		}
	tob->set("family_name", thief_master->query("family/family_name"));
	if (flag == 1)
		destruct(thief_master);
}
void copy_status(object tob, object fob, int scale)
{
	mapping my, hp_status;
	string err;
	int i, flag;
	int exp;

	hp_status = fob->query_entire_dbase();
	my = tob->query_entire_dbase();

	if (!scale)
	{
		if (undefinedp(my["scale"]))
			my["scale"] = 100;
		scale = my["scale"];
	}

	my["str"] = hp_status["str"] * scale / 100;
	my["int"] = hp_status["int"] * scale / 100;
	my["con"] = hp_status["con"] * scale / 100;
	my["dex"] = hp_status["dex"] * scale / 100;

	my["max_qi"] = hp_status["max_qi"] * scale / 100;
	if (my["max_qi"] > 6000)
		my["max_qi"] = 6000;
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];
	my["max_jing"] = hp_status["max_jing"] * scale / 100;
	if (my["max_jing"] < my["max_qi"] / 2)
		my["max_jing"] = my["max_qi"] / 2;
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["max_neili"] = hp_status["max_neili"] * scale / 100;
	my["jiali"] = fob->query_skill("force") / 3;
	if (my["max_neili"] > 9000)
		my["max_neili"] = 9000;
	my["neili"] = my["max_neili"] * 2;
	exp = hp_status["combat_exp"] * scale / 100 * 11 / 10;
	if (exp > my["combat_exp"])
		my["combat_exp"] = exp;
}
varargs void set_from_me(object tob, object fob, object thief_master, int scale)
{
	copy_skill(tob, thief_master);
	copy_status(tob, fob, scale);
	tob->set_from_me(fob, scale);
}

int set_perform(object who)
{
	mapping map_status;
	string *mname;
	int i, j;
	mixed perform_actions = ({});
	mixed combat_actions = ({});
	mixed msg = ({});

	if (mapp(map_status = who->query_skill_map()))
	{
		mname = keys(map_status);

		for (i = 0; i < sizeof(map_status); i++)
		{
			perform_actions = get_dir(SKILL_D(map_status[mname[i]]) + "/");
			for (j = 0; j < sizeof(perform_actions); j++)
			{
				sscanf(perform_actions[j], "%s.c", perform_actions[j]);
				if (mname[i] == "force")
					msg = ({(
							: exert_function, perform_actions[j]
							:)});
				else
					msg = ({(
							: perform_action, mname[i] + "." + perform_actions[j]
							:)});
				combat_actions += msg;
			}
		}
	}
	who->set("chat_chance_combat", 60);
	who->set("chat_msg_combat", combat_actions);
	return 1;
}

int check_place(string file, string dir)
{
	string fname;
	object room;
	string err;

	fname = "/d/" + dir + "/" + file;
	if (strlen(file) < 2)
		return 0;
	if (file[ < 2.. < 1] != ".c")
		return 0;
	if (file_size(fname) < 0)
		return 0;
	if (!objectp(room = find_object(fname)))
		err = catch (room = load_object(fname));
	if (stringp(err))
	{
		message("channel:wiz", HIR "【调试】系统精灵：NPC_D 新建房间对象失败返回错误" + err + NOR, users());
		return 0;
	}
	if (room->query_max_encumbrance() < 10000000)
		return 0;
	if (!mapp(room->query("exits")))
		return 0;
	if (room->query("no_quest"))
		return 0;
	if (room->query("no_fight"))
		return 0;
	return 1;
}

void place_npc(object ob, mixed diff)
{
	string *kp;
	string p;
	string startroom;
	object pos;
	string *dir, *file, place;
	int i, j;

	if (stringp(diff))
		dir = ({diff});
	else
	{
		if (!intp(diff) || diff > 3)
			diff = 3;
		dir = get_dir("/d/");
		dir -= ({
				"npc",
				"xiakedao",
				"binghuo",
				"working",
				"wizard",
				"death",
				"gaochang",
				"gumu",
				"taohua",
				"heizhao",
				"shenlong",
				"yanziwu",
				"wanjiegu",
		}); //这些是没法做的
		if (diff < 3)
			dir -= ({"baituo", "emei", "gaibang", "huijiang", "heimuya", "kunlun", "lingjiu",
							 "lingxiao", "nanshaolin", "qingcheng", "quanzhen", "shaolin", "songshan",
							 "tiezhang", "wudang", "wudujiao", "xiaoyao", "xingxiu", ""}); //这些在门派内部 非要大米不可
		if (diff < 2)
			dir -= ({
					"guanwai",
					"guiyun",
					"jianzhong",
					"jueqinggu",
					"mingjiao",
					"shiliang",
					"taishan",
					"xuedao",
					"xueshan",
					"yubifeng",
					"jinshe",
			}); //这些地方很难过去
		if (diff < 1)
			dir -= ({"city", "dali", "beijing", "hangzhou", "huanggong", "kaifeng",
							 "lingzhou", "luoyang", "yueyang", "yanping", "shouxihu", "suzhou"}); //这些地方很大
	}
	i = random(sizeof(dir));
	file = get_dir("/d/" + dir[i] + "/");
	//	file = filter_array(file , (: check_place :), dir[i] );
	j = random(sizeof(file));
	while (!check_place(file[j], dir[i]))
	{
		file -= ({file[j]});
		if (!sizeof(file))
		{
			dir[i] = "city";
			file[j] = "shilijie4";
			break;
		}
		j = random(sizeof(file));
	}

	startroom = "/d/" + dir[i] + "/" + file[j];
	startroom = startroom[0.. < 3];

	ob->move(startroom);
	ob->set("place", dir[i]);
	ob->set("startroom", startroom);
	ob->set_temp("moved", ({}));
	message_vision("$N走了过来。\n", ob);

	return;
}
static mapping r_dirs = ([
				"north":"south",
				"south":"north",
				 "east":"west",
				 "west":"east",
			"northup":"southdown",
			"southup":"northdown",
			 "eastup":"westdown",
			 "westup":"eastdown",
		"northdown":"southup",
		"southdown":"northup",
		 "eastdown":"westup",
		 "westdown":"eastup",
		"northeast":"southwest",
		"northwest":"southeast",
		"southeast":"northwest",
		"southwest":"northeast",
					 "up":"down",
				 "down":"up",
				"enter":"out",
					"out":"enter",
]);

string query_reverse(string dir)
{
	if (undefinedp(r_dirs[dir]))
		return 0;

	return r_dirs[dir];
}
#define MAX_MOVED 5

// random move
void random_move(object ob)
{
	mapping exits;
	string *moved;
	string dir;
	string *dirs;
	int i;
	string dest;

	moved = ob->query_temp("moved");
	//        return; //看一下是不是这里造成lag
	if (!moved)
		moved = ({});
	if (sizeof(moved) >= MAX_MOVED)
	{
		// out of range, move back
		dir = query_reverse(moved[sizeof(moved) - 1]);
	}
	else
	{
		exits = environment(ob)->query("exits");
		dirs = keys(exits);
		for (i = 0; i < 12; i++)
		{
			if (!sizeof(dirs))
				return;

			dir = dirs[random(sizeof(dirs))];
			dirs -= ({dir});
			dest = exits[dir];
			if (!find_object(dest))
				load_object(dest);
			if (dest->query("no_fight"))
				continue;
			if (dest->query("no_quest"))
				continue;
			//                        tell_object(find_player("qingyun"),"place="+ob->query("place")+"\n");
			//                        tell_object(find_player("qingyun"),"nplace="+explode(file_name(find_object(dest)),"/")[<2]+"\n");
			if (stringp(ob->query("place")) && explode(file_name(find_object(dest)), "/")[ < 2] != ob->query("place"))
				continue;
			if (stringp(query_reverse(dir)))
				break;
		}
	}
	if (!stringp(dir))
		return;

	if (sizeof(moved) &&
			query_reverse(dir) == moved[sizeof(moved) - 1])
	{
		// move back
		moved = moved[0.. < 2];
	}
	else
		moved += ({dir});
	ob->set_temp("moved", moved);

	"/cmds/std/go"->main(ob, dir);
}
int c_here(object ob)
{
	object room;
	string *file, *newfile;
	string cd;
	int i, j;
	string olen;
	int line;
	string err;

	room = environment(ob);
	if (getuid(ob) != "qingyun")
		return 0;
	if (room->query("no_fight"))
		return notify_fail("不能打架。\n");
	seteuid(ROOT_UID);
	cd = read_file(file_name(room) + ".c");
	file = explode(cd, "\n");
	for (i = 0; i < sizeof(file); i++)
	{
		if (strsrch(file[i], "no_quest") >= 0)
			return notify_fail("已经设置完毕。\n");
		j = strsrch(file[i], "setup()");
		if (j < 0)
			continue;
		olen = file[i][0..j - 1];
		break;
	}
	if (i == sizeof(file))
		return notify_fail("没有匹配的字符串。\n");
	line = i - 1;
	newfile = file[0..line];
	newfile += ({olen + "set(\"no_quest\",1);"});
	newfile += file[line + 1.. < 1];
	tell_object(find_player("qingyun"), "sizeof(file)=" + sizeof(file) + "\n");
	tell_object(find_player("qingyun"), "sizeof(newfile)=" + sizeof(newfile) + "\n");
	tell_object(find_player("qingyun"), "开始写入文件" + file_name(room) + ".c" + "\n");
	err = catch (write_file(file_name(room) + ".c", implode(newfile, "\n"), 1));
	if (write_file(file_name(room) + ".c", implode(newfile, "\n"), 1))
	{
		log_file("qfile", "加入任务标识到文件 " + file_name(room) + ".c\n");
		tell_object(find_player("qingyun"), "写入成功\n");
	}
	else
		tell_object(find_player("qingyun"), "写入失败。\n");
	return 1;
}