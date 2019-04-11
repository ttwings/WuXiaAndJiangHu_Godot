// monkey.c 
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
	set_name("猴子", ({ "monkey" }) );
	set("gender", "雄性");
	set("race", "走兽");
	set("age", 25);
	set("long", "这只猴子在在桃树间跳上跳下，还不时津津有味地啃几口着蜜桃。\n");
	set("combat_exp", 5000);
	set("attitude", "peaceful");
	
	set("water", 200);
	set("food", 200);

	set("apply/attack", 10);
	set("apply/defense", 10);

//	set("chat_chance", 30);
//	set("chat_msg", ({
//		"土匪一声大喊: 此山是我开，此树是我栽，若要从此过，留下买路财 !\n",
//	}) );

	set_skill("unarmed", 25);
	set_skill("parry", 20);
	set_skill("dodge", 20);

	setup();
}
