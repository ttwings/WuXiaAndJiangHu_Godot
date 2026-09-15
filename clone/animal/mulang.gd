#lang.c 狼
# Last Modified by winder on Aug. 1 2002

# extends Npc_TRAINEE;
# inherit "/# inherit/char/trainee";

func create():

	set_name("母狼", ["mu lang", "lang", "wolf"]);
	set_attr("race", "走兽");
	set_attr("gender", "雌性");
	set_attr("age", 15);
	set_attr("long", "这是一头灰色的母狼，正用红色的眼睛盯着你，不时发出令人胆战的嗥声！\n");
	set_attr("msg_fail", "$n转动脖颈对着$N就咬，$N忙缩回手");
	set_attr("msg_succ", "$N一挥手，$n的头便跟着动了起来");
	set_attr("msg_trained", "$n伸出红色的舌头舔了舔$N的脚");
	set_attr("auto_follow", 1);
	set_attr("wildness", 9);
	set_attr("attitude", "aggressive");

	set_attr("str", 29);
	set_attr("con", 40);
	set_attr("dex", 45);
	set_attr("int", 10);

	set_attr("combat_exp", 14000);

	set_temp("apply/attack", 20);
	set_temp("apply/damage", 20);
	set_temp("apply/armor", 20);

	set_attr("chat_chance", 10);
	set_attr("chat_msg", [
						"母狼发出一声嗥叫，好象随时都要扑上来！\n",
						"母狼的双目在黑暗中闪着红光，紧紧地注视着你的一举一动。\n",
						"「嗥~~~~」母狼发出一声嗥叫。\n",
					]);

	setup();

