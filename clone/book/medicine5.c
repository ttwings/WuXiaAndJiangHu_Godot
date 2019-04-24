// medicine5.c
// Last Modified by Winder on May. 29 2001

#include <ansi.h>
inherit ITEM;

void init()
{
	add_action("do_kan", "watch");
	add_action("do_kan", "kan");
}

void create()
{
	set_name(HIY "孙思邈千金方" NOR, ({"qianjin fang", "qianjingfang", "fang"}));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long",
			"\n这是一本『孙思邈千金方』，你可以好好看看(watch)。\n");
		set("value", 50);
		set("material", "paper");
	}
	setup();
}
int do_kan(string arg)
{
	object me = this_player();
	int lvl = me->query_skill("medicine", 1);

	if (!id(arg))
		return notify_fail("你要看什么？\n");
	if (!present(this_object(), this_player()))
		return 0;

	if (me->is_busy())
	{
		write("你现在正忙着呢。\n");
		return 1;
	}
	if (!me->query_skill("medicine", 1))
	{
		write("这是医书。你一窍不通，有啥好看的？\n");
		return 1;
	}
	if (!me->query_skill("literate", 1))
	{
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}
	write(HIR "                   【黄帝内经】\n");
	write(YEL " 〖江湖珍药秘方〗\n\n");
	write(HIG "金创药           川贝、生地、血竭\n");
	if (lvl >= 10)
		write("养精丹           川贝，枸枳子，菊梗\n");
	if (lvl >= 20)
		write("清心散           巴豆，荷叶，菊梗\n");
	if (lvl >= 30)
		write("白虎夺命丹       虎骨、天山雪莲、茯苓、白芷\n");
	if (lvl >= 40)
		write("白云熊胆丸       熊胆、白芷、柴胡、没药\n");
	if (lvl >= 50)
		write("天香断续膏       白薇、没药、灵芝、灵脂\n");
	if (lvl >= 60)
		write("小还丹           桑叶、当归、天山雪莲、藿香\n");
	if (lvl >= 70)
		write("百草丹           穿山甲、甘草、藏红花\n");
	if (lvl >= 80)
		write("延年聚精丹       天山雪莲，藏红花，荷叶\n");
	if (lvl >= 90)
		write("回阳五龙散       何首乌、穿山甲、茯苓、防风、菊梗\n");
	if (lvl >= 100)
		write("黑石玉洞丹       豹胎、防风、熊胆、天山雪莲\n");
	if (lvl >= 110)
		write("九转结气丸       牛黄、蝉蜕、枸枳子、荷叶\n");
	if (lvl >= 120)
		write("九花玉露丸       天山雪莲、甘草、桃花瓣、荷叶\n");
	if (lvl >= 130)
		write("玉露清新散       荷叶、当归、白薇、金银花\n");
	if (lvl >= 140)
		write("三黄宝蜡丸       麻黄、藤黄、雄黄、灵脂\n");
	if (lvl >= 150)
		write("大还丹           荷叶、当归、天山雪莲、藿香\n");
	if (lvl >= 160)
		write("续命八丸         人参、茯苓、灵芝、鹿茸、何首乌、灵脂、熊胆、三七、麝香\n");
	write("\n" NOR);
	return 1;
}
