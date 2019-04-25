// male-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

string *clothname = ({
	"粗布衣",
	HIB "青衫" NOR,
	BBLK "黑色劲装" NOR,
	HIC "短打劲装" NOR,
	HIM "紫蟒袍" NOR,
	BLU "蓝马褂" NOR,
	HIY "明黄锦袍" NOR,
	HIB "天蓝长袍" NOR,
});
string *clothid = ({
	"rough cloth",
	"blue cloth",
	"black cloth",
	"bunt cloth",
	"purple cloth",
	"blue cloth",
	"yellow cloth",
	"celeste cloth",
});
string *clothlong = ({
	"这是一件很普通的粗布衣。\n",
	"这是一件很普通的粗布青衫。\n",
	"这是一件很笔挺的黑色劲装。\n",
	"这是一件很利索的短打劲装。\n",
	"这是一件很重的紫蟒袍。\n",
	"这是一件很重的蓝马褂。\n",
	"这是一件明黄锦袍。\n",
	"这是一件天蓝长袍。\n",
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
		// 	set("long", clothlong[i]);
		set("unit", "件");
		set("value", 0);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 3);
	}
	setup();
}
