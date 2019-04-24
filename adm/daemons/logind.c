// adm/daemons/logind.c
// Modified by Constant Apr 19 2000
// Modified by Constant Jan 2 2001
// Modified by Zeratul Jan 12 2001 存款限制移至updated.c中

inherit F_DBASE;

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <localtime.h>

#define VISITORS "/log/MUDVISITOR"
#define GIFTCARD "/log/GIFTCARD"

int wiz_lock_level = WIZ_LOCK_LEVEL;
// tentop
int mad_lock = 0;
// 浩劫产生的条件变量
int dienpc = 0;
string *banned_name = ({"你", "你", "我", "他", "她", "它", "妈", "爸", "　",
												"翔少爷", "方舟子", "草鱼", "时空", "丁",
												"木人", "赫连铁树", "单正", "韦小宝", "火云",
												"仙子", "风儿", "凡狗", "演若达多", "寒江雪", "【我★爱】",
												"紫志龙"});

string *wiz_ip = ({"127.0.0.1",
									 "210.34.9.71",
									 "210.34.1.193",
									 "localhost",
									 "210.34.9.25",
									 "210.34.4.159"});

private
void get_id(string arg, object ob);
private
void confirm_id(string yn, object ob);
private
void sel_str(string item, object ob, mapping my, int all, int min, int max);
private
void sel_int(string item, object ob, mapping my, int all, int min, int max);
private
void sel_con(string item, object ob, mapping my, int all, int min, int max);
private
init_new_player(object user);
private
void get_hometown(string born, object ob);
private
void config_gift(object me, mapping my);
private
void delete_err_pass(string yn, object ob, object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object make_body(object ob);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
int howmuch_money(object ob);
int howmany_visitor();
int howmany_card();
void set_visitor(int num);
void set_card(int num);
// tentop

void create()
{
	seteuid(getuid());
	set("channel_id", "连线精灵");
}

void logon(object ob)
{
	object *usr;
	int i, inv_wiz_cnt, wiz_cnt, ppl_cnt, login_cnt;
	int iplimit;
	int in_login;
	int user_num;

	if (BAN_D->is_banned(query_ip_name(ob)) == 1)
	{
		write("对不起，您的地址不受欢迎。\n");
		destruct(ob);
		return;
	}
	cat(WELCOME);
	"/cmds/usr/time"->main();

	usr = users();
	wiz_cnt = 0;
	inv_wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	iplimit = 0;
	in_login = 0;

	for (i = 0; i < sizeof(usr); i++)
	{
		if (query_ip_name(usr[i]) == query_ip_name(ob))
			iplimit++;
		if (member_array(query_ip_name(ob), wiz_ip) == -1 &&
				!environment(usr[i]))
			in_login++;
		if (!environment(usr[i]))
			login_cnt++;
		else if (wizardp(usr[i]) && (usr[i]->query("env/invisibility") || usr[i]->query("no_look_wiz")))
			inv_wiz_cnt++;
		else if (wizardp(usr[i]) && !usr[i]->query("env/invisibility"))
			wiz_cnt++;
		else
			ppl_cnt++;
	}

	if (in_login > 10 && !member_array(query_ip_name(ob), wiz_ip))
	{
		write("对不起，侠客行一百现在正忙着呢，请稍后再试。\n");
		destruct(ob);
		return;
	}

	if (BAN_D->is_multi(query_ip_name(ob), iplimit - 1))
	{
		write("对不起，您所在的地址无法登录更多的角色。\n");
		destruct(ob);
		return;
	}
	// 计数 Start
	user_num = howmany_visitor();
	write("您是侠客行一百自二千零一年一月十四日以来的第" + HIY + chinese_number(user_num + 1) + NOR "位访问者。\n");
	set_visitor(user_num + 1);
	if (iplimit > 1)
		write("您所在的地址已有" HIY + chinese_number(iplimit - 1) + NOR "位玩家在线上。\n");
	/*	if (iplimit>8)
	{
		write("对不起，您所在的地址无法登录更多的角色。\n");
		destruct(ob);
		return;
	}
*/
	// 计数 End
	log_file("PLAYERNUM", sprintf("At %s: %d %s\n", ctime(time()), ppl_cnt, query_ip_name(ob)));
	printf("目前共有 %s 位世外高人、%s 位江湖儿女在线上，以及 %s 位使用者尝试连线中。\n",
				 chinese_number(wiz_cnt),
				 chinese_number(ppl_cnt),
				 chinese_number(login_cnt + inv_wiz_cnt));

	write("您的英文名字：");
	input_to("get_id", ob);
}

void set_visitor(int num)
{
	if (num > 0)
		write_file(VISITORS, sprintf("VISITORS %d", num), 1);
	else
		write("巫师请注意访问者数目不对！\n");
	return;
}

void set_card(int num)
{
	if (num > 0)
		write_file(GIFTCARD, sprintf("GIFTCARD %d", num), 1);
	else
		write("巫师请注意访问者数目不对！\n");
	return;
}

int howmany_user()
{
	int i, j, ppl_cnt;
	string *dir, *ppls, name;
	mixed info;
	seteuid(getuid());
	ppl_cnt = 0;
	dir = get_dir(DATA_DIR + "login/");
	for (i = 0; i < sizeof(dir); i++)
	{
		reset_eval_cost();
		ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
		ppl_cnt += sizeof(ppls);
	}
	return ppl_cnt;
}

int howmany_visitor()
{
	int num = 0;
	string content, format;
	content = read_file(VISITORS);
	sscanf(content, "%s %d", format, num);
	if (format != "VISITORS")
		write(format + "\n巫师请注意访问者数目不对！\n");
	return num;
}

int howmany_card()
{
	int num = 0;
	string content, format;
	content = read_file(GIFTCARD);
	sscanf(content, "%s %d", format, num);
	if (format != "GIFTCARD")
		write(format + "\n巫师请注意访问者数目不对！\n");
	return num;
}

private
void get_id(string arg, object ob)
{
	object ppl, *ob_list;
	int i, j;

	arg = lower_case(arg);
	if (!check_legal_id(arg))
	{
		write("您的英文名字：");
		input_to("get_id", ob);
		return;
	}

#ifdef MAX_USERS
	if ((string)SECURITY_D->get_status(arg) == "(player)" &&
			//		sizeof(users()) >= MAX_USERS )
			sizeof(users()) > 1000)
	{
		ppl = find_body(arg);
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		if (!ppl || !interactive(ppl))
		{
			write("对不起，" + MUD_NAME + "的使用者已经太多了，请待会再来。\n");
			destruct(ob);
			return;
		}
	}
#endif

	if (wiz_level(arg) < wiz_lock_level)
	{
		write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL + " 以上的人才能连线。\n");
		destruct(ob);
		return;
	}

	if ((string)ob->set("id", arg) != arg)
	{
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}
	/*
	if( arg=="guest" )
	{
		// If guest, let them create the character.
		confirm_id("Yes", ob);
		return;
	} else
*/
	if (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0)
	{
		if (ob->restore())
		{
			write("请输入密码：");
			input_to("get_passwd", 1, ob);
			return;
		}
		//		write("您的人物储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
		write("您的人物储存挡出了一些问题，请利用其他帐号通知巫师处理。\n");
		destruct(ob);
		return;
	}
	else if (strlen(arg) > 8)
	{
		write("您的英文名字太长了，请选择短一点的。\n");
		destruct(ob);
		return;
	}

	ob_list = users();
	j = 0;
	for (i = 0; i < sizeof(ob_list); i++)
	{
		if ((string)ob_list[i]->query("id") == arg)
			j++;
	}
	if (j > 1)
	{
		write("对不起，有人正在使用该代号注册，请换一个代号登录。\n");
		destruct(ob);
		return;
	}

	write("使用 " + (string)ob->query("id") + " 这个名字将会创造一个新的人物，您确定吗(y/n)？");
	input_to("confirm_id", ob);
}

private
void get_passwd(string pass, object ob)
{
	string my_pass;
	object user;
	int i, j, s;
	mapping m;
	string *k;

	write("\n");
	my_pass = ob->query("password");
	if (crypt(pass, my_pass) != my_pass)
	{
		write("密码错误！\n");
		ob->set("error_pass/" + ctime(time()), query_ip_name(ob));
		ob->save();
		destruct(ob);
		return;
	}

	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user)
	{
		if (user->query_temp("netdead"))
		{
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if (!ob->query("scborn/reset_gift"))
		if (objectp(user = make_body(ob)))
		{
			if (user->restore())
			{
				log_file("USAGE", sprintf("%s (%s) loggined from %s (%s)\n", user->query("name"), user->query("id"), query_ip_name(ob), ctime(time())));
				if (mapp(m = ob->query("error_pass")))
				{
					if ((string)SECURITY_D->get_status(ob->query("id")) == "(player)")
					{
						tell_object(find_player("trya"), "status=" + SECURITY_D->get_status(ob->query("id")) + "\n");
						delete_err_pass("y", ob, user);
						return;
					}
					k = keys(m);
					for (i = 0; i < sizeof(m); i++)
						write(k[i] + "\t" + m[k[i]] + "\n");
					write("删除以上密码错误记录？[y/n]");
					input_to("delete_err_pass", ob, user);
					return;
				}
				enter_world(ob, user);
				return;
			}
			destruct(user);
		}
	write("请您重新创造这个人物。\n");
	confirm_id("y", ob);
}
private
void delete_err_pass(string yn, object ob, object user)
{
	if (yn == "")
	{
		write("删除以上密码错误记录？[y/n]");
		input_to("delete_err_pass", ob, user);
		return;
	}
	if (yn[0] == 'y' || yn[0] == 'Y')
		ob->delete ("error_pass");
	enter_world(ob, user);
}

private
void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if (yn == "")
	{
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if (yn[0] != 'y' && yn[0] != 'Y')
	{
		write("好吧，欢迎下次再来。\n");
		destruct(ob);
		return;
	}
	else
	{
		tell_object(user, "有人从别处( " + query_ip_number(ob) + " )连线取代你所控制的人物。\n");
		//		log_file( "USAGE", sprintf("%s (%s) replaced by %s (%s)\n", user->query("name"), user->query("id"), query_ip_name(ob), ctime(time()) ) );
		log_file("LOGIN", sprintf("%-20s replaced by   %15s (%s)\n", user->query("name") + "(" + user->query("id") + ")", query_ip_name(ob), ctime(time())));
	}

	// Kick out tho old player.
	old_link = user->query_temp("link_ob");
	if (old_link)
	{
		exec(old_link, user);
		destruct(old_link);
	}

	reconnect(ob, user);
}

private
void confirm_id(string yn, object ob)
{
	if (yn == "")
	{
		write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
		input_to("confirm_id", ob);
		return;
	}
	if (yn[0] != 'y' && yn[0] != 'Y')
	{
		write("好吧，那么请重新输入您的英文名字：");
		input_to("get_id", ob);
		return;
	}
	ob->set_temp("new_char", 1);
	write(@TEXT

						请输入您的高姓大名，由于这个名字代表你的人物，而且以后不能更改，
								务必慎重择名（不雅观的姓名将被删除）。另：请不要选择金庸小说中
										已有人物姓名。

				TEXT);
	write("您的中文名字：");
	input_to("get_name", ob);
}

private
void get_name(string arg, object ob)
{
	if (!check_legal_name(arg))
	{
		write("您的中文名字：");
		input_to("get_name", ob);
		return;
	}
	ob->set("name", arg);
	write("请设定您的密码：");
	input_to("new_password", 1, ob);
}

private
void new_password(string pass, object ob)
{
	write("\n");
	if (strlen(pass) < 5)
	{
		write("密码的长度至少要五个字元，请重设您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass, 0));
	write("请再输入一次您的密码，以确认您没记错：");
	input_to("confirm_password", 1, ob);
}

private
void confirm_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if (crypt(pass, old_pass) != old_pass)
	{
		write("您两次输入的密码并不一样，请重新设定一次密码：");
		input_to("new_password", 1, ob);
		return;
	}
	write(@TEXT

						请选择你的人物出生地：

								参天之树，必有其根，怀山之水，必有其源。 故乡，是游子梦魂萦绕、辗转反侧的地方，是游子心中最深最沉的牵挂。

				你可以选择出生在下列城市：

				1〖 北京 〗 〖 开封 〗 〖 南阳 〗 〖 灵州 〗 〖 漠北 〗 〖 西夏 〗 2〖 长安 〗 〖 洛阳 〗 〖 兰州 〗 〖 汉中 〗 〖 襄阳 〗 〖 永登 〗 3〖 扬州 〗 〖 杭州 〗 〖 苏州 〗 〖 无锡 〗 〖 嘉兴 〗 〖 宜兴 〗 4〖 福州 〗 〖 泉州 〗 〖 台湾 〗 〖 延平 〗 〖 石梁 〗 〖 澎湖 〗 5〖 大理 〗 〖 衡阳 〗 〖 江陵 〗 〖 岳阳 〗 〖 佛山 〗 〖 成都 〗

				TEXT);
	input_to("get_hometown", ob);
}

private
void get_hometown(string born, object ob)
{
	mapping my;
	string hometown;
	int j;
	object old;

	j = random(6);
	my = ([]);
	my["area"] = born;
	switch (born)
	{
	case "1":
		switch (j)
		{
		case 0:
			hometown = "北京";
			my["START_ROOM"] = "/d/beijing/kedian";
			break;
		case 1:
			hometown = "开封";
			my["START_ROOM"] = "/d/kaifeng/daoxiang1";
			break;
		case 2:
			hometown = "南阳";
			my["START_ROOM"] = "/d/nanyang/kedian1";
			break;
		case 3:
			hometown = "灵州";
			my["START_ROOM"] = "d/lingzhou/chema";
			break;
		case 4:
			hometown = "漠北";
			my["START_ROOM"] = "/d/mobei/menggubao1";
			break;
		default:
			hometown = "西夏";
			my["START_ROOM"] = "d/lingzhou/chema";
			break;
		}
		break;

	case "2":
		switch (j)
		{
		case 0:
			hometown = "长安";
			my["START_ROOM"] = "/d/changan/kedian";
			break;
		case 1:
			hometown = "兰州";
			my["START_ROOM"] = "/d/lanzhou/kedian";
			break;
		case 2:
			hometown = "汉中";
			my["START_ROOM"] = "/d/hanzhong/kedian1";
			break;
		case 3:
			hometown = "洛阳";
			my["START_ROOM"] = "/d/luoyang/luoshenmiao";
			break;
		case 4:
			hometown = "襄阳";
			my["START_ROOM"] = "/d/xiangyang/kedian";
			break;
		default:
			hometown = "永登";
			my["START_ROOM"] = "/d/yongdeng/kedian";
			break;
		}
		break;
	case "3":
		switch (j)
		{
		case 0:
			hometown = "扬州";
			my["START_ROOM"] = "/d/city/kedian";
			break;
		case 1:
			hometown = "杭州";
			my["START_ROOM"] = "/d/hangzhou/kedian";
			break;
		case 2:
			hometown = "苏州";
			my["START_ROOM"] = "/d/suzhou/kedian";
			break;
		case 3:
			hometown = "无锡";
			my["START_ROOM"] = "/d/wuxi/kedian";
			break;
		case 4:
			hometown = "嘉兴";
			my["START_ROOM"] = "/d/jiaxing/yanyu";
			break;
		default:
			hometown = "宜兴";
			my["START_ROOM"] = "/d/yixing/nanxun";
			break;
		}
		break;
	case "4":
		switch (j)
		{
		case 0:
			hometown = "福州";
			my["START_ROOM"] = "/d/fuzhou/rongcheng";
			break;
		case 1:
			hometown = "泉州";
			my["START_ROOM"] = "/d/quanzhou/kedian";
			break;
		case 2:
			hometown = "台湾";
			my["START_ROOM"] = "/d/taiwan/anping";
			break;
		case 3:
			hometown = "延平";
			my["START_ROOM"] = "/d/yanping/road3";
			break;
		case 4:
			hometown = "石梁";
			my["START_ROOM"] = "/d/shiliang/gate";
			break;
		default:
			hometown = "澎湖";
			my["START_ROOM"] = "/d/taiwan/penghu";
			break;
		}
		break;
	default:
		switch (j)
		{
		case 0:
			hometown = "衡阳";
			my["START_ROOM"] = "/d/henshan/chaguan";
			break;
		case 1:
			hometown = "江陵";
			my["START_ROOM"] = "/d/jiangling/majiu";
			break;
		case 2:
			hometown = "岳阳";
			my["START_ROOM"] = "/d/yueyang/yueyanglou1";
			break;
		case 3:
			hometown = "佛山";
			my["START_ROOM"] = "/d/foshan/yingxionglou";
			break;
		case 4:
			hometown = "大理";
			my["START_ROOM"] = "/d/dali/baiyiminju";
			break;
		default:
			hometown = "成都";
			my["START_ROOM"] = "/d/chengdu/kedian";
			break;
		}
		break;
	}
	write("\n您的出生地是：" + hometown + "\n");
	my["hometown"] = hometown;
	write(@TEXT
※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
※ 一个人物的天赋对于他或她所修习的武艺息息相关。侠客行中的人物大    ※
※ 多具有以下四项显性天赋：                                              ※
※                                                                        ※
※ 膂力：影响攻击能力及负荷量的大小。                                    ※
※ 悟性：影响学习武功秘籍的速度及理解师傅的能力。                        ※
※ 根骨：影响体力恢复的速度及升级后所增加的体力。                        ※
※ 身法：影响防御及躲避的能力。                                          ※
※                                                                        ※
※ 每个人物另外还有六项起作用的隐性属性：                            ※
※                                                                        ※
※ 耐力：影响到打斗。耐力高的，在打斗中能更快地恢复元气。                ※
※ 灵性：影响技能学习。灵性高的，更容易多学些功夫。                      ※
※ 胆识：影响攻击成功率。胆识高的，倾向于进攻。                          ※
※ 定力：影响防御成功率。定力低的，容易被对手找到破绽反击。              ※
※ 福缘：影响到在游戏里的机遇。总体来说，越高越好。但不绝对如此。        ※
※ 容貌：容貌好的人，不容易引起敌意。对定力低的敌手，有震慑作用。        ※
※                                                                        ※
※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※ TEXT);
	if (ob->query("scborn/reset_gift"))
	{
		old = NPC_D->create_player(ob->query("id"));
		write("你前世的天赋为：\n\n");
		write("臂力：[ " + old->query("str") + " ]\t");
		write("悟性：[ " + old->query("int") + " ]\n");
		write("根骨：[ " + old->query("con") + " ]\t");
		write("身法：[ " + old->query("dex") + " ]\n");
		write("耐力：[ " + old->query("sta") + " ]\t");
		write("容貌：[ " + old->query("per") + " ]\n");
		write("灵性：[ " + old->query("spi") + " ]\t");
		write("福缘：[ " + old->query("kar") + " ]\n");
		write("胆识：[ " + old->query("cor") + " ]\t");
		write("定力：[ " + old->query("cps") + " ]\n");
		write("\n");
		destruct(old);
		write("你要继承前世的属性吗？(Y/N)");
		input_to("confirm_gift", ob, my);
		return;
	}
	config_gift(ob, my);
}

private
void confirm_gift(string arg, object ob, mapping my)
{
	object old;
	string chartype;

	arg = lower_case(arg);
	if (arg == "y" || arg == "Y")
	{
		write("\n你继承前世的先天属性。\n");
		old = NPC_D->create_player(ob->query("id"));
		my["str"] = old->query("str") + 2;
		my["int"] = old->query("int");
		my["con"] = old->query("con") + 2;
		my["dex"] = old->query("dex") + 2;
		my["sta"] = old->query("sta") + 2;
		my["per"] = old->query("per") + 2;
		my["spi"] = old->query("spi") + 2;
		my["kar"] = old->query("kar") + 2;
		my["cor"] = old->query("cor") + 2;
		my["cps"] = old->query("cps") + 2;
		chartype = old->query("character");
		destruct(old);
		write("您的电子邮件地址：");
		input_to("get_email", ob, my, chartype);
	}
	else if (arg == "n" || arg == "N")
	{
		write("你重新自己的先天属性。\n");
		config_gift(ob, my);
	}
	else
		write("你要继承前世的属性吗？(Y/N)");
	input_to("confirm_gift", ob, my);
}

private
void config_gift(object ob, mapping my)
{
	int all, min, max;

	all = 80 + 10 * ob->query("scborn/times");
	if (ob->query("scborn/times"))
		all += 10;
	max = 30 + 5 * ob->query("scborn/times");
	min = (all - max - max) / 2;
	//	min = 10+5*ob->query("scborn/times");
	printf("你的天赋总点数为" + all + "，您请输入您的膂力点数(" + min + "到" + max + ")：");
	input_to("sel_str", ob, my, all, min, max);
}

private
void sel_str(string qty1, object ob, mapping my, int all, int min, int max)
{
	int qty;
	qty = atoi(qty1);
	if (qty < min)
	{
		write(HIR "您选择的膂力数值不能小于" + min + "：\n" NOR);
		printf("你的天赋总点数为" + all + "，您请输入您的膂力点数(" + min + " 到 " + max + ")：");
		input_to("sel_str", ob, my, all, min, max);
	}
	else if (qty > max)
	{
		write(HIR "您选择的膂力数值不能大于" + max + "：\n" NOR);
		printf("你的天赋总点数为" + all + "，您请输入您的膂力点数(" + min + " 到 " + max + ")：");
		input_to("sel_str", ob, my, all, min, max);
	}
	else
	{
		my["str"] = qty;
		printf("你的天赋点数尚余%d点，您请输入您的悟性点数(" + min + " 到 " + max + ")：", all - my["str"]);
		input_to("sel_int", ob, my, all, min, max);
		return;
	}
}

private
void sel_int(string qty1, object ob, mapping my, int all, int min, int max)
{
	int qty;
	qty = atoi(qty1);
	if (qty < min)
	{
		write(HIR "您选择的悟性数值不能小于" + min + "：\n" NOR);
		printf("你的天赋点数尚余%d点，您请输入您的悟性点数(" + min + " 到 " + max + ")：", 80 - my["str"]);
		input_to("sel_int", ob, my, all, min, max);
	}
	else if (qty > max)
	{
		write(HIR "您选择的悟性数值不能大于" + max + "：\n" NOR);
		printf("你的天赋点数尚余%d点，您请输入您的悟性点数(" + min + " 到 " + max + ")：", 80 - my["str"]);
		input_to("sel_int", ob, my, all, min, max);
	}
	else
	{
		my["int"] = qty;
		printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：",
					 all - my["str"] - my["int"],
					 ((all - my["str"] - my["int"]) < (max + min) ? min : all - my["str"] - my["int"] - max),
					 (all - my["str"] - my["int"]) > (max + min) ? max : all - my["str"] - my["int"] - min);
		//		  80-my["str"]-my["int"],
		//		  (80-my["str"]-my["int"]<40)?10:80-my["str"]-my["int"]-30,
		//		  (80-my["str"]-my["int"]>40)?30:80-my["str"]-my["int"]-10);
		input_to("sel_con", ob, my, all, min, max);
		return;
	}
}

private
void sel_con(string qty1, object ob, mapping my, int all, int min, int max)
{
	int qty;
	qty = atoi(qty1);
	if (qty < min)
	{
		write(HIR "您选择的根骨数值不能小于" + min + "：\n" NOR);
		printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：",
					 all - my["str"] - my["int"],
					 (all - my["str"] - my["int"]) < (max + min) ? min : all - my["str"] - my["int"] - max,
					 (all - my["str"] - my["int"]) > (max + min) ? max : all - my["str"] - my["int"] - min);
		//		80-my["str"]-my["int"],
		//(80-my["str"]-my["int"]<40)?10:80-my["str"]-my["int"]-30,
		//(80-my["str"]-my["int"]>40)?30:80-my["str"]-my["int"]-10);
		input_to("sel_con", ob, my, all, min, max);
	}
	else if (qty > max)
	{
		write(HIR "您选择的根骨数值不能大于" + max + "：\n" NOR);
		printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：",
					 all - my["str"] - my["int"],
					 (all - my["str"] - my["int"]) < (max + min) ? min : all - my["str"] - my["int"] - max,
					 (all - my["str"] - my["int"]) > (max + min) ? max : all - my["str"] - my["int"] - min);
		//		80-my["str"]-my["int"],
		//		(80-my["str"]-my["int"]<40)?10:80-my["str"]-my["int"]-30,
		//		(80-my["str"]-my["int"]>40)?30:80-my["str"]-my["int"]-10);
		input_to("sel_con", ob, my, all, min, max);
	}
	else if (all - my["str"] - my["int"] > (max + min))
	{
		if (qty < all - my["str"] - my["int"] - max)
		{
			write(HIR "您选择的根骨数值不在允许范围内。\n" NOR);
			//			printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：", 80-my["str"]-my["int"], (80-my["str"]-my["int"]<40)?10:80-my["str"]-my["int"]-30, (80-my["str"]-my["int"]>40)?30:80-my["str"]-my["int"]-10);
			printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：",
						 all - my["str"] - my["int"],
						 (all - my["str"] - my["int"]) < (max + min) ? min : all - my["str"] - my["int"] - max,
						 (all - my["str"] - my["int"]) > (max + min) ? max : all - my["str"] - my["int"] - min);
			input_to("sel_con", ob, my, all, min, max);
		}
		else
		{
			my["con"] = qty;
			my["dex"] = all - my["str"] - my["int"] - my["con"];
			printf("\n膂力[%d]， 悟性[%d]， 根骨[%d]， 身法[%d]\n", my["str"], my["int"], my["con"], my["dex"]);
			write("您同意这一组天赋吗？");
			input_to("get_gift", ob, my);
			return;
		}
	}
	else
	{
		if (qty > all - my["str"] - my["int"] - min)
		{
			write(HIR "您选择的根骨数值不在允许范围内。\n" NOR);
			//		printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：", 80-my["str"]-my["int"], (80-my["str"]-my["int"]<40)?10:80-my["str"]-my["int"]-30, (80-my["str"]-my["int"]>40)?30:80-my["str"]-my["int"]-10);
			printf("你的天赋点数尚余%d点，您请输入您的根骨点数(%d 到 %d)：",
						 all - my["str"] - my["int"],
						 (all - my["str"] - my["int"]) < (max + min) ? min : all - my["str"] - my["int"] - max,
						 (all - my["str"] - my["int"]) > (max + min) ? max : all - my["str"] - my["int"] - min);
			input_to("sel_con", ob, my, all, min, max);
		}
		else
		{
			my["con"] = qty;
			my["dex"] = all - my["str"] - my["int"] - my["con"];
			printf("\n膂力[%d]， 悟性[%d]， 根骨[%d]， 身法[%d]\n", my["str"], my["int"], my["con"], my["dex"]);
			write("您同意这一组天赋吗？");
			input_to("get_gift", ob, my, all, min, max);
			return;
		}
	}
}

private
void get_gift(string yn, object ob, mapping my, int all, int min, int max)
{
	if (yn[0] != 'y' && yn[0] != 'Y')
	{
		printf("你的天赋总点数为" + all + "，您请输入您的膂力点数(" + min + " 到 " + max + ")：");
		input_to("sel_str", ob, my, all, min, max);
	}
	if (yn[0] == 'y' || yn[0] == 'Y')
	{
		write(@TEXT

							请选择你的人物性格属性：

									人生在世，有各种性格和抱负。性格属性的选择，或多或少影响了你今后
											的发展和未来。但每个性格属性都不是绝对的，如果你拿不定注意，就选普通
													吧。 你可以选择下列性格属性：

					1、冒险：胆识相对高些，不过定力就比较低了。 2、谨慎：定力相对高些，不过胆识就比较低了。 3、可人：容貌比较好些，别的不会太好，但也绝不太差。 4、睿智：灵性高些，能学到比较多的功夫。别的虽然一般，却也都过得去。 5、坚韧：耐力高些，但是你选的根骨不宜太低。 0、普通：什么都不考虑，也许有机会选到兼具上面若干项的好天赋呢。 TEXT);
		input_to("get_char", ob, my);
	}
}

private
void get_char(string chartype, object ob, mapping my)
{
	// 福缘
	my["kar"] = 10 + random(21) + 5 * ob->query("scborn/times");
	// 胆识、定力、容貌、灵性、耐力
	switch (chartype)
	{
	case "1":
		my["cor"] = 20 + random(11) + 3 * ob->query("scborn/times");
		my["cps"] = 10 + random(11) + 3 * ob->query("scborn/times");
		my["per"] = 15 + random(11) + 3 * ob->query("scborn/times");
		my["spi"] = 15 + random(11) + 3 * ob->query("scborn/times");
		my["sta"] = 15 + random(11) + 3 * ob->query("scborn/times");
		write("您选择了冒险的性格。\n");
		break;
	case "2":
		my["cor"] = 10 + random(11) + 3 * ob->query("scborn/times");
		my["cps"] = 20 + random(11) + 3 * ob->query("scborn/times");
		my["per"] = 15 + random(11) + 3 * ob->query("scborn/times");
		my["spi"] = 15 + random(11) + 3 * ob->query("scborn/times");
		my["sta"] = 15 + random(11) + 3 * ob->query("scborn/times");
		write("您选择了谨慎的性格。\n");
		break;
	case "3":
		my["cor"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["cps"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["per"] = 20 + random(11) + 3 * ob->query("scborn/times");
		my["spi"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["sta"] = 13 + random(15) + 3 * ob->query("scborn/times");
		write("您选择了可人的性格。\n");
		break;
	case "4":
		my["cor"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["cps"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["per"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["spi"] = 20 + random(11) + 3 * ob->query("scborn/times");
		my["sta"] = 13 + random(15) + 3 * ob->query("scborn/times");
		write("您选择了睿智的性格。\n");
		break;
	case "5":
		my["cor"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["cps"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["per"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["spi"] = 13 + random(15) + 3 * ob->query("scborn/times");
		my["sta"] = 20 + random(11) + 3 * ob->query("scborn/times");
		write("您选择了坚韧的性格。\n");
		break;
	default:
		my["cor"] = 10 + random(21) + 3 * ob->query("scborn/times");
		my["cps"] = 10 + random(21) + 3 * ob->query("scborn/times");
		my["per"] = 10 + random(21) + 3 * ob->query("scborn/times");
		my["spi"] = 10 + random(21) + 3 * ob->query("scborn/times");
		my["sta"] = 10 + random(21) + 3 * ob->query("scborn/times");
		write("您不选择特定的性格。\n");
		break;
	}
	write("\n您的电子邮件地址：");
	input_to("get_email", ob, my, chartype);
}

private
void get_email(string email, object ob, mapping my, string chartype)
{
	object user;

	write("\n");
	if (email == "" || strsrch(email, "@") == -1)
	{
		write("电子邮件地址需要是 id@address 的格式。\n");
		write("您的电子邮件地址：");
		input_to("get_email", ob, my);
		return;
	}
	ob->set("email", email);
	ob->set("registered", 1);

	// If you want do race stuff,ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if (!objectp(user = make_body(ob)))
		return;
	if (ob->query("scborn/times") == 6)
	{
		my["str"] = 60;
		my["dex"] = 60;
		my["con"] = 60;
		my["int"] = 60;
		my["kar"] = 60;
		my["cor"] = 60;
		my["cps"] = 60;
		my["per"] = 60;
		my["spi"] = 60;
		my["sta"] = 60;
	}
	user->set("str", my["str"]);
	user->set("dex", my["dex"]);
	user->set("con", my["con"]);
	user->set("int", my["int"]);
	user->set("kar", my["kar"]);
	user->set("cor", my["cor"]);
	user->set("cps", my["cps"]);
	user->set("per", my["per"]);
	user->set("spi", my["spi"]);
	user->set("sta", my["sta"]);
	user->set("START_ROOM", my["START_ROOM"]);
	//save in data
	//save in user ob and login ob
	user->set("base", my);
	user->set("scborn/times", ob->query("scborn/times"));
	ob->set("base", my);
	/////////
	user->set("character", chartype);
	user->set("born/hometown", my["hometown"]);
	user->set("born/area", my["area"]);
	ob->set("registered", 1);
	user->set("registered", 1);

	write("您要扮演男性(m)的角色或女性(f)的角色？");
	input_to("get_gender", ob, user);
}

private
void get_gender(string gender, object ob, object user)
{
	object res;
	string err;

	write("\n");
	if (gender == "")
	{
		write("您要扮演男性(m)的角色或女性(f)的角色？");
		input_to("get_gender", ob, user);
		return;
	}

	if (gender[0] == 'm' || gender[0] == 'M')
		user->set("gender", "男性");
	else if (gender[0] == 'f' || gender[0] == 'F')
		user->set("gender", "女性");
	else
	{
		write("对不起，您只能选择男性(m)或女性(f)的角色：");
		input_to("get_gender", ob, user);
		return;
	}

	log_file("Newuser", sprintf("%s (%s) was created from %s (%s) with (%d %d %d %d)\n", user->query("name"), user->query("id"), query_ip_name(ob), ctime(time()), user->query("str"), user->query("int"), user->query("con"), user->query("dex")));
	ob->set("created_on", ctime(time()));
	ob->set("created_from", query_ip_name(ob));
	init_new_player(user);
	if (ob->query("scborn/reset_gift"))
	{
		err = catch (res = SCBORN_D->check_user(user, ob)); //读取保存的东西等
		if (stringp(err))
			CHANNEL_D->do_channel(this_object(), "sys", "SCBORN_D CATCH ERROR=" + err);
		if (!err && objectp(res))
			user = res;
		ob->delete ("scborn/reset_gift");
		user->set("scborn/times", ob->query("scborn/times"));
	}
	enter_world(ob, user);
	write("\n");
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	user = new (ob->query("body"));
	if (!user)
	{
		write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
		write(err + "\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name(ob->query("name"), ({ob->query("id")}));
	return user;
}

private
init_new_player(object user)
{
	user->set("title", "普通百姓");
	user->set("birthday", time());
	user->set("potential", 99);
	user->set("jing", 100);
	user->set("qi", 100);
	user->set("tili", 100);
	user->set("food", (user->query("str") + 10) * 10);
	user->set("water", (user->query("str") + 10) * 10);

	user->set("channels", ({"chat", "rumor", "party", "xkx", "sing", "es", "snow"}));
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, shoe, room, mailbox, gift, login_ob;
	string startroom;
	string baseroom;
	mixed *ltime;
	int i, cardnum, is_holiday = 0;

	// 节日映射数组，请按照格式添加新节日。
	// Added by Constant Jan 2 2001.
	mapping *holidays = ({
			([
									24:12,
									25:12,
					"cardfile":"/clone/misc/cards/card_cs",
	]),
			([
									31:12,
									 1:1,
					"cardfile":"/clone/misc/cards/card_ny",
	]),
			([
									11:2,
									12:2,
									13:2,
									14:2,
					"cardfile":"/clone/misc/cards/card_ft",
	]),
	});

	user->set_temp("link_ob", ob);
	// 登录时记录经验和潜能, 以及登录时间, 为离线信息预留
	user->set_temp("nowexp", user->query("combat_exp"));
	user->set_temp("nowpot", user->query("potential"));
	user->set_temp("nowtime", time());
	user->set_name(user->query("name"), ({user->query("id")}));
	ob->set_temp("body_ob", user);
	ob->set_temp("new_char", user);
	user->set("registered", ob->query("registered"));
	exec(user, ob);

	write("\n目前权限：" + wizhood(user) + "\n");
	user->setup();
	if (!user->query("food") && !user->query("water") &&
			ob->query("age") == 14)
	{
		user->set("food", user->max_food_capacity());
		user->set("water", user->max_water_capacity());
	}

	// In case of new player, we save them here right aftre setup
	// compeleted.
	user->save();
	ob->save();
	// Use condition to auto save user file
	user->apply_condition("autosave", 1);

	// 根据时间判断是否为节日，并赠送玩家礼品。
	// Added by Constant Jan 2 2001
	ltime = localtime(time());

	for (i = 0; i < sizeof(holidays); i++)
	{
		if (holidays[i][ltime[LT_MDAY]] == ltime[LT_MON] + 1)
		{
			if (!user->query("holiday_cards") &&
					user->query("mud_age") > 86400)
			{
				cardnum = howmany_card();
				set_card(cardnum + 1);
				gift = new (holidays[i]["cardfile"]);
				gift->move(user);
				user->set("holiday_cards", cardnum);
			}
			is_holiday = 1;
			break;
		}
	}

	// 若不是节日，则删除玩家身上属性，使下一节日能收到赠品。
	// Added by Constant Jan 2 2001
	if (!is_holiday && user->query("holiday_cards"))
		user->delete ("holiday_cards");

	if (wizhood(user) == "(player)")
	{
		if (user->query("class") == "bonze")
		{
			if (user->query("gender") == "女性")
			{
				cloth = new ("/clone/cloth/ni-cloth");
				shoe = new ("/clone/cloth/ni-shoe");
			}
			else
			{
				cloth = new ("/clone/cloth/seng-cloth");
				shoe = new ("/clone/cloth/seng-shoe");
			}
		}
		else
		{
			if (user->query("class") == "taoist")
			{
				if (user->query("gender") == "女性")
				{
					cloth = new ("/clone/cloth/daogu-cloth");
					shoe = new ("/clone/cloth/dao-shoe");
				}
				else
				{
					cloth = new ("/clone/cloth/dao-cloth");
					shoe = new ("/clone/cloth/dao-shoe");
				}
			}
			else
			{
				if (user->query("gender") == "女性")
				{
					cloth = new ("/clone/cloth/female-cloth");
					shoe = new ("/clone/cloth/female-shoe");
				}
				else
				{
					cloth = new ("/clone/cloth/male-cloth");
					shoe = new ("/clone/cloth/male-shoe");
				}
			}
		}
	}
	else
	{
		if (!user->query("no_look_wiz"))
		{
			cloth = new ("/clone/cloth/wiz-cloth.c");
			shoe = new ("/clone/cloth/wiz-shoe.c");
		}
		else
		{
			cloth = new ("/clone/cloth/male-cloth");
			shoe = new ("/clone/cloth/male-shoe");
		}
	}
	cloth->move(user);
	cloth->wear();
	shoe->move(user);
	shoe->wear();

	if (!silent)
	{
		baseroom = START_ROOM;
		if (stringp(user->query("START_ROOM")))
			baseroom = user->query("START_ROOM");
		if (ob->query("registered") == 0)
			cat(UNREG_MOTD);
		else
			cat(MOTD);
		if (user->is_ghost())
			startroom = DEATH_ROOM;
		else if (!stringp(startroom = user->query("startroom")))
			startroom = baseroom;

		if (!catch (load_object(startroom)))
			user->move(startroom);
		else
		{
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		if (!user->query("env/invisibility"))
			tell_room(startroom, user->query("name") + "连线进入这个世界。\n", ({user}));
	}
	login_ob = new (LOGIN_OB);
	login_ob->set("id", user->query("id"));
	login_ob->restore();
	write("\n你上次光临侠客行一百是 " + HIG + ctime(login_ob->query("last_on")) + NOR + " 从 " + HIR + login_ob->query("last_from") + NOR + " 连接的。\n\n");
	destruct(login_ob);

	CHANNEL_D->do_channel(this_object(), "sys",
												sprintf("%s(%s)由%s连线进入。共清除 " + reclaim_objects() + " 个变数。\n", user->name(), user->query("id"), query_ip_name(user)));
	UPDATE_D->check_user(user);
	mailbox = new ("/clone/misc/mailbox");
	mailbox->move(user);
	//  user->start_call_out( (: call_other,"/cmds/usr/news","check_me",user :),5);
}

varargs void reconnect(object ob, object user, int silent)
{
	user->set_temp("link_ob", ob);
	ob->set_temp("new_char", user);
	ob->set_temp("body_ob", user);
	exec(user, ob);

	user->reconnect();
	if (!silent)
	{
		if (!wizardp(user) || !user->query("env/invisibility"))
			tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n",
								({user}));
	}
	CHANNEL_D->do_channel(this_object(), "sys",
												sprintf("%s由%s重新连线进入。", user->query("name"), query_ip_name(user)));
	UPDATE_D->check_user(user);
}

int check_legal_id(string id)
{
	int i;

	i = strlen(id);

	if ((strlen(id) < 3) || (strlen(id) > 8))
	{
		write("对不起，你的英文名字必须是 3 到 8 个英文字母。\n");
		return 0;
	}
	while (i--)
		if (id[i] < 'a' || id[i] > 'z')
		{
			write("对不起，你的英文名字只能用英文字母。\n");
			return 0;
		}

	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);

	if ((strlen(name) < 4) || (strlen(name) > 10))
	{
		write("对不起，你的中文名字必须是 2 到 5 个中文字。\n");
		return 0;
	}
	while (i--)
	{
		if (name[i] <= ' ')
		{
			write("对不起，你的中文名字不能用控制字元。\n");
			return 0;
		}
		if ((strsrch(name, "　") >= 0) ||
				(strsrch(name, "爸") >= 0))
		{
			write("对不起，你的中文名字不能用引起误会的单字。\n");
			return 0;
		}
		if (i % 2 == 0 && !is_chinese(name[i..< 0]))
		{
			write("对不起，请您用「中文」取名字。\n");
			return 0;
		}
	}
	if (member_array(name, banned_name) != -1)
	{
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if (objectp(ob = find_player(name)))
		return ob;
	body = children(USER_OB);
	for (int i = 0; i < sizeof(body); i++)
		if (clonep(body[i]) && getuid(body[i]) == name)
			return body[i];

	return 0;
}

int set_wizlock(int level)
{
	if (wiz_level(this_player(1)) <= level)
		return 0;
	if (geteuid(previous_object()) != ROOT_UID)
		return 0;
	wiz_lock_level = level;
	return 1;
}
// add for ten top.
int set_madlock(int setmark)
{
	// if( wiz_level(this_player(1)) < wiz_level("(arch)") )
	// 	return 0;
	if (setmark == 1)
		mad_lock = 1;
	else
		mad_lock = 0;
	return 1;
}

int get_madlock()
{
	return mad_lock;
}
int howmuch_money(object ob)
{
	int total;
	int total2;
	object gold, silver, coin;

	total = 0;
	total2 = 0;

	gold = present("gold_money", ob);
	silver = present("silver_money", ob);
	coin = present("coin_money", ob);

	if (gold)
		total += gold->value();
	if (silver)
		total += silver->value();
	if (coin)
		total += coin->value();

	total2 = (int)ob->query("balance");
	if (!total2 || total2 < 0)
	{
		ob->set("balance", 0);
	}
	total = total + total2;
	return total;
}

// 增加浩劫判断条件变量的读取和设置
void add_dienpc()
{
	dienpc++;
}
void set_dienpc(int i)
{
	if (i == -1)
	{
		mad_lock = 1;
		dienpc = 0;
		return;
	}
	dienpc = i;
}
int get_dienpc()
{
	return dienpc;
}
