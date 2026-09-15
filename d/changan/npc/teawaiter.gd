# teawaiter.c 
# inherit NPC;
# inherit F_DEALER;

extends Npc
func create():
#	reload("teawaiter");
	set_name("茶博士", "cha boshi");
	set_attr("shop_id", ({"boshi", "waiter"}));
	set_attr("gender", "男性");
	set_attr("class", "scholar");
	set_attr("combat_exp", 1000);
	set_attr("age", 26);
	set_attr("per", 14);
	set_attr("attitude", "friendly");
	set_attr("shen_type", 1);
	set_skill("unarmed", 10);
	set_attr("vendor_goods", ({
		"/d/city/obj/jiudai",
		"/d/city/obj/jitui",
	}) );
	setup();
	carry_object("/clone/misc/cloth").wear();

func _init():
	# object ob;
	create()
	# ::init();
	add_action("do_list", "list");
	add_action("do_buy", "buy");
