// zhenwu-jian.c 真武剑
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIC "真武剑" NOR, ({"zhenwu jian", "sword", "jian"}));
        set_weight(50000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "柄");
                set("long", "此剑剑鞘铜绿斑斓，以铜丝嵌着两个篆文：“真武”。\n乃是创派之祖张三丰所用佩剑，向来是武当派镇山之宝。\n");
                set("value", 10000);
                set("material", "steel");
                set("weapon_prop/personality", 8);
                set("wield_msg", "$N「唰」的一声抽出$n。剑面流纹如水，澹然如镜。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(180);
        setup();
}
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query("shen") < 0 || victim->query("shen") > 0)
                return -damage_bonus / 2;

        if (me->query("shen") == 0 || victim->query("shen") == 0)
                return 0;
        if (me->query_skill_mapped("force") != "taiji-shengong")
                return 0;

        if (me->query_skill_mapped("sword") != "taiji-jian" ||
            me->query_skill("taiji-jian", 1) < 100)
                // only increase damage
                return damage_bonus / 3;

        switch (random(4))
        {
        case 0:
                if (!victim->is_busy())
                {
                        victim->start_busy(me->query_skill("sword") / 100 + 1);
                        return HIC "$N" HIC "跨前一步，手中的" NOR + HIY "真武剑" NOR + HIC "幻化成无数圆圈，向$n" HIC "逼去，剑法细密之极。\n"
                                                                                            "$n" HIC "大吃一惊，不知如何抵挡，只有连连后退！\n" NOR;
                }
        case 1:
                n = me->query_skill("sowrd");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n = victim->query("eff_jing");
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIY "$N" HIY "一声长吟，手中的真武剑化作一"
                                       "道长虹，“唰”的扫过$n" HIY "而去！\n" NOR
                                 : HIY "$N" HIY "突然大声喝道：“邪魔外道，还"
                                       "不受死？”手中真武剑" HIY "忽的一抖，$n" HIY "登时觉得眼花缭乱！\n" NOR;
        }

        // double effect
        return damage_bonus;
}