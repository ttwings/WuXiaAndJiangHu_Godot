// card_ny.c
#include <ansi.h>
#include <command.h>
inherit ITEM;

void create()
{
        set_name(HIR "新年贺卡" NOR, ({"new year card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "张");
                set("long",
"这是一张"HIR"新年贺卡"NOR"，送给每位在新的一年进入飞雪连天的玩家。
				你可以打开(dakai)来看看，会有意外惊喜哦。\n");
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
                                "                                                                   \n" +
                                "            ┬┴┬┌─　●─┬─　　│─┼─┐　●├─┤○         \n" +
                                "            ┴┬┴├┬　┌─┼─　│◎　│　│　○└┬┘●         \n" +
                                "            ─┼─││　│　│　　││─┴─┴　──┼──         \n" +
                                "            ●│○││　┴─┼─　　│○　　●　／　│　＼         \n" +
                                "                                                                   \n" +
                                "                                             飞雪连天恭贺          \n" +
                                "                                                                   \n" +
                                "\n" NOR);
        }
        return 1;
}

int do_chaikai(string arg)
{
        object newcard, box, obj0, obj1, obj2, obj3;
        object me = this_player();
        int col;

        if (!present(this_object(), this_player()))
                return 0;

        //	return notify_fail("还没到时候呢，别急拆开啊！\n");

        if (arg == "card")
        {
                message_vision("$N眉开眼笑地拆开了新年贺卡，突然掉下一个礼品盒！\n", me);
                box = new (__DIR__ "giftbox");
                newcard = new (__DIR__ "card_ny_done");
                newcard->move(me);
                if (random(100) == 1)
                {
                        obj0 = new ("/clone/medicine/nostrum/puti-zi");
                        obj0->move(box);
                }
                if (random(50) == 1)
                {
                        obj1 = new ("/clone/medicine/nostrum/renshenguo");
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
                obj3 = new ("/clone/medicine/nostrum/jiuhuawan");
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
