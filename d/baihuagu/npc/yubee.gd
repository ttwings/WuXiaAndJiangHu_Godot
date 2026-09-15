# // yebee.c 玉蜂

# inherit NPC;
#include <ansi.h>
extends Npc
func create():
	set_name_cn(HIY + "玉蜂" + NOR, "yu bee");
	set_attr("race", "昆虫");
	set_attr("subrace", "飞虫");
	setuid(getuid());
	set_attr("age", 1);
	set_attr("long", "这是一群玉色的蜜蜂，个头比普通蜜蜂大得多，\n");
	set_attr("attitude", "peaceful");
	set_attr("no_train", 1);
	set_attr("combat_exp", 500);
	set_attr("chat_chance", 3);
	set_attr("chat_msg",[
		"玉蜂嘤嘤嗡嗡地乱舞个不停。\n",
		"玉蜂飞速地向你冲过来，好象要叮你一口。可是在要触及你的一刹那又飞开了。\n",
		"玉蜂嗡嗡嗡飞过来，在你头上转了一圈，又飞走了。\n",
	]);
	set_temp("apply/attack", 200);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 2);
	set_temp("apply/armor", 1);
	# setup();

func _init():
	if(strsrch(file_name(environment(this_object())),"baihuagu") < 0):
		write("玉蜂嗡嗡嗡转了一圈，飞回百花谷去了。\n");
		destruct(this_object());
