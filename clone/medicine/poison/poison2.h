// poison2.h
// Last Modified by winder on Feb. 28 2001

int do_tu(string arg)
{
	string what, my;
	object ob, me = this_player();
	int i;
	i = (me->query_skill("poison") / 10) + 3 + (me->query_skill("five-poison") / 10) + 3;

	if (!arg || sscanf(arg, "%s on %s", my, what) != 2 || !id(my))
		return notify_fail("命令格式: tu <药> on <武器>。\n");

	ob = present(what, me);
	if (!ob)
		return notify_fail("你身上没有" + what + "这样东西。\n");
	if (!ob->query("weapon_prop"))
		return notify_fail("只能涂在武器上。\n");

	ob->set("poisoned", query("pour_type"));
	ob->set("poison_number", ob->query("poison_number") + i);

	ob->set_temp("apply/long", ({ob->query("long") + "但看上去" + query("drug_color") + "，好象是被喂了剧毒。\n"}));
	message_vision("$N背过身去，将" + query("name") + "涂在$n上。\n", me, ob);
	me->start_busy(2);
	add_amount(-1);
	return 1;
}

void destruct(object ob)
{
	message_vision("$N慢慢地燃烧完了。\n", ob);
	ob->add_amount(-1);
	return;
}
