// dog.c
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
	set_name("野狗", ({"dog"}));
	set("race", "走畜");
	set("age", 3);
	set("long", "一只浑身脏兮兮的野狗。\n");

	set("str", 32);
	set("dex", 36);

	set("chat_chance", 6);
	set("chat_msg", ({(
						  : this_object(), "random_move"
						  :),
					  "野狗用鼻子闻了闻你的脚。\n",
					  "野狗在你的脚边挨挨擦擦的，想讨东西吃。\n",
					  "野狗对著你摇了摇尾巴。\n",
					  "野狗用後腿抓了抓自己的耳朵。\n"}));

	set_temp("apply/attack", 10);
	set_temp("apply/armor", 3);

	setup();
}

int accept_object(object who, object ob)
{
	if (ob->id("bone"))
	{
		set_leader(who);
		message("vision", name() + "高兴地汪汪叫了起来。\n", environment());
		return 1;
	}
}
