// jingcaiban.c

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

// 全局变量，即储存玩家押注的所有数据
mapping *all_biao;
// 全局变量，此处为目前数量
int num;
// 全局变量，此处为最终结杲
mapping *end_biao;
int jieguo;

// 以下七行为函数声明
int do_read(string);
int do_post(string);
int do_ya(string);
void enough_rest();
string codetoteam(string arg);
string ordercode(string arg, int arg1);
string upcase(string arg);

string *team = ({"阿根廷", "巴西", "比利时", "喀麦隆", "中国", "哥斯达黎加", "德国", "丹麦",
				 "厄瓜多尔", "西班牙", "法国", "克罗地亚", "爱尔兰", "意大利", "日本", "韩国",
				 "墨西哥", "尼日利亚", "波兰", "葡萄牙", "巴拉圭", "俄罗斯", "沙特", "瑞典",
				 "斯洛文尼亚", "塞内加尔", "突尼斯", "土耳其", "英格兰", "美国", "乌拉圭", "南非"});
string *code = ({"AR", "BR", "BE", "CM", "CN", "CR", "DE", "DK",
				 "EC", "ES", "FR", "HR", "IE", "IT", "JP", "KP",
				 "MX", "NG", "PL", "PT", "PY", "RU", "SA", "SE",
				 "SI", "SN", "TN", "TU", "UK", "US", "UY", "ZA"});

void create()
{
	set_name(HIY "世界杯竞猜版" NOR, ({"board", "ban"}));
	set("long", "这是一个记录玩家的竞猜押注情况的版。
押注请read rules，查看目前的投注情况请read ban。\n");
	set("unit", "张");
	set("no_put", 1);
	set("no_get", 1);
//设大点不让玩家Get
	set_weight(900000000);
	seteuid(getuid());
	restore();
}

void init()
{
	add_action("do_read", "read");
	add_action("do_post", "post");
	add_action("do_ya", "ya");
	add_action("do_duijiang", "duijiang");
	add_action("do_duijiang", "duixian");
}

string query_save_file()
{
	// 定义一个储存文件的路径
	return DATA_DIR + "board/fifa2002_b";
}

// 玩家下注
int do_ya(string arg)
{
	int i;
	string c, t, c1, c2, c3, c4, c5, c6, c7, c8;
	object ob, me = this_player();
	mapping biao;

	// 表示停止下注，由巫师在do_post()函数里加入
	if (query("end_ya"))
		return notify_fail("截止时间已过，下回赶早。\n");
	// 防止多人同意押注产生意外
	if (query_temp("busy"))
		return notify_fail("稍候........\n");
	// 分析玩家指令
	if (!arg)
		return notify_fail("命令格式：ya <类别> <球队> <多少两黄金>\n");
	arg = upcase(arg);
	if (sscanf(arg, "%s %s %d", t, c, i) != 3)
		return notify_fail("命令格式：ya <类别> <球队> <多少两黄金>\n");
	// 排除一些不可能的押注可能
	if (t != "1" && t != "2" && t != "4" && t != "8")
		return notify_fail("你总要先选定投注类别罢？\n");
	// 至少1gold
	if (i < 1)
		return notify_fail("你想白赚啊？\n");
	// 上限，可以自由调整
	if (i > 1000)
		return notify_fail("押得太多，请少于1000。\n");
	if ((int)i > me->query("balance") / 10000)
		// 钱庄的存款不够押的钱
		return notify_fail("这里不收现金！到钱庄存够了钱再来！\n");

	// 押冠军
	switch (t)
	{
	case "1":
		// 调玩家身上的参数
		if (me->query("fifa2002/1"))
			return notify_fail("你只能给冠军下一次注！\n");
		if (codetoteam(c) == "未知国名")
			return notify_fail("先看好国家代码再来！\n");
		message_vision("$N想了半天大声喊道：“我认为" HIR + codetoteam(c) + NOR "队能拿到冠军！押 " HIY + chinese_number(i) + NOR " 两黄金！”\n", me);
		// 在玩家身上设下押的结果
		me->set("fifa2002/1", c);
		// 押的黄金数
		me->set("fifa2002/10", i);
		// 这是一个记录该玩家押注数据的映射
		biao = ([
			  "id":me->query("id"),
			"name":me->query("name"),
			"type":1,
			"code":c,
			"gold":i,
		]);
		break;
	case "2":
		// 调玩家身上的参数
		if (me->query("fifa2002/2"))
			return notify_fail("你只能给亚军下一次注！\n");
		if (codetoteam(c) == "未知国名")
			return notify_fail("先看好国家代码再来！\n");
		message_vision("$N想了半天大声喊道：“我认为" HIR + codetoteam(c) + NOR "队能拿到亚军！押 " HIY + chinese_number(i) + NOR " 两黄金！”\n", me);
		// 在玩家身上设下押的结果
		me->set("fifa2002/2", c);
		// 押的黄金数
		me->set("fifa2002/20", i);
		// 这是一个记录该玩家押注数据的映射
		biao = ([
			  "id":me->query("id"),
			"name":me->query("name"),
			"type":2,
			"code":c,
			"gold":i,
		]);
		break;
	case "4":
		// 调玩家身上的参数
		if (me->query("fifa2002/4"))
			return notify_fail("你只能给四强下一次注！\n");
		if (sscanf(c, "%s-%s-%s-%s", c1, c2, c3, c4) != 4)
			return notify_fail("国家代码输入格式错！\n");
		if (codetoteam(c1) == "未知国名")
			return notify_fail("没有" HIR + c1 + NOR "这国家代码！\n");
		if (codetoteam(c2) == "未知国名")
			return notify_fail("没有" HIR + c2 + NOR "这国家代码！\n");
		if (codetoteam(c3) == "未知国名")
			return notify_fail("没有" HIR + c3 + NOR "这国家代码！\n");
		if (codetoteam(c4) == "未知国名")
			return notify_fail("没有" HIR + c4 + NOR "这国家代码！\n");
		c = ordercode(c, 4);
		message_vision("$N想了半天大声喊道：“我认为" HIR + codetoteam(c1) + "、" + codetoteam(c2) + "、" + codetoteam(c3) + "、" + codetoteam(c4) + NOR "队能进入四强！押 " HIY + chinese_number(i) + NOR " 两黄金！”\n", me);
		// 在玩家身上设下押的结果
		me->set("fifa2002/4", c);
		// 押的黄金数
		me->set("fifa2002/40", i);
		// 这是一个记录该玩家押注数据的映射
		biao = ([
			  "id":me->query("id"),
			"name":me->query("name"),
			"type":4,
			"code":c,
			"gold":i,
		]);
		break;
	case "8":
		// 调玩家身上的参数
		if (me->query("fifa2002/8"))
			return notify_fail("你只能给八强下一次注！\n");
		if (sscanf(c, "%s-%s-%s-%s-%s-%s-%s-%s", c1, c2, c3, c4, c5, c6, c7, c8) != 8)
			return notify_fail("国家代码格式输入错！\n");
		if (codetoteam(c1) == "未知国名")
			return notify_fail("没有" HIR + c1 + NOR "这国家代码！\n");
		if (codetoteam(c2) == "未知国名")
			return notify_fail("没有" HIR + c2 + NOR "这国家代码！\n");
		if (codetoteam(c3) == "未知国名")
			return notify_fail("没有" HIR + c3 + NOR "这国家代码！\n");
		if (codetoteam(c4) == "未知国名")
			return notify_fail("没有" HIR + c4 + NOR "这国家代码！\n");
		if (codetoteam(c5) == "未知国名")
			return notify_fail("没有" HIR + c5 + NOR "这国家代码！\n");
		if (codetoteam(c6) == "未知国名")
			return notify_fail("没有" HIR + c6 + NOR "这国家代码！\n");
		if (codetoteam(c7) == "未知国名")
			return notify_fail("没有" HIR + c7 + NOR "这国家代码！\n");
		if (codetoteam(c8) == "未知国名")
			return notify_fail("没有" HIR + c8 + NOR "这国家代码！\n");
		c = ordercode(c, 8);
		message_vision("$N想了半天大声喊道：“我认为" HIR + codetoteam(c1) + "、" + codetoteam(c2) + "、" + codetoteam(c3) + "、" + codetoteam(c4) + "、" + codetoteam(c5) + "、" + codetoteam(c6) + "、" + codetoteam(c7) + "、" + codetoteam(c8) + NOR "队能进入八强！押 " HIY + chinese_number(i) + NOR " 两黄金！”\n", me);
		// 在玩家身上设下押的结果
		me->set("fifa2002/8", c);
		// 押的黄金数
		me->set("fifa2002/80", i);
		// 这是一个记录该玩家押注数据的映射
		biao = ([
			  "id":me->query("id"),
			"name":me->query("name"),
			"type":8,
			"code":c,
			"gold":i,
		]);
		break;
	}
	me->add("balance", -i * 10000);
	tell_object(me, "钱庄已经扣除了你押下的" + chinese_number(i) + "两黄金。请等候结果吧！\n");
	if (!pointerp(all_biao))
		all_biao = ({biao});
	else
		all_biao += ({biao});
	// 储存进这个文件对应的.o文件里
	save();
	remove_call_out("enough_rest");
	// 1秒后取消busy
	call_out("enough_rest", 1);
	return 1;
}

// 巫师专用，确定结果
int do_post(string arg)
{
	int i;
	string c, c1, c2, c3, c4, c5, c6, c7, c8;
	mapping end;
	object me = this_player();

	if (!wizardp(me))
		return 0;
	if (arg == "end")
	{
		// 停止押注
		set("end_ya", 1);
		message("channel:sys", HIM "【谣言】" HIR "某人：竞猜版开始停止下注，请关注比赛结果！\n" NOR, users());
		save();
		return 1;
	}
	// 分析巫师指令
	if (!arg)
		return notify_fail("命令格式：post <类别> <结果>\n");
	arg = upcase(arg);
	if (sscanf(arg, "%d %s", i, c) != 2)
		return notify_fail("命令格式：post <类别> <结果>\n");
	switch (i)
	{
	case 1:
		message("channel:sys", HIM "【谣言】" HIR "某人：竞猜版冠军结果公布，是 " HIY + codetoteam(c) + HIR " ！押对的快去兑奖啊！\n" NOR, users());
		break;
	case 2:
		message("channel:sys", HIM "【谣言】" HIR "某人：竞猜版亚军结果公布，是 " HIY + codetoteam(c) + HIR " ！押对的快去兑奖啊！\n" NOR, users());
		break;
	case 4:
		c = ordercode(c, 4);
		if (sscanf(c, "%s-%s-%s-%s", c1, c2, c3, c4) != 4)
			return notify_fail("国家代码输入格式错！\n");
		if (codetoteam(c1) == "未知国名")
			return notify_fail("没有" HIR + c1 + NOR "这国家代码！\n");
		if (codetoteam(c2) == "未知国名")
			return notify_fail("没有" HIR + c2 + NOR "这国家代码！\n");
		if (codetoteam(c3) == "未知国名")
			return notify_fail("没有" HIR + c3 + NOR "这国家代码！\n");
		if (codetoteam(c4) == "未知国名")
			return notify_fail("没有" HIR + c4 + NOR "这国家代码！\n");
		message("channel:sys", HIM "【谣言】" HIR "某人：竞猜版四强结果公布，是 " HIY + codetoteam(c1) + "、" + codetoteam(c2) + "、" + codetoteam(c3) + "、" + codetoteam(c4) + HIR " ！押对的快去兑奖啊！\n" NOR, users());
		break;
	case 8:
		c = ordercode(c, 8);
		if (sscanf(c, "%s-%s-%s-%s-%s-%s-%s-%s", c1, c2, c3, c4, c5, c6, c7, c8) != 8)
			return notify_fail("国家代码格式输入错！\n");
		if (codetoteam(c1) == "未知国名")
			return notify_fail("没有" HIR + c1 + NOR "这国家代码！\n");
		if (codetoteam(c2) == "未知国名")
			return notify_fail("没有" HIR + c2 + NOR "这国家代码！\n");
		if (codetoteam(c3) == "未知国名")
			return notify_fail("没有" HIR + c3 + NOR "这国家代码！\n");
		if (codetoteam(c4) == "未知国名")
			return notify_fail("没有" HIR + c4 + NOR "这国家代码！\n");
		if (codetoteam(c5) == "未知国名")
			return notify_fail("没有" HIR + c5 + NOR "这国家代码！\n");
		if (codetoteam(c6) == "未知国名")
			return notify_fail("没有" HIR + c6 + NOR "这国家代码！\n");
		if (codetoteam(c7) == "未知国名")
			return notify_fail("没有" HIR + c7 + NOR "这国家代码！\n");
		if (codetoteam(c8) == "未知国名")
			return notify_fail("没有" HIR + c8 + NOR "这国家代码！\n");
		message("channel:sys", HIM "【谣言】" HIR "某人：竞猜版八强结果公布，是 " HIY + codetoteam(c1) + "、" + codetoteam(c2) + "、" + codetoteam(c3) + "、" + codetoteam(c4) + "、" + codetoteam(c5) + "、" + codetoteam(c6) + "、" + codetoteam(c7) + "、" + codetoteam(c8) + HIR " ！押对的快去兑奖啊！\n" NOR, users());
		break;
	default:
		return notify_fail(HIR "哪有这个类别！\n" NOR);
	}
	// 这是一个记录结果数据的映射
	end = ([
		"type":i,
		"code":c,
	]);
	// 最终结果储存进这个文件对应的.o文件里
	if (!pointerp(end_biao))
		end_biao = ({end});
	else
		end_biao += ({end});
	jieguo = 1;
	save();
	// 更新
	return 1;
}
// 玩家查看
int do_read(string arg)
{
	int i, j;
	object me = this_player();
	string name, str, str1, str2;
	mapping biao;

	if (arg == "rules")
	{
		//这个规则根据每次巫师设计的定
		write("
    世界杯的冠军、亚军、四强、八强分别谁属？欢迎在此押注：
押注者以黄金为单位，最高可押一千黄金，最少也要押一两黄金。现金
不收，必须先存进钱庄。押赌后钱庄直接扣钱。押赌时间到六月十日截
止。押对八强的一赔二十，四强的一赔十，冠亚军的一赔八，比赛揭晓，
押中者按倍数返还黄金，不中者则罢。
    想好了后就 "HIR"ya <类别> <国名编号> <多少两黄金> "NOR"。
    例如：
    想压一千黄金给阿根廷为冠军，则ya 1 AR 1000。
    如果认为四强是阿根廷、法国、巴西、德国，而且想押五百黄金的
话，则ya 4 AR-BR-DE-FR 500。当然，顺序是无所谓的。
    当然每个ID只能押一次，押过不许后悔！\n

类    别：   "HIY"1-冠军 2-亚军 4-四强 8-八强"NOR"
国家编号："HIC"
           A组 法国FR    丹麦DK    乌拉圭UY    塞内加尔SN
           B组 南非ZA    西班牙ES  巴拉圭PY    斯洛文尼亚SI
           C组 巴西BR    中国CN    土耳其TU    哥斯达黎加CR
           D组 波兰PL    美国US    韩国KP      葡萄牙PT  
           E组 德国DE    沙特SA    爱尔兰IE    喀麦隆CM
           F组 瑞典SE    阿根廷AR  英格兰UK    尼日利亚NG
           G组 意大利IT  墨西哥MX  克罗地亚HR  厄瓜多尔EC
           H组 日本JP    俄罗斯RU  比利时BE    突尼斯TN
\n"NOR);
		write("开奖后请使用duixian <类别> 指令，你的奖金将自动进入你帐户。\n");
		return 1;
	}
	if (arg == "ban")
	{
		//有了分数的参数
		if (num)
			write("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n" HIG "世界杯赛投注竞猜版  ");
		write(!jieguo ? RED "还在投注中！" : HIR "开始兑奖(duijiang)了！");
		//表示还没有数据
		if (!pointerp(end_biao) || !sizeof(end_biao))
			write(HIY "\n巫师尚未设定结果。\n" NOR);
		else
		{
			write(HIY "\n比赛结果\n" NOR);
			for (i = 0; i < sizeof(end_biao); i++)
			{
				switch ((int)end_biao[i]["type"])
				{
				case 1:
					write(HIR "\n冠军 ");
					break;
				case 2:
					write(HIR "\n亚军 ");
					break;
				case 4:
					write(HIR "\n四强 ");
					break;
				case 8:
					write(HIR "\n八强 ");
					break;
				}
				for (j = 0; j < sizeof(code); j++)
					if (strsrch(end_biao[i]["code"], code[j]) >= 0)
						write(HIY + team[j] + " " NOR);
			}
		}
		//表示还没有数据
		if (!pointerp(all_biao) || !sizeof(all_biao))
		{
			write(HIG "\n\n还没有人开始投注。\n");
			return 1;
		}
		write(HIG "\n\n已有 " + sizeof(all_biao) + " 个玩家投注：\n" HIY "玩家名         投注类别 押黄金数  　             国家名\n" HIG "———————————————————————————————————\n" NOR);
		str1 = HIM "已经兑过奖的玩家：                \n" NOR;
		str2 = HIM "还未兑过奖的玩家：                \n" NOR;
		// all_biao也是全局变量，看文件头
		for (i = 0; i < sizeof(all_biao); i++)
		{
			// 取出每个押注玩家的名字
			str = sprintf("%18s ", all_biao[i]["name"] + "(" + all_biao[i]["id"] + ")");
			switch ((int)all_biao[i]["type"])
			{
			case 1:
				str += HIR "冠军" NOR;
				break;
			case 2:
				str += HIR "亚军" NOR;
				break;
			case 4:
				str += HIR "四强" NOR;
				break;
			case 8:
				str += HIR "八强" NOR;
				break;
			}
			str += sprintf("%8s", all_biao[i]["gold"] + "两 ");
			for (j = 0; j < sizeof(code); j++)
				if (strsrch(all_biao[i]["code"], code[j]) >= 0)
					str += team[j] + " ";
			// dui这个参数是在兑奖后加入的，这表示没兑奖的，加入str2
			if (!(int)all_biao[i]["dui"])
				str2 += str + "\n";
			// 有dui参数的，记入str1
			else
				str1 += str + "\n";
		}
		// 显示信息
		write(str1 + "\n" + str2 + "\n" NOR);
		return 1;
	}
	else
		write("你要看什么？押注规则请read rules，押注情况请read ban。\n");
	return 1;
}

void enough_rest()
{
	delete_temp("busy");
}
// 兑奖指令
int do_duijiang(string arg)
{
	int i, j, k, item, t;
	string result;
	object ob, me = this_player();
	mapping biao, fifa2002;

	// 没有jieguo就表示没有开始兑奖
	if (!jieguo)
		return notify_fail("还未到兑奖时间！\n");
	if (!query("end_ya"))
		return notify_fail("还未到兑奖时间！\n");
	if (query_temp("busy"))
		return notify_fail("稍候........\n");
	set_temp("busy", 1);
	k = 0;
	// 分析指令
	if (!arg)
		return notify_fail("命令格式：duijiang <类别>\n");

	switch (arg)
	{
	case "1":
		item = 1;
		t = 8;
		break;
	case "2":
		item = 2;
		t = 8;
		break;
	case "4":
		item = 4;
		t = 10;
		break;
	case "8":
		item = 8;
		t = 20;
		break;
	default:
		return notify_fail("没有这个项目吧！\n");
	}
	for (i = 0; i < sizeof(all_biao); i++)
	{
		if ((int)all_biao[i]["type"] == item &&
			all_biao[i]["id"] == me->query("id"))
		{
			if (all_biao[i]["dui"])
				return notify_fail("你已兑过奖啦！\n");
			result = all_biao[i]["code"];
			j = all_biao[i]["gold"];
			// 表示此人兑过奖了
			all_biao[i]["dui"] = 1;
			// 存盘
			save();
		}
	}
	for (i = 0; i < sizeof(end_biao); i++)
	{
		if ((int)end_biao[i]["type"] == item &&
			result == end_biao[i]["code"])
		{
			k = j * t;
		}
	}
	if (k > 0)
	// 中奖就给吧
	{
		write("你押 " + j + " 两黄金，按规定得奖金 " + k + " 两黄金，已划入你的钱庄帐户！\n");
		me->add("balance", k * 10000);
		message("channel:sys", HIM "【谣言】" HIR "某人：" + me->name() + "兑奖得到 " + chinese_number(k) + " 两黄金！\n" NOR, users());
		return 1;
	}
	else
	// 没有对的也来个空门奖吧
	{
		ob = new ("/clone/food/jitui");
		ob->move(me);
		write("你没押对，但发一个安慰奖，送你一根鸡腿吧！\n");
		message_vision(HIY "竞猜表上头突然油光一闪，“扑”地掉下一根油光光的鸡腿，正好掉进$N的手中。\n" NOR, me);
	}
	remove_call_out("enough_rest");
	call_out("enough_rest", 1);
	return 1;
}
// 对玩家输入的国家代码进行字母排序
string ordercode(string arg, int arg1)
{
	int i, j;
	string nc, nc1, nc2, nc3, nc4, nc5, nc6, nc7, nc8;

	j = 1;
	for (i = 0; i < sizeof(code); i++)
		if (strsrch(arg, code[i]) >= 0)
		{
			switch (j)
			{
			case 1:
				nc1 = code[i];
				break;
			case 2:
				nc2 = code[i];
				break;
			case 3:
				nc3 = code[i];
				break;
			case 4:
				nc4 = code[i];
				break;
			case 5:
				nc5 = code[i];
				break;
			case 6:
				nc6 = code[i];
				break;
			case 7:
				nc7 = code[i];
				break;
			case 8:
				nc8 = code[i];
				break;
			}
			j++;
		}
	if (arg1 == 4)
		nc = nc1 + "-" + nc2 + "-" + nc3 + "-" + nc4;
	if (arg1 == 8)
		nc = nc1 + "-" + nc2 + "-" + nc3 + "-" + nc4 + "-" + nc5 + "-" + nc6 + "-" + nc7 + "-" + nc8;
	return nc;
}
// 国家代码大写修正
string upcase(string arg)
{
	arg = replace_string(arg, "a", "A");
	arg = replace_string(arg, "b", "B");
	arg = replace_string(arg, "c", "C");
	arg = replace_string(arg, "d", "D");
	arg = replace_string(arg, "e", "E");
	arg = replace_string(arg, "f", "F");
	arg = replace_string(arg, "g", "G");
	arg = replace_string(arg, "h", "H");
	arg = replace_string(arg, "i", "I");
	arg = replace_string(arg, "j", "J");
	arg = replace_string(arg, "k", "K");
	arg = replace_string(arg, "l", "L");
	arg = replace_string(arg, "m", "M");
	arg = replace_string(arg, "n", "N");
	arg = replace_string(arg, "o", "O");
	arg = replace_string(arg, "p", "P");
	arg = replace_string(arg, "q", "Q");
	arg = replace_string(arg, "r", "R");
	arg = replace_string(arg, "s", "S");
	arg = replace_string(arg, "t", "T");
	arg = replace_string(arg, "u", "U");
	arg = replace_string(arg, "v", "V");
	arg = replace_string(arg, "w", "W");
	arg = replace_string(arg, "x", "X");
	arg = replace_string(arg, "y", "Y");
	arg = replace_string(arg, "z", "Z");
	return arg;
}
// 国家代码和中文国家名的变换
string codetoteam(string arg)
{
	int i;

	for (i = 0; i < sizeof(team); i++)
		if (code[i] == arg)
			return team[i];
	return "未知国名";
}
