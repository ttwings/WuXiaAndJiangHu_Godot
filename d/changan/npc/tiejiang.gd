extends Npc

signal on_do_list
signal on_do_buy

func create():
	set_name("铁匠", "tiejiang");
	set_attr("shen_type", 1);
	set_attr("gender", "男性" );
	set_attr("age", 33);
	set_attr("long", "铁匠正用铁钳夹住一块红热的铁块放进炉中。\n");

	set_attr("combat_exp", 400);
	set_attr("attitude", "friendly");
	set_attr("vendor_goods",{
		"/clone/weapon/gangjian":3,
		"/clone/weapon/gangdao":3,
		"/clone/weapon/tiejia":3,
	});
	setup();

	carry_object("/clone/misc/cloth").wear();

func _init():
	create()
#	add_action("do_list", "list");
#	add_action("do_buy", "buy");
	
