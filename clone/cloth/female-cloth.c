// female-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

string *clothname = ({
	HIM "粉红绸衫" NOR,
	HIW "白绸衫" NOR,
	HIG "湖绿长裙" NOR,
	HIY "鹅黄夹袄" NOR,
	HIB "青衫小袖" NOR,
	HIC "天青小袂" NOR,
	HIR "散花衣" NOR,
	MAG "紫纱小夹衫" NOR,
});
string *clothid = ({
	"pink cloth",
	"white cloth",
	"green skirt",
	"yellow coat",
	"blue shan",
	"qing mei",
	"flower cloth",
	"purple jiashan",
});
string *clothlong = ({
	"这件粉红色的绸衫上面绣着几只黄鹊，闻起来还有一股淡香。\n",
	"这是一件轻盈飘动的白绸轻衫。\n",
	"这是一件清新可人的湖绿长裙。\n",
	"这是一件女孩喜欢的鹅黄夹袄。\n",
	"这是一件小巧玲珑的青衫小袖。\n",
	"这是一件用金线绣着几朵梅花的天青小袂。\n",
	"这件红色的散花衣轻轻爽爽，很是飘逸。\n",
	"这是一件紫纱小夹衫。\n",
});

void create()
{
	int i = random(sizeof(clothname));
	set_name(clothname[i], ({clothid[i], "cloth"}));
	set_weight(1000);
	set("long", clothlong[i]);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		//  set("long", clothlong[i]);
		set("unit", "件");
		set("value", 0);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 3);
		set("female_only", 1);
	}
	setup();
}
