// lamb.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
	set_name("黄羊", ({"lamb", "yang", "huang yang"}));
	set("race", "走畜");
	set("age", 11);
	set("long", "一只野黄羊，正低头认真地吃着草。\n");

	set("str", 26);
	set("cor", 30);

	set("combat_exp", 800);

	set("chat_chance", 6);
	set("chat_msg", ({"黄羊咩~~咩~~的叫了几声。\n"}));

	set_temp("apply/attack", 15);
	set_temp("apply/damage", 6);
	set_temp("apply/armor", 2);

	setup();
}

void die()
{
	object ob;
	message_vision("$N倒在地上，咩~~的一声就死了！\n", this_object());
	ob = new (__DIR__ "obj/yangrou");
	ob->move(environment(this_object()));
	ob = new (__DIR__ "obj/yangpi");
	ob->move(environment(this_object()));
	destruct(this_object());
}
