// sword_book4.c

inherit ITEM;

void create()
{
	set_name("嵩山剑谱", ({"sword book", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long",
"当年五岳剑派与魔教十长老两度会战华山，五派好手死伤殆尽，五派
剑派的许多精世绝招，随五派高手而逝。左冷禅会集本派残存的耆宿，
将各人所记得的剑招，不论精粗，尽数录了下来，汇成一部剑谱。这
数十年来，他去芜存菁，将本派剑法中种种不够狠辣的招数，不够堂
皇的姿式，一一修改，使得本派剑法‘内八路，外九路’、一十七路
长短、快慢各路剑法完美无缺。
这本小册子就是他整理的嵩山剑谱。\n");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name"        : "songshan-sword",
			"exp_required": 10000,
			"jing_cost"   : 20,
			"difficulty"  : 20,
			"max_skill"   : 120
		]) );
	}
}
