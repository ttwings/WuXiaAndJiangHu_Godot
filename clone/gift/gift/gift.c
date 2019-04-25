#include <ansi.h>
inherit ITEM;

int query_autoload()
{
        return 1;
}

void create()
{
        set_name(HIY "仙丹" NOR, ({"gift"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIY "这是一颗增加容貌的仙丹。\n" NOR);
                set("unit", "颗");
                set("value", 10000);
                set("weight", 50);

                // 增加天赋的种类
                set("gift_type", "per");

                // 天赋种类的名称
                set("gift_name", "容貌");

                // 成功的几率
                set("gift_point", 100);

                // 成功的描述
                set("gift_msg", HIC "突然间你的皮肤透过一道光泽。\n" NOR);
        }
        setup();
}
init()
{
        add_action("do_eat", "eat");
}
int do_eat(string arg)
{
        int point = query("gift_point");
        int max, top;
        object me = this_player();

        if (!id(arg))
                return 0;
        if (me->is_busy())
        {
                write("你正忙着呢。\n");
                return 1;
        }
        //考虑特殊因素可以调节成功率

        //     max = 10 + SCBORN_D->query_scborn_times(me) * 5;
        max = 10;
        if (SCBORN_D->query_scborn_times(me) == 6)
                max = 10000;
        top = 35 + SCBORN_D->query_scborn_times(me) * 5;
        message_vision(WHT "$N" WHT "一仰脖，吞下了一" +
                           query("unit") + name() + WHT "。\n" NOR,
                       me);

        if (me->query("gift/" + query("gift_type") + "/all") >= max || me->query(query("gift_type")) >= top)
        {
                tell_object(me, "你觉得这药好象没什么效果。\n");
        }
        else if (random(100) >= point)
        {
                tell_object(me, HIR "不过你觉得这药好像没起到什么"
                                    "作用。\n" NOR);

                // 记录失败的记号
                me->add("gift/" + query("gift_type") + "/fail", 1);
                log_file("gift/eat_dan", sprintf("%-20s eat %-10s(%s) fail [%s]\n", me->query("name") + "(" + me->query("id") + ")", this_object()->name(), this_object()->query("gift_type"), ctime(time())));
        }
        else
        {
                tell_object(me, query("gift_msg"));
                tell_object(me, HIC "你的" + query("gift_name") +
                                    HIC "永久增加一点。\n" NOR);

                // 记录成功的记号
                me->add("gift/" + query("gift_type") + "/succeed", 1);
                log_file("gift/eat_dan", sprintf("%-20s eat %-10s(%s) success [%s]\n", me->query("name") + "(" + me->query("id") + ")", this_object()->name(), this_object()->query("gift_type"), ctime(time())));
                log_file("gift/tianfu",
                         sprintf("%-20s 吃下%-10s增加了%s(%s) [%s]\n",
                                 me->query("name") + "(" + me->query("id") + ")",
                                 base_name(this_object()),
                                 query("gift_name"), query("gift_type"), ctime(time())));

                // 增加相应的天赋属性
                me->add(query("gift_type"), 1);
        }

        // 记录入吃丹的总量
        me->add("gift/" + query("gift_type") + "/all", 1);
        destruct(this_object());
        return 1;
}
