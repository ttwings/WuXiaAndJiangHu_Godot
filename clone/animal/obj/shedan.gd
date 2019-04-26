# poison: shedan.c
# Last Modified by winder on Aug. 1 2002

# inherit PILL;
#include <ansi.h>
var cure_ob;

func create():

	set_name("毒蛇胆", ["shedan", "dan"]);
	set("unit", "粒");
	set("long", "这是一只绿莹莹的毒蛇胆。\n");
	set("value", 200);
	set("medicine", 1);
	setup();


func _init():

	add_action("do_pour", "drop");

func cure_ob(me):

	message_vision("$N吃下一粒" + name() + "。\n", me);
	if (me.query_condition("snake_poison") > 7):
	
		me.apply_condition("snake_poison", me.query_condition("snake_poison") - 5);
	

	destruct(this_object());
	return 1;

func effect_in_liquid(ob):

	if (ob.query("liquid/type") == "alcohol"):
	
		this_player().add("qi", 10 * ob.query("liquid/drunk_apply"));
		message_vision(MAG +  "$N感到一股真气缓缓注入丹田，混身上下暖哄哄的。\n" + NOR, this_player());
	
	return 0;

