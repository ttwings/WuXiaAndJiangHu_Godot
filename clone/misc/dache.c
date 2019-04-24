// Last Modified by Winder on May. 15 2001
// /clone/misc/dache.c
// sign/value必须是整百的数

inherit ITEM;
#include <ansi.h>
int do_go(string);
int look_sign();
mapping *sign = ({
	(["name":"黑木崖",
		"target":"黑木崖乱石坡",
			"id":"heimuya",
		   "out":"heimuya",
		  "file":"/d/heimuya/road1",
		 "value":200,
		  "time":10]),
	(["name":"铁掌峰",
		"target":"铁掌峰山脚下",
			"id":"tiezhang",
		   "out":"tiezhang",
		  "file":"/d/tiezhang/shanjiao",
		 "value":200,
		  "time":10]),
	(["name":"梅庄",
		"target":"梅庄大门",
			"id":"meizhuang",
		   "out":"meizhuang",
		  "file":"/d/meizhuang/gate",
		 "value":200,
		  "time":10]),
	(["name":"太湖",
		"target":"太湖湖畔",
			"id":"taihu",
		   "out":"yanziwu",
		  "file":"/d/yanziwu/hupan",
		 "value":100,
		  "time":10]),
	(["name":"无量山",
		"target":"无量山坳",
			"id":"wuliang",
		   "out":"wuliang",
		  "file":"/d/wuliang/shanlu6",
		 "value":300,
		  "time":10]),
	(["name":"天山",
		"target":"天山山路",
			"id":"tianshan",
		   "out":"xiyu",
		  "file":"/d/xingxiu/tianroad2",
		 "value":300,
		  "time":10]),
	(["name":"凌霄城",
		"target":"凌霄城石崖",
			"id":"lingxiao",
		   "out":"lingxiao",
		  "file":"/d/lingxiao/shiya",
		 "value":200,
		  "time":10]),
	(["name":"雪山寺",
		"target":"雪山寺山门",
			"id":"xueshan",
		   "out":"xueshansi",
		  "file":"/d/xueshan/shanmen",
		 "value":300,
		  "time":10]),
	(["name":"光明顶",
		"target":"光明顶山门",
			"id":"mingjiao",
		   "out":"mingjiao",
		  "file":"/d/mingjiao/shanmen",
		 "value":300,
		  "time":10]),
	(["name":"中条山",
		"target":"中条山脚下",
			"id":"zhongtiao",
		   "out":"zhongtiao",
		  "file":"/d/huashan/jzroad3",
		 "value":100,
		  "time":10]),
	(["name":"长白山",
		"target":"长白山白河",
			"id":"changbai",
		   "out":"changbai",
		  "file":"/d/guanwai/baihe",
		 "value":300,
		  "time":10]),
	(["name":"终南山",
		"target":"终南山脚下",
			"id":"zhongnan",
		   "out":"zhongnan",
		  "file":"/d/quanzhen/shanjiao",
		 "value":100,
		  "time":10]),
	(["name":"恒山",
		"target":"恒山金龙峡",
			"id":"hengshan",
		   "out":"hengshan",
		  "file":"/d/hengshan/jinlongxia",
		 "value":100,
		  "time":10]),
	(["name":"衡山",
		"target":"衡山棂星门",
			"id":"henshan",
		   "out":"henshan",
		  "file":"/d/henshan/lingxingmen",
		 "value":100,
		  "time":10]),
	(["name":"华山",
		"target":"华山莎萝坪",
			"id":"huashan",
		   "out":"huashan",
		  "file":"/d/huashan/shaluo",
		 "value":100,
		  "time":10]),
	(["name":"泰山",
		"target":"泰山岱宗坊",
			"id":"taishan",
		   "out":"taishan",
		  "file":"/d/taishan/daizong",
		 "value":100,
		  "time":10]),
	(["name":"嵩山",
		"target":"嵩山太室阙",
			"id":"songshan",
		   "out":"songshan",
		  "file":"/d/songshan/taishique",
		 "value":100,
		  "time":10]),
	(["name":"青城山",
		"target":"青城建福宫",
			"id":"qingcheng",
		   "out":"qingcheng",
		  "file":"/d/qingcheng/jianfugong",
		 "value":200,
		  "time":10]),
	(["name":"昆仑山",
		"target":"昆仑派山门",
			"id":"kunlun",
		   "out":"kunlun",
		  "file":"/d/kunlun/shanmen",
		 "value":300,
		  "time":10]),
	(["name":"峨眉山",
		"target":"峨眉报国寺",
			"id":"emei",
		   "out":"emei",
		  "file":"/d/emei/bgs",
		 "value":200,
		  "time":10]),
	(["name":"武当山",
		"target":"武当解剑岩",
			"id":"wudang",
		   "out":"wudang",
		  "file":"/d/wudang/jiejianyan",
		 "value":100,
		  "time":10]),
	(["name":"南少林寺",
		"target":"南少林迎客亭",
			"id":"nanshaolin",
		   "out":"nanshaolin",
		  "file":"/d/nanshaolin/ting",
		 "value":100,
		  "time":10]),
	(["name":"少林寺",
		"target":"少林寺山门",
			"id":"shaolin",
		   "out":"shaolin",
		  "file":"/d/shaolin/shanmen",
		 "value":100,
		  "time":10]),
	(["name":"扬州",
		"target":"扬州中央广场",
			"id":"yangzhou",
		   "out":"yangzhouw",
		  "file":"/d/city/shilijie4",
		 "value":100,
		  "time":10]),
});
void setup()
{
}
void init()
{
	add_action("do_go", "qu");
	add_action("look_sign", "kan");
}
void create()
{
	set_name("大车", ({"da che", "che", "dache"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long","这是一辆半新不旧的大车，车上坐着一个半老不老的车夫。
你可以仔细看看(kan)车上挂着的牌子，那就是你乘上大车，\n可以去(qu)的地方。\n");
		set("unit", "辆");
		set("no_fight",1);
		set("no_get", 1);
		set("no_steal", 1);
		set("no_beg", 1);
		set("no_drop", 1);
		set("no_put", 1);
	}
	setup();
}
int look_sign()
{
	string adjstr1, adjstr2, str = "由此去(qu)到下列地方：\n  目的地        地名          价码\n================================================\n";
	int adj1, adj2, i = sizeof(sign);
	while (i--)
	{
		if (environment(this_player())->query("outdoors") != sign[i]["out"])
		{
			str += " " + sign[i]["target"];
			adjstr1 = sign[i]["target"];
			adj1 = 18 - strlen(adjstr1);
			while (adj1--)
				str += " ";
			str += "(" HIY + sign[i]["id"] + NOR ") ";
			adjstr2 = "(" + sign[i]["id"] + ") ";
			adj2 = 18 - strlen(adjstr2);
			while (adj2--)
				str += " ";
			str += "：" CYN + MONEY_D->price_str(sign[i]["value"]) + NOR "\n";
		}
	}
	write(str + "------------------------------------------------\n");
	return 1;
}

void do_move(object ob, int i)
{
	ob->delete_temp("block_msg/all");
	ob->delete_temp("noliving");
	write("终于到" + sign[i]["name"] + "了。\n\n");
	ob->move(sign[i]["file"]);
	tell_room(environment(ob), "\n忽然远处有一辆大车飞驰而来，快到你身边时就慢慢停了下来。\n" + ob->name() + "从大车上走了下来。\n", ({ob}));
}

int do_go(string arg)
{
	object *inv, ob = this_player();
	int j, i = sizeof(sign);

	if (!arg)
		return notify_fail("你要去哪里？先看看(kan)再走吧！\n");
	if (ob->is_busy() || ob->is_fighting())
		return notify_fail("你正忙着呢！\n");

	inv = all_inventory(ob);
	for (j = 0; j < sizeof(inv); j++)
	{
		if (inv[j]->is_character())
		{
			write("大车里里位置有限，挤不下那么多人。\n");
			return 1;
		}
	}
	if (ob->query_temp("LAST_PKER_TIME") &&
		time() - ob->query_temp("LAST_PKER_TIME") < 7200 && !wizardp(ob))
		return notify_fail("杀了人，可不能做缩头乌龟！\n");

	while (i--)
	{
		if (arg == sign[i]["id"])
		{
			if (environment(ob)->query("outdoors") == sign[i]["out"])
				return notify_fail("车夫笑骂道：“你糊涂啦，去什么去！你不是已经在" HIR + sign[i]["name"] + NOR "了吗？！”\n");
			switch (MONEY_D->player_pay(ob, sign[i]["value"]))
			{
			case 0:
				return notify_fail("穷光蛋，一边呆着去！\n");
			case 2:
				return notify_fail("有零钱吗？\n");
			}
			message_vision("\n$N登上了大车，一扬手丢了" + chinese_number(sign[i]["value"] / 100) + "两银子给车夫，说了声：“去" + sign[i]["name"] + "。”\n$N说完掀开帘子，一哈腰钻进车去。\n\n", ob);
			write(HIC"大车内"NOR" -
    车里干干净净，放了两张舒服的大椅子。窗帘半拉了下来，阳光从
缝隙中透进来，窗外看不尽的景致，有的壮观，有的也无趣。于是昏昏
沉沉地睡去，也不管路上走了多久。门外挂了一串风铃，叮呤呤响着。
车夫坐在前面，一路赶着马，一路得意地哼着什么小调。\n");
			ob->set_temp("noliving/journey", 1);
			ob->set_temp("block_msg/all", 1);
			ob->move("/clone/misc/dachenei");
			call_out("do_move", sign[i]["time"]+random(10), ob, i);
			return 1;
		}
	}
	return notify_fail("你要去哪里？\n");
}
/*
少林寺山门   (shaolin)    /d/shaolin/shanmen
武当解剑岩   (wudang)     /d/wudang/jiejianyan
峨眉报国寺   (emei)       /d/emei/bgs
昆仑派山门   (kunlun)     /d/kunlun/shanmen
青城建福宫   (qingcheng)  /d/qingcheng/jianfugong
嵩山太室阙   (songshan)   /d/songshan/taishique
泰山岱宗坊   (taishan)    /d/taishan/daizong
华山莎萝坪   (huashan)    /d/huashan/shaluo
衡山棂星门   (henshan)    /d/henshan/lingxingmen
恒山金龙峡   (hengshan)   /d/hengshan/jinlongxia
终南山脚下   (zhongnan)   /d/quanzhen/shanjiao
中条山脚下   (zhongtiao)  /d/huashan/jzroad3
光明顶山门   (mingjiao)   /d/mingjiao/shanmen
雪山寺山门   (xueshansi)  /d/xueshan/shanmen
天山山路     (xiyu)       /d/xingxiu/tianroad2
无量山坳     (wuliang)    /d/wuliang/shanlu6
太湖湖畔     (yanziwu)    /d/yanziwu/hupan
梅庄大门     (meizhuang)  /d/meizhuang/gate
铁掌峰山脚下 (tiezhang)   /d/tiezhang/shanjiao
黑木崖乱石坡 (heimuya)    /d/heimuya/road1
*/
