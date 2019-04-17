# // junfu.c

#include <armor.h>
extends Cloth;

func create():
	set_name("军服", ({ "junfu", "cloth" }));
	set("long", "这是一件有点旧的官兵服。\n");
	set_weight(2000);
	set("material", "cloth");
	set("unit", "件");
	set("value", 200);
	set("armor_prop/armor", 10);
	setup();

