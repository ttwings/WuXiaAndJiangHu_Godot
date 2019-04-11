// jinduan.c 

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("½õ¶Ð", ({ "jin duan", "jinduan", "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¼þ");
                set("material", "Ë¿");
		set("value", 5000);
                set("armor_prop/armor", 3);
        }
        setup();
}

