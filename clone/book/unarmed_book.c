// unarmed_book.c

inherit ITEM;

void create()
{
	set_name("「格斗大全」", ({ "gedou daquan", "unarmed book", "shu" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本普普通通的介绍基本拳脚的书。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":         "unarmed",
			"exp_required": 0 ,
			"jing_cost":    20+random(20),
			"difficulty":	20,
			"min_skill":	0,
			"max_skill":	20
		]) );
	}
}
