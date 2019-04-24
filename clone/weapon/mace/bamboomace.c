// bamboomace.c
// Last Modified by winder on May. 25 2001
#include <weapon.h>

inherit MACE;

void create()
{
        set_name("Öñ½Ú±Þ", ({"bamboo mace", "mace"}));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "°Ñ");
                set("value", 500);
                set("material", "wood");
        }

        init_mace(15);
        setup();
}
