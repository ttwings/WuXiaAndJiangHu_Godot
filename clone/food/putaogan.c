// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

inherit ITEM;
void init();
void eat();

void create()
{
        set_name("葡萄干", ({"putao gan", "gan"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "葡萄干是西北边疆的特产，吃起来香甜可口．\n");
                set("unit", "把");
                set("value", 60);
                set("food_remaining", 4);
                set("food_supply", 10);
        }
}
void init()
{
        add_action("do_chi", "eat");
}

int do_chi(string arg)
{
        if (!this_object()->id(arg))
                return 0;

        if (this_player()->is_busy())
                return notify_fail("你上一个动作还没有完成。\n");

        if (!arg)
                return notify_fail("你要吃什么？\n");

        if ((int)this_player()->query("food") >= (int)this_player()->max_food_capacity())
                return notify_fail("你已经吃太饱了，再也塞不下任何东西了。\n");

        message_vision("$N从兜里掏出把葡萄干，一颗一颗的塞到嘴里，\n一颗，一颗，又一颗．．．\n", this_player());
        this_player()->add("food", 30);
        destruct(this_object());
        return 1;
}
