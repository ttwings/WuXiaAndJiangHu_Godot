// xiuhua_xie2.c

#include <ansi.h>
#include <armor.h>
inherit BOOTS;
void create()
{
    set_name(GRN "´ÐÂÌÐå»¨Ð¬" NOR, ({"xiuhua xie", "xie", "shoes"}));
    set_weight(1000);
    if ( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "Ë«");
        set("value", 1000);
        set("material", "grass");
        set("armor_prop/armor", 1);
        set("female_only", 1);
        set("armor_prop/personility", 3);
    }
    setup();
}
