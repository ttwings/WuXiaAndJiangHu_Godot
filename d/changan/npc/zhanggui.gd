# zhanggui.c

extends Npc;
# inherit F_DEALER;

func create():
	set_name("南北行掌柜", "zhanggui");
	set("shen_type", 1);

	set("gender", "男性");
	set("age", 45);
	set("long",
	"他做了几十年的小买卖，真名反而没人知道，大家都叫他掌柜。\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 40000);
	set("attitude", "friendly");
	set("vendor_goods", [
		"/d/xingxiu/obj/fire",
		"/d/city/npc/obj/mabudai",
		"/d/city/npc/obj/beixin",
		"/d/city/npc/obj/toukui",
		"/d/city/npc/obj/cycle",
		"/d/city/npc/obj/surcoat",
		"/d/city/npc/obj/shield",
		"/d/city/npc/obj/huwan",
		"/d/city/npc/obj/zhitao",
		"/d/city/npc/obj/huyao",
		"/d/city/npc/obj/caoxie",
		"/d/city/npc/obj/pixue",
		"/d/city/npc/obj/shoutao",
		"/d/city/npc/obj/tieshou",
	]);
	
	setup();
	carry_object("/clone/misc/cloth").wear();


func init():
	add_action("do_list", "list");
	add_action("do_buy", "buy");

