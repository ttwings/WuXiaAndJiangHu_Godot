# // dasao.c 

# inherit NPC;
# inherit F_DEALER;
extends Npc
func create():
	set_name("大嫂","da sao");
	set_attr("age", 32);
	set_attr("gender", "女性");
	set_attr("per", 20);
	set_attr("attitude", "friendly");

	set_attr("combat_exp", 400);
	set_skill("unarmed", 10);
	set_skill("dodge", 10);

	set_attr("vendor_goods",{
		__DIR__ + "obj/taoyong",
		__DIR__ + "obj/zhuan",
		__DIR__ + "obj/wa",
	});
	setup();
	# carry_object("/clone/misc/cloth").wear();
	add_money("silver", 2);

func _init():
	create()
	add_action("do_buy", "buy");
	add_action("do_list", "list");

