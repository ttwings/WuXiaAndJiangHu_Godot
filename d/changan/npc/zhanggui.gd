# zhanggui.c

extends Npc;
# inherit F_DEALER;

func create():
	set_name("南北行掌柜", "zhanggui");
	set_attr("shen_type", 1);

	set_attr("gender", "男性");
	set_attr("age", 45);
	set_attr("long",
	"他做了几十年的小买卖，真名反而没人知道，大家都叫他掌柜。\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set_attr("combat_exp", 40000);
	set_attr("attitude", "friendly");
	set_attr("vendor_goods", [
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

