// bee.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
	set_name("蜜蜂", ({"bee"}));
	set("race", "昆虫");
	set("subrace", "飞虫");
	set("age", 5);
	set("long", "这是一只蜜蜂，正忙着采蜜。\n");

	set("str", 40);
	set("dex", 50);

	set_temp("apply/attack", 33);
	set_temp("apply/armor", 5);

	set("chat_chance", 2);
	set("chat_msg", ({
						(
							: this_object(), "random_move"
							:),
						"蜜蜂嗡嗡嗡飞过来，在你头上转了一圈，又飞走了。\n",
						"蜜蜂飞到路边的一朵鲜艳的野花上，忙忙碌碌地采着蜜。\n",
					}));

	setup();
}
