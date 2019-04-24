// yijinjing.c

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(YEL "易筋经" NOR, ({"yijinjing"}));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "卷");
		set("long", "易筋经\n这是一卷古朴丝织经轴，看来很有年月了，上面文字坚深，不知你识\n也不识。易筋经是少林镇寺之宝 ，一直妥藏此处。\n");
		set("value", 10);
		set("material", "silk");
		set("skill", ([
								 "name":"yijinjing", // name of the skill
						 "exp_required":100000,		 // minimum combat experience required
							"jing_cost":10,			 // jing cost every time study this
						   "difficulty":30,			 // the base int to learn this skill
							"max_skill":200			 // the maximum level you can learn
		]));
	}
}
