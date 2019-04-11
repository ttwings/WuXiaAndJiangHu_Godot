#include <ansi.h>
inherit ITEM;
void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
	remove_call_out("decay");
	call_out("decay", 180);
}

void create()
{
	set_name("怪蛇之胆", ({"guai shedan", "dan", "shedan"}));
	set("unit", "只");
	set("long", "这是怪蛇的胆，圆圆的，呈深紫色，腥臭无比，不知有没有毒。\n");
	set("value", 1000);
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int force_limit, neili_limit,food_limit,water_limit;
	object me=this_player();

	force_limit = me->query_skill("force")*10;
	neili_limit = me->query("max_neili");
	food_limit = me->max_food_capacity();
	water_limit = me->max_water_capacity();

	if (!id(arg)) return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢喝，小心别噎着了。\n");

	if (( me->query("food")>=food_limit)||(me->query("water")>=water_limit))
		return notify_fail("你已经吃饱了，再也吃不下任何一点东西。\n");
	if ( neili_limit <= force_limit  )
	{
		me->add("max_neili", 2);
		me->add("neili", 5);
	}
	message_vision(HIY "$N吃下一颗蛇胆，只觉汁液腥极苦极，难吃无比，只想喷了出去。\n" NOR, me);
	me->add("food",50);
	me->add("water",50);
	destruct(this_object());
	return 1;
}

void decay()
{
	object where = environment(this_object());
	if ( interactive(where) )
		message("vision", GRN"蛇胆啪的一声破了，弄得你一身甚是腥臭。\n"NOR, 
			where); 
	else
		message("vision", MAG"蛇胆啪的一声破了，汁液流了一地。\n"NOR,
			where);
	destruct(this_object());
}
