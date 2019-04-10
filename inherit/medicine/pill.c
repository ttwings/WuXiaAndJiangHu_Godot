// pill.c

inherit COMBINED_ITEM;

void init()
{
	add_action("do_eat", "eat");
	add_action("do_pour", "pour");
}

int do_eat(string arg)
{
	string what = query("cure");
	int howmuch = query("amount");

	if (!id(arg))
		return notify_fail("你想吃什么？\n");

	if ((int)this_player()->query("eff_qi") == 
	    (int)this_player()->query("max_qi"))
		return notify_fail("你现在不需要用" + this_object()->name() + "。\n");
	else {
		this_player()->receive_curing("qi", 50);
		message_vision("$N吃下一包金创药，气色看起来好多了。\n", this_player());
		destruct(this_object());
		return 1;
	}
}

int do_pour(string arg)
{
	string me, what;
	object ob;
	function f;

	if( !arg || sscanf(arg, "%s in %s", me, what)!=2 || !id(me) )
		return notify_fail("指令格式: pour <药粉> in <物品>\n");
	ob = present(what, this_player());
	if( !ob ) return notify_fail("你身上没有 " + what + " 这样东西。\n");
	if( !what->query("pourable") )
	{
		write(this_object()->name() + "似乎不能掺进水酒里的。\n");
		return 1;
	}
	if( !ob->query("liquid/remaining") )
	{
		write(ob->name() + "里什么也没有，先装些水酒才能溶化掉"+this_object()->name()+"。\n");
		return 1;
	}
// We let call other to call the "master copy" of the object in case the
// powder object got destructed after used up.
	f = (: call_other, base_name(this_object()), "effect_in_liquid" :);
	ob->set("liquid/drink_func", bind(f, ob));
	message_vision("$N将一" +query("unit") + name() + "扔进" + ob->name() + "，摇晃了几下。\n", this_player());
	destruct(this_object());
	return 1;
}

