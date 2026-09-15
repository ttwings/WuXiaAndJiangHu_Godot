# bee.c
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("蜜蜂", ["bee"]);
	set_attr("race", "昆虫");
	set_attr("subrace", "飞虫");
	set_attr("age", 5);
	set_attr("long", "这是一只蜜蜂，正忙着采蜜。\n");

	set_attr("str", 40);
	set_attr("dex", 50);

	set_temp("apply/attack", 33);
	set_temp("apply/armor", 5);

	set_attr("chat_chance", 2);
	set_attr("chat_msg", [
						(
							: this_object(), "random_move"
							:),
						"蜜蜂嗡嗡嗡飞过来，在你头上转了一圈，又飞走了。\n",
						"蜜蜂飞到路边的一朵鲜艳的野花上，忙忙碌碌地采着蜜。\n",
					]);

	setup();

