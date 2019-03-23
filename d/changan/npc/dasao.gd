// dasao.c 

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("?¡è¡ì???", ({"da sao", "sao"}));
	set("age", 32);
	set("gender", "????€¡ì");
	set("per", 20);
	set("attitude", "friendly");

	set("combat_exp", 400);
	set_skill("unarmed", 10);
	set_skill("dodge", 10);

	set("vendor_goods", ({
		__DIR__"obj/taoyong",
		__DIR__"obj/zhuan",
		__DIR__"obj/wa",
	}));
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 2);
}

void init()
{	
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

