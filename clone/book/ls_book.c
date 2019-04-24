//独孤九剑剑谱(Lonely_sword_book)
// ls_book.c
// Date: Oct.6 1997 by That

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
int do_study(string);
int study(object me, string arg)
{
    object where = environment(me);
    object ob;
    int myskill, cost;

    cost = 20; //每读一次耗20精
    myskill = me->query_skill("lonely-sword", 1);
    if (!arg || !objectp(ob = present(arg, me)))
        return notify_fail("你要读什么？\n");
    if (!me->query_skill("literate", 1) || me->query_skill("literate", 1) < 100)
        return notify_fail("对照剑谱，你什么都读不懂。\n");
    if (me->is_busy())
        return notify_fail("你现在正忙着呢。\n");
    if (me->is_fighting())
        return notify_fail("你无法在战斗中专心下来研读新知！\n");
    if ((int)me->query("combat_exp") < 50000)
        return notify_fail("你的实战经验不足，不能学独孤九剑。\n");
    if (myskill > 299)
        return notify_fail("你研读了一会儿，发现上面所说的对你而言都太浅了。\n");
    if (myskill < 75)
        return notify_fail("你读了一会书,可是却毫无收获。\n");
    if ((int)me->query("jing") > cost)
    {
        if (myskill * myskill * myskill / 10 > (int)me->query("combat_exp"))
        {
            printf("也许是缺乏实战经验，你对独孤九剑剑谱面所说的东西总是无法领会。\n");
        }
        else
        {
            printf("你研读有关独孤九剑剑谱上的技巧，似乎有点心得。\n");
            me->improve_skill("lonely-sword", (int)me->query_skill("literate", 1) + (int)me->query("int"));
        }
    }
    else
    {
        cost = me->query("jing");
        write("你现在过于疲倦，无法专心下来研读新知。\n");
    }
    me->receive_damage("jing", cost);
    return 1;
}
void create()
{
    set_name(HIG "独孤九剑剑谱" NOR, ({"lonely_sword_book", "ls_book"}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit", "本");
        set("no_drop", "这是当世孤本啊。如何能丢失？");
        set("no_put", "这是当世孤本啊。如何能丢失？");
        set("no_get", 1);
        set("no_steal", 1);
        set("long", "独孤九剑剑法。你只能研习(yanxi)。\n");
        set("value", 1000);
        set("material", "paper");
        set("master_id", "npc");
    }
}

void init()
{
    add_action("do_study", "yanxi");
}

int do_study(string arg)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    write("哇，真是千古独步的剑法！");
    study(me, arg);
    return 1;
}

string query_autoload()
{
    object me;
    me = this_object();
    return me->query("master_id");
}
void autoload(string arg)
{
    set("master_id", arg);
}
void owner_is_killed()
{
    write(HIY "只见眼前金光一闪...好象是.....\n" NOR);
    destruct(this_object());
}
