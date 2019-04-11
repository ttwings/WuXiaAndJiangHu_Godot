// Last Modified by winder on May. 29 2001
// fojing1.c

inherit ITEM;

void create()
{
	set_name("摩诃僧诋律",({"moheseng diyu","shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册佛经。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"buddhism",
			"exp_required":	0,
			"jing_cost":	35,
			"difficulty":	20,
			"max_skill":	100
		]) );
	}
}
