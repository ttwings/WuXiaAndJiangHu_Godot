// card_ft_done.c
#include <ansi.h>
#include <command.h>
inherit ITEM;

void create()
{
        set_name(HIR "新春贺卡" NOR, ({"spring festival card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "张");
                set("long",
"这是一张"HIR"新春贺卡"NOR"，送给每位在新春佳节连入飞雪连天
的玩家。你可以打开(dakai)来看看，会有意外惊喜哦。\n");
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
                            HIR "\n" +
                                "                                              \n" +
                                "        │       │       │       │         \n" +
                                "     ╭┴┴╮ ╭┴┴╮ ╭┴┴╮ ╭┴┴╮      \n" +
                                "     │    │ │    │ │    │ │    │      \n" +
                                "     │    │ │    │ │    │ │    │      \n" +
                                "     │ 迎 │ │ 春 │ │ 接 │ │ 福 │      \n" +
                                "     │    │ │    │ │    │ │    │      \n" +
                                "     │    │ │    │ │    │ │    │      \n" +
                                "     ╰┬┬╯ ╰┬┬╯ ╰┬┬╯ ╰┬┬╯      \n" +
                                "        !!       !!       !!       !!         \n" +
                                "        ;;       ;;       ;;       ;;         \n" +
                                "\n" +
                                HIY "                      「侠客行一百」恭贺    \n" +

                                "\n" NOR);
        }
        return 1;
}

int do_chaikai(string arg)
{
        object me = this_player();

        if (!present(this_object(), this_player()))
                return 0;

        message_vision("$N试图拆开新春贺卡，发现这张卡已经被拆开过了。\n", me);
        return 1;
}

string query_autoload()
{
        return 1 + "";
}
