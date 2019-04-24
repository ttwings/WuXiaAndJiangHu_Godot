// tea.c 孟婆茶

#include <ansi.h>
#include <command.h>
#include <login.h>
inherit ITEM;

int mpc_effect(object me);
void create()
{
	set_name(GRN "孟婆茶" NOR, ({GRN "mengpo tea" NOR, "cha", "tea"}));
	set_weight(1);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", GRN "这就是传说中著名的孟婆茶。每个鬼魂在投胎转世之前，都要喝上一碗孟婆茶，据说喝了这碗茶后，你在阳间的一切一切就都会忘得干干净净，就此与今世脱离了一切关系。\n");
		set("unit", "碗");
	}
	set("pour_type", "1");
	setup();
}

void init()
{
	add_action("do_drink", "drink");
	add_action("do_drink", "he");
}

int do_drink(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");
	//if a ghost
	if (!me->is_ghost())
	{
		write("你得先死了才能喝这碗茶......\n\n\n要不，先死一次？......\n");
		return 1;
	}
	message_vision("$N犹豫了一会儿，还是把一碗孟婆茶喝了下去。\n\n\n\n", me);
	remove_call_out("mpc_effect");
	call_out("mpc_effect", 5, me);
	return 1;
}
int mpc_effect(object me)
{
	string stroom;
	stroom = me->query("startroom");
	if (stroom[0..7] != "/d/death")
		if (me->query("eff_jing") < 5 && me->query("eff_qi") < 5)
			if (me->query("dietime") && time() - me->query("dietime") < 600)
			{
				me->set("eff_qi", (int)me->query("max_qi"));
				me->set("qi", (int)me->query("max_qi"));
				me->set("eff_jing", (int)me->query("max_jing"));
				me->set("jing", (int)me->query("max_jing"));
			}
	message_vision(BLU "$N觉得一阵头晕目眩，以前发生的事情似乎忘记了许多许多..........\n\n\n" NOR, me);
	tell_object(me, BLU "忘记吧...................\n\n\n\n" NOR);
	destruct(this_object());
	return 1;
}
