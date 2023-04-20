extends Npc

signal on_do_list
signal on_do_buy

func create():
	set_name("铁匠", "tiejiang");
	set("shen_type", 1);
	set("gender", "男性" );
	set("age", 33);
	set("long", "铁匠正用铁钳夹住一块红热的铁块放进炉中。\n");

	set("combat_exp", 400);
	set("attitude", "friendly");
	set("vendor_goods",{
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
	
