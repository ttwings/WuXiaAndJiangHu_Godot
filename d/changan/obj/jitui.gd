# jitui.c 鸡腿

#include <weapon.h>

# inherit HAMMER;
# inherit F_FOOD;
extends Food

func create():
	set_name("烤鸡腿", "jitui");
	set_weight(350);
	set("long", "一枝烤得香喷喷的鸡腿。\n");
	set("unit", "根");
	set("value", 80);
	set("food_remaining", 4);
	set("food_supply", 15);
	set("wield_msg", "$N抓起一根$n，握在手中当武器。\n");
	set("material", "bone");
	init_hammer(1);
	setup();

func finish_eat():
	if( !query("weapon_prop") ) :
		return 0;
	set_name("啃得精光的鸡腿骨头", "bone");
	set_weight(150);
	set("long", "一根啃得精光的鸡腿骨头。\n");
	return 1;

