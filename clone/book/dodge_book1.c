// dodge_book.c

inherit ITEM;

void create()
{
	set_name("「闪躲之术」", ({ "dodge book", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","这是一本普普通通的研究闪躲之术的书籍。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":         "dodge",
			"exp_required": 0 ,
			"jing_cost":    20+random(20),
			"difficulty":	20,
			"min_skill":	0,
			"max_skill":	20
		]) );
	}
}
