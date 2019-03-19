// teawaiter.c 
inherit NPC;
inherit F_DEALER;

void create()
{
//	reload("teawaiter");
	set_name("²è²©Ê¿", ({"cha boshi","waiter"}));
	set("shop_id", ({"boshi", "waiter"}));
	set("gender", "ÄÐÐÔ");
	set("class", "scholar");
	set("combat_exp", 1000);
	set("age", 26);
	set("per", 14);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 10);
	set("vendor_goods", ({
		"/d/city/obj/jiudai",
		"/d/city/obj/jitui",
	}) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}
void init()
{
	object ob;

	::init();
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
