
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(CYN "镇岳尚方" NOR, ({ "zhenyue shangfang", "zhenyue", 
                                              "jian", "sword" }));
        set_weight(8000);
        if (clonep())
//                destruct(this_object());
						set_default_object(__FILE__);
        else {
                set("long", CYN"
此剑乃周昭王瑕在位五十一年以二年岁次壬午，铸五剑，各投
五岳，铭曰镇岳尚方，古文篆书，剑长五尺通体流光。剑脊与
剑柄之上还铸有无数密密麻麻的古篆，似乎与武学有关。\n" NOR);
                set("unit", "柄");
                set("value", 80000);
								set("no_sell",1);
                set("material", "steel");
                set("wield_msg", CYN "$N" CYN "蓦地纵声长啸，霎时寒"
                                 "芒一闪，一道金光破空划过，落于$N"
                                 CYN "掌间。\n" NOR);
                set("unwield_msg", CYN "$N" CYN "一声轻哼，将手中的"
                                   "宝剑插入剑鞘。\n" NOR);
                set("skill", ([
                        "name"         : "hengshan-sword",
                        "exp_required" : 300000,
                        "jing_cost"    : 40,
                        "difficulty"   : 30,
                        "max_skill"    : 150,
                        "min_skill"    : 50
                ]));

           //     set("stable", 100);
        }
        init_sword(160);
        setup();
}
