// head.c -脑袋
#include <ansi.h>
inherit ITEM;
int decayed;

void create()
{
	set_name(RED "头颅" NOR, ({"head"}));
	set_weight(300);
	set("unit", "颗");
	set("value", 0);
	decayed = 0;
	set("long", RED "一颗鲜血淋淋的首级，须发散乱，余血正缓缓渗出。\n" NOR);
	if (clonep(this_object()))
		call_out("decay", 300, 1);
}

int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }
int is_container() { return 1; }

string short() { return name() + "(" + capitalize(query("id")) + ")"; }

void decay(int phase)
{
	decayed = phase;
	if (query("shihui"))
	{
		phase = 0;
		decayed = 0;
		delete ("shihui");
		call_out("decay", 600, 1);
	}
	switch (phase)
	{
	case 1:
		say(query("name") + "开始腐烂了，发出一股难闻的恶臭。\n");
		set_name("腐烂的头颅", ({"decomposite head"}));
		set("long", "这颗头颅显然已经腐烂了一段时间了，一股恶臭夹杂血腥的味道。\n");
		call_out("decay", 120, phase + 1);
		break;
	case 2:
		say(query("name") + "被风吹乾了，变成一颗骷髅头。\n");
		set_name("白惨惨的骷髅头", ({"head bone"}));
		set("long", "这颗骷髅头已经放躺在这里有些时候了。\n");
		call_out("decay", 60, phase + 1);
		break;
	case 3:
		say("一阵风吹过，把" + query("name") + "化成骨灰吹散了。\n");
		if (environment())
		{
			object *inv;
			int i;

			inv = all_inventory(this_object());
			for (i = 0; i < sizeof(inv); i++)
				inv[i]->move(environment());
		}
		destruct(this_object());
		break;
	}
}
