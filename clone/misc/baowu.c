// Last modified by winder 2003.9.2
// /clone/misc/baowu.c

#include <ansi.h>
inherit ITEM;
string *titles = ({
	HIW "夜明珠" NOR,
	HIG "岫岩玉" NOR,
	HIY "和田玉" NOR,
	HIG "巴林玉" NOR,
	HIR "昌化鸡血石" NOR,
	HIC "青田石" NOR,
	HIY "田黄石" NOR,
	YEL "寿山石" NOR,
	HIW "橄榄石" NOR,
	BLK "黑曜石" NOR,
	HIW "白宝石" NOR,
	HIR "红宝石" NOR,
	HIG "绿宝石" NOR,
	HIG "绿松石" NOR,
	HIG "孔雀石" NOR,
	HIC "青金石" NOR,
	YEL "金" HIG "绿宝石" NOR,
	HIG "绿晶" NOR,
	HIM "紫水晶" NOR,
	HIY "软玉" NOR,
	HIY "琥珀" NOR,
	HIB "蓝宝石" NOR,
	HIW "钻石" NOR,
	HIG "碧玉" NOR,
	HIW "水晶" NOR,
	GRN "翡翠" NOR,
	HIM "玛瑙" NOR,
	GRN "猫儿眼" NOR,
	HIR "珊瑚" NOR,
	HIG "手镯" NOR,
	WHT "玉杯" NOR,
	WHT "玉莲花" NOR,
	CYN "玉带" NOR,
	CYN "玉发簪" NOR,
	CYN "玉戒指" NOR,
	HIC "玉佩" NOR,
	WHT "玉如意" NOR,
	CYN "玉手镯" NOR,
	WHT "玉盏" NOR,
	WHT "珍珠" NOR,
	HIG "祖母绿" NOR,
	HIG "玉西瓜" NOR,
});

void create()
{
	int i = random(sizeof(titles));
	set_name(titles[i], ({"bao wu"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "你挖出来的宝物，不知道有什么作用。\n");
		set("unit", "个");
		set("no_sell", 1);
		set("no_put", 1);
		//		set("value", 50);
		set("no_beg", 1);
		set("no_steal", 1);
	}
}
