// diaopi.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("貂皮", ({"diao pi", "pi"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "款");
                set("material", "fur");
                set("value", 5000);
                set("armor_prop/armor", 3);
        }
        setup();
}
