# maque.c 麻雀
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("麻雀", ["ma que", "que", "bird"]);
	set_attr("race", "飞禽");
	set_attr("age", 3);
	set_attr("long", "一只叽叽喳喳，飞来飞去的小麻雀。\n");
	set_attr("attitude", "peaceful");

	set_attr("combat_exp", 100);

	set_attr("chat_chance", 10);
	set_attr("chat_msg", [
						(
							: this_object(), "random_move"
							:),
						"小麻雀叽叽喳喳的欢叫着，在你头顶上飞来飞去。\n",
						"小麻雀忽而停在墙头，忽而飞上树梢，忙碌着找食吃。\n",
					]);

	set_attr("chat_msg_combat", [
							   (
								   : this_object(), "random_move"
								   :),
							   "小麻雀叽叽叽地怒叫着，全身的羽毛都抖竖起来！\n",
						   ]);

	setup();

