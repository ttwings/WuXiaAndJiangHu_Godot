# jitui.c 鸡腿

#include <weapon.h>

# inherit HAMMER;
# inherit F_FOOD;
extends Food

func create():
	set_name("烤鸡腿", "jitui");
	set_weight(350);
	set_attr("long", "一枝烤得香喷喷的鸡腿。\n");
	set_attr("unit", "根");
	set_attr("value", 80);
	set_attr("food_remaining", 4);
	set_attr("food_supply", 15);
	set_attr("wield_msg", "$N抓起一根$n，握在手中当武器。\n");
	set_attr("material", "bone");
	init_hammer(1);
	setup();

func finish_eat():
	if( !query("weapon_prop") ) :
		return 0;
	set_name("啃得精光的鸡腿骨头", "bone");
	set_weight(150);
	set_attr("long", "一根啃得精光的鸡腿骨头。\n");
	return 1;

