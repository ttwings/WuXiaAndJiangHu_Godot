// jingcaiban.c

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

// 全局变量，即储存玩家押注的所有数据
mapping *all_biao;
// 全局变量，此处为目前数量
int num;
// 全局变量，此处为最终结杲
int jieguo;

// 以下四行为函数声明
int do_read(string);
int do_post(string);
int do_ya(string);
void enough_rest();

void create()
{
	set_name(HIY "世界杯亚洲Ｂ组十强赛竞猜版" NOR, ({"board", "ban"}));
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
	return DATA_DIR + "board/jingcai_b";
}

// 玩家下注
int do_ya(string arg)
{
	int i, j;
	object me, ob;
	mapping biao;

	me = this_player();
	// 表示停止下注，由巫师在do_post()函数里加入
	if (query("end_ya"))
		return notify_fail("截止时间已过，下回赶早。\n");
	// 防止多人同意押注产生意外
	if (query_temp("busy"))
		return notify_fail("稍候........\n");
	// 调玩家身上的参数
	if (me->query("jingcai"))
		return notify_fail("每人只能押一次！\n");
	// 分析玩家指令
	if (!arg || sscanf(arg, "%d %d", i, j) != 2)
		return notify_fail("命令格式：ya <分数> <多少两黄金>\n");
	// 排除一些不可能的押注可能
	if (i < 10 || i > 22)
		return notify_fail("不可能吧？你是不是想白送钱？\n");
	// 至少1gold
	if (j < 1)
		return notify_fail("你想白赚啊？\n");
	// 上限，可以自由调整
	if (j > 1000)
		return notify_fail("押得太多，请少于1000。\n");
	if ((int)j > me->query("balance") / 10000)
		// 钱庄的存款不够押的钱
		return notify_fail("这里不收现金！到钱庄存够了钱再来！”\n");
	message_vision("$N想了半天大声喊道：“我认为中国队能拿到 " + i + " 分！押 " + j + " 两黄金！”\n", me);
	me->add("balance", -j * 10000);
	tell_object(me, "钱庄已经扣除了你押下的" + j + "两黄金。请等候结果吧！\n");
	// 在玩家身上设下押的结果
	me->set("jingcai/win", i);
	// 押的黄金数
	me->set("jingcai/gold", j);
	// 这是一个记录该玩家押注数据的映射
	biao = ([
				"id":me->query("id"),
			"name":me->query("name"),
			 "win":i,
			"gold":j,
	]);
	if (!pointerp(all_biao))
		all_biao = ({biao});
	else
		all_biao += ({biao});
	//储存进这个文件对应的.o文件里
	save();
	remove_call_out("enough_rest");
	//1秒后取消busy
	call_out("enough_rest", 1);
	return 1;
}

// 巫师专用，更新情况
int do_post(string arg)
{
	int i;
	object me = this_player();

	if (!wizardp(me))
		return 0;
	if (!arg)
		return notify_fail("你要更新什么？\n");
	// 只加数字表示更新即时情况
	if (sscanf(arg, "%d", i) == 1)
	{
		// num是全程变量
		if (i > num)
		{
			message("channel:sys", HIM "【谣言】" HIR "某人：听说竞猜版中国队当前得分由 " + num + " 更新为 " + i + " 分！\n" NOR, users());
			// 更新
			num = i;
			save();
			return 1;
		}
		else
			return notify_fail("中国队得分会越挣越少吗？\n");
	}
	// 加-last参数，表示更新最终结果
	if (sscanf(arg, "-last %d", i) == 1)
	{
		if (i >= num)
		{
			message("channel:sys", HIM "【谣言】" HIR "某人：听说竞猜版最终结果公布，是 " + jieguo + " 分！押对的快去兑奖啊！\n" NOR, users());
			// 更新
			jieguo = i;
			save();
			return 1;
		}
		else
			return notify_fail("中国队得分会越挣越少吗？\n");
	}
	if (arg == "end")
	{
		// 停止押注
		set("end_ya", 1);
		message("channel:sys", HIM "【谣言】" HIR "某人：竞猜版开始停止下注，请关注比赛结果！\n" NOR, users());
		save();
		return 1;
	}
	return notify_fail("你要的中国队得分是多少？\n");
}
// 玩家查看
int do_read(string arg)
{
	int i, j, k;
	object me;
	string name, str, str1, str2;
	mapping biao;

	me = this_player();
	if (arg == "rules")
	{
		//这个规则根据每次巫师设计的定
		write("
    世界杯外围赛亚洲十强赛Ｂ组，中国队能拿几分？欢迎在此押注：
押注者以黄金为单位，最高可押一千黄金，最少也要押一两黄金。现金
不收，必须先存进钱庄。押赌后钱庄直接扣钱。押赌时间到十月十二日
截止。押小于十三分的数字一赔十二，押十三至二十之间的数字是一赔
六，二十以上的数字是一赔十五，比赛结束，押中者按倍数返还黄金，
不中者则罢。想好了后就 "HIY"ya <分数> <多少两黄金> "NOR"。
    当然每个ID只能押一次，押过不许后悔！\n\n");
		write("开奖后请使用duixian指令，你的奖金将自动进入你帐户。\n");
		return 1;
	}
	if (arg == "ban")
	{
		//有了分数的参数
		if (num)
			write("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n" HIG "本届十强赛，中国已获 " HIY + num + HIG " 分！");
		write(!jieguo ? RED "还在投注中！" : HIR "开始兑奖(duijiang)了！");
		//表示还没有数据
		if (!pointerp(all_biao) || !sizeof(all_biao))
		{
			write(NOR "\n还没有人开始投注。\n");
			return 1;
		}
		write(NOR "\n已有 " + sizeof(all_biao) + " 个玩家投注：\n" HIY "玩家名　　　　预测分数  　押黄金数" HIG "｜" HIY "玩家名　　　　预测分数数　押黄金数\n" HIG "—————————————————┼—————————————————\n");
		str1 = HIM "已经兑过奖的玩家：                " HIG "｜\n" NOR;
		str2 = HIM "还未兑过奖的玩家：                " HIG "｜\n" HIC;
		j = 0;
		k = 0;
		// all_biao也是全局变量，看文件头
		for (i = 0; i < sizeof(all_biao); i++)
		{
			// 取出每个押注玩家的名字
			name = all_biao[i]["name"] + "(" + all_biao[i]["id"] + ")";
			// dui这个参数是在兑奖后加入的，这表示没兑奖的，加入str2
			if (!(int)all_biao[i]["dui"])
			{
				str2 += sprintf("%-18s    %-5d  %-5d%s", name, (int)all_biao[i]["win"], (int)all_biao[i]["gold"], j % 2 ? "\n" : HIG "｜" HIC, );
				// j和下面的k都是为了两个一行，分行用的j%2就是除2剩下的余数，为0就换行
				j++;
			}
			// 有dui参数的，记入str1
			else
			{
				str1 += sprintf("%-18s    %-5d  %-5d%s", name, (int)all_biao[i]["win"], (int)all_biao[i]["gold"], k % 2 ? "\n" : HIG "｜" HIC, );
				k++;
			}
		}
		/* 这里的str1与str2可以根据不同的情况表现不同的信息，比如在比赛中，可
以根据all_biao[i]["win"]是否大于num，即目前的分数数，判断哪些玩家还有
希望，哪些玩家已经被淘汰：str1="无获奖希望的玩家"：......  */
		//显示信息
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
int do_duijiang()
{
	int i, j;
	object ob, me = this_player();
	mapping biao, jingcai;

	// 没有jieguo就表示没有开始兑奖
	if (!jieguo)
		return notify_fail("还未到兑奖时间！\n");
	// 查找身上参数
	if (!jingcai = me->query("jingcai"))
		return notify_fail("你没有奖的，或者已经兑过奖了！\n");
	if (query_temp("busy"))
		return notify_fail("稍候........\n");
	set_temp("busy", 1);
	// 与结果相符，即中奖
	if (jingcai["win"] == jieguo)
	{
		// 1赔15
		if (jingcai["win"] > 22)
			i = jingcai["gold"] * 15;
		// 1赔6
		else if (jingcai["win"] > 14)
			i = jingcai["gold"] * 6;
		// 1赔12
		else
			i = jingcai["gold"] * 12;
		// 这些都可以按照设定的规则来定
		write("你押 " + jingcai["win"] + " 分 " + jingcai["gold"] + " 两黄金，按规定得奖金 " + i + " 两黄金，已划入你的钱庄帐户！\n");
		message("channel:sys", HIM "【谣言】" HIR "某人：" + me->name() + "兑奖得到 " + chinese_number(i) + " 两黄金！\n" NOR, users());
		me->add("balance", i * 10000);
	}
	// 没有对的也来个空门奖吧
	else
	{
		ob = new ("/clone/food/jitui");
		ob->move(me);
		write("你没押对，但发一个安慰奖，送你一根鸡腿吧！\n");
		message_vision(HIY "竞猜表上头突然金光一闪，“扑”地掉下一根油光光的鸡腿，正好掉进$N的手中。\n" NOR, me);
	}
	for (j = 0; j < sizeof(all_biao); j++)
	{
		// 表示此人兑过奖了
		if (all_biao[j]["id"] == me->query("id"))
			all_biao[j]["dui"] = 1;
	}
	// 存盘
	save();
	// 身上参数取消，以防重复兑奖
	me->delete ("jingcai");
	remove_call_out("enough_rest");
	call_out("enough_rest", 1);
	return 1;
}
