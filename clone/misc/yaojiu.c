// yaojiu.c
#include <ansi.h>

inherit ITEM;
int do_pour(string arg);

void create()
{
	set_name("药臼", ({ "yao jiu", "jiu" }) );
	set("long",
		"这是一个药臼，是医士们用来炼制丹药的容器：\n"
		"put <药材>          将药材放入药臼中。\n"
		"fill                向药臼中添加清水。\n"
		"burn                点火折燃烧木柴。\n"
		"putout              灭火冷却药臼。\n"
//		"get <丹药>          取出丹药。\n"
	);
	set_weight(3000);
	set_max_encumbrance(5000);
	set("unit", "个");
	set("no_drop", 1);
	set("no_steal", 1);
	set("no_put", 1);
	set("no_beg", 1);
	set("no_get", 1);
	set("no_insert", 1);
	set("process", 0);

	seteuid(getuid());
}

int is_container() { return 1; }

void init()
{
	object ob;
	add_action("do_fill", "fill");
	add_action("do_burn", "burn");
	add_action("do_putout", "putout");
}

int do_fill(string arg)
{
	object room = environment(this_player());

        if (!present(this_object(), this_player()))
                return 0;

	if (!arg || arg != "water")
		return notify_fail("你要往药臼里添加什么？\n");
	if (query("process") > 0)
		return notify_fail("你已经往药臼里添过水了啦！\n");
	if (!(int)room->query("resource/water"))
		return notify_fail("这里没有水。你找个有水之处再添水吧。\n");
	set("process", 1);
	message_vision("$N往药臼里添了些清水。\n", this_player());
	return 1;
}
int do_burn()
{
	object *inv = all_inventory(this_object());
	object room = environment(this_player());
	object me = this_player();
	int seq, i = 0, j = 0;

        if (!present(this_object(), this_player()))
                return 0;

	if (!wizardp(me))
	{
		if (query("process") == 0)
			return notify_fail("还没放水就点火，想干烧啊！\n");
		if (query("process") != 1)
			return notify_fail(HIY"现在不用你再点火了啦！\n"NOR);
		if (!present("fire", me))
			return notify_fail("你身上没有带火折。这回糟了吧。\n");
		if(!present("mu chai",me) && !present("mu chai",room))
			return notify_fail("点燃火折你才发现没有木柴可烧。\n");
	}
	set("process", 2);
	set("burntime", time());
	message_vision("$N掏出火折一晃，火折亮了起来。火折点燃木柴后，再把药臼放在柴上。\n", this_player());
	for ( seq = 0; seq < sizeof(inv); seq++)
	{
		if( !inv[seq]->query("vegetable"))
		{
			set("process", 3);
			message_vision("药臼里混进不能入药的东西。看来这臼药没用了。。。\n", this_player());
		}
		i += inv[seq]->query("vegetable");
		j += inv[seq]->query("nostrum");
		destruct(inv[seq]);
	}
	message_vision("过了一会药臼里冒出一股淡淡的白气。药材渐渐熬到水中。。。\n", this_player());
	set("vegetable", i);
	set("nostrum", j);
	return 1;
}
int do_putout()
{
	string *dir, target = "shit";
	object obj, room = environment(this_player());
	int i;

        if (!present(this_object(), this_player()))
                return 0;

	seteuid(getuid());
	if (query("vegetable") == 0)
		return notify_fail("药臼里没有药材，熬不成药了！\n");
	if (query("process") < 2)
		return notify_fail("现在没有火可灭了啦！\n");
	if (time() - query("burntime") < 180 && !wizardp(this_player()))
		return notify_fail("药正在熬，火候还没到，现在可灭不得火！\n");
	if (time() - query("burntime") > 300 && !wizardp(this_player()))
	{
		set("process", 0);
		return notify_fail("药好像熬了太久，火候过了，药熬糊了！\n");
	}
	message_vision("$N撤了着火的木柴，让药臼自行冷却。\n", this_player());
	if (query("process") == 3)
	{
		set("process", 0);
		return notify_fail("肯定是药臼中掺进杂质了，这次药没熬成！\n");
	}
	set("process", 0);
	dir = get_dir("/clone/medicine/nostrum/");
	for (i=0; i<sizeof(dir); i++)
	{
		obj = new( "/clone/medicine/nostrum/" + dir[i] );
		if (obj->query("vegetable") == query("vegetable") &&
			obj->query("nostrum") == query("nostrum"))
		{
			target = dir[i];
		}
		destruct(obj);
	}
	if(obj = new("/clone/medicine/nostrum/"+target))
	{
		if(obj->query("level") < this_player()->query_skill("medicine", 1))
		{
			obj->move(this_player());
			obj->move(this_object());
			message_vision("$N终于炼出一"+obj->query("unit")+obj->query("name")+"。\n", this_player());
			this_player()->add("medicine_count", 1);
		}
		else
		{
			destruct(obj);
			obj = new("/clone/medicine/nostrum/shit");
			obj->move(this_object());
			message_vision("可能是$N医术不精，炼出一"+obj->query("unit")+obj->query("name")+"。\n", this_player());
		}
		return 1;
	}
	else return notify_fail("可能是因为配方不太对，这次熬药没成功！\n");
}

