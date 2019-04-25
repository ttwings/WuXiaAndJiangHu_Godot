// /clone/misc/cards/card_cs.c

#include <ansi.h>
#include <command.h>
inherit ITEM;

void create()
{
        set_name(HIR "圣诞贺卡" NOR, ({"Christmas card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "张");
                set("long",
"这是一张"HIR"圣诞贺卡"NOR"，送给每位在圣诞节进入侠客行一百
的玩家。你可以打开(dakai)来看看，记住自己的编号。
新年钟声敲响的时候，等待着我们的抽奖礼品。\n");
                set("value", 0);
                set_weight(10);
        }
        setup();
}
void init()
{
        add_action("do_dakai", "dakai");
        add_action("do_chaikai", "chaikai");
}
int do_dakai(string arg)
{
        object me = this_player();
        string message;
        int col;

        if (!present(this_object(), this_player()))
                return 0;

        if (arg == "card")
        {
                tell_object(me,
                            HIW "\n" +
                                "     ┏━━━━━━━━ " HIR "圣诞快乐" HIW " ━━━━━━━━┓\n" +
                                "     ┃  ┌──── Merry  Christmas ────┐  ┃\n" +
                                "     ┃  │                                  │  ┃\n" +
                                "     ┃  │                                  │  ┃\n");
                if (strlen(me->query("name")) == 2)
                        tell_object(me,
                                    HIW "     ┃  │  亲爱的" + me->query("name") + "：                      │  ┃\n");
                if (strlen(me->query("name")) == 4)
                        tell_object(me,
                                    HIW "     ┃  │  亲爱的" + me->query("name") + "：                    │  ┃\n");
                if (strlen(me->query("name")) == 6)
                        tell_object(me,
                                    HIW "     ┃  │  亲爱的" + me->query("name") + "：                  │  ┃\n");
                if (strlen(me->query("name")) == 8)
                        tell_object(me,
                                    HIW "     ┃  │  亲爱的" + me->query("name") + "：                │  ┃\n");
                if (strlen(me->query("name")) == 10)
                        tell_object(me,
                                    HIW "     ┃  │  亲爱的" + me->query("name") + "：              │  ┃\n");
                tell_object(me,
                            HIW "     ┃  │      愿您和您的家人在主的祝福    │  ┃\n" +
                                "     ┃  │  下，快乐、平安！                │  ┃\n" +
                                "     ┃  │                                  │  ┃\n" +
                                "     ┃  │             *  *" HIR "r" HIW "*  *            │  ┃\n" +
                                "     ┃  │          * *" HIR "a" HIW "* " HIG "^" HIY "Y" HIG "^" HIW " *" HIR "i" HIW "* *         │  ┃\n" +
                                "     ┃  │         *" HIM "m" HIW "*" HIG "^" HIY "Y" HIG "^" HIW "*" HIG "^\\^" HIW "*" HIG "^" HIY "Y" HIG "^" HIW "*" RED "s" HIW "*        │  ┃\n" +
                                "     ┃  │         " HIG "^" HIY "Y" HIG "^" HIW "*" HIG "\\" HIW "*" RED "e" HIW "*" HIG "/" HIW "*" HIG "l" HIW "*" HIG "/" HIW "*" HIG "^" HIY "Y" HIG "^" HIW "        │  ┃\n" +
                                "     ┃  │         *" HIG "\\" HIW "*" CYN "t" HIW "*" HIG "|" HIY "Y" HIG "^\\^" HIY "Y" HIG "|" HIW "*" HIG "l" HIW "*" HIG "/" HIW "*        │  ┃\n" +
                                "     ┃  │        *" MAG "s" HIW "*" HIG "|" HIY "Y" HIG "^\\\\^/^//^" HIY "Y" HIG "|" HIW "*" HIR "a" HIW "*       │  ┃\n" +
                                "     ┃  │        " GRN "^" YEL "Y" GRN "^\\\\_^\\\\\\//^_//^" YEL "Y" GRN "^" HIW "       │  ┃\n" +
                                "     ┃  │        " GRN "^\\_^\\_\\_\\//_/_/^_/^" HIW "       │  ┃\n" +
                                "     ┃  │         " GRN "^^\\_^\\_\\\\/_/^_/^^" HIW "        │  ┃\n" +
                                "     ┃  │           " GRN "^^\\_ \\// _/^^" HIW "          │  ┃\n" +
                                "     ┃  │               " GRN "\\_\\_/" HIW "              │  ┃\n" +
                                "     ┃  │                " GRN "/|\\" HIW "               │  ┃\n" +
                                "     ┃  │               " GRN "/\\\\/\\" HIW "              │  ┃\n" +
                                "     ┃  │                                  │  ┃\n" +
                                "     ┃  │                  " RED "侠客行一百恭贺" HIW "  │  ┃\n" +
                                HIW "     ┃  └─────────────────┘  ┃\n" +
                                "     ┗━━━━━━━━━━━━━━━━━━━━━┛\n" +
                                "\n" HIY + "         卡编号：" + me->query("holiday_cards") +
                                "\n" NOR);
        }
        return 1;
}

int do_chaikai(string arg)
{
        object newcard, box, obj0, obj1, obj2, obj3, obj4, obj5, obj6;
        object me = this_player();
        int col;

        if (!present(this_object(), this_player()))
                return 0;

        //	return notify_fail("还没到时候呢，别急拆开啊！\n");

        if (arg == "card")
        {
                message_vision("$N充满憧憬地拆开了圣诞卡，突然如魔术般，出现
一个礼品盒！\n", me);
                box = new(__DIR__"giftbox");
                newcard = new(__DIR__"card_cs_done");
                newcard->move(me);
                if (random(50) == 1)
                {
                        obj1 = new ("/clone/medicine/nostrum/puti-zi");
                        obj1->move(box);
                }
                if (random(20) == 1)
                {
                        //                        obj2 = new("/clone/money/100gold");
                        obj2 = new ("/clone/money/gold");
                        obj2->set_amount(100);
                        obj2->move(box);
                }
                if (random(3) == 1)
                {
                        obj3 = new ("/clone/medicine/nostrum/xiongdan");
                        obj3->move(box);
                }
                obj3 = new("/clone/medicine/nostrum/jiuhuawan");
                obj3->move(box);
                box->move(environment(me));
                destruct(this_object());
        }
        return 1;
}

string query_autoload()
{
        return 1 + "";
}
