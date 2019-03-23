// /feature/banker.c 银行家
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands
// Modified by Zeratul Jan 5 2001 增加了存款判断

#include <dbase.h>
#include <ansi.h>

void enough_rest()
{
        delete_temp("busy");
}

int do_check()
{
        // here we use 3 units to display bank infos
        int total = (int)this_player()->query("balance");
        
        // Modified by zeratul 2001-1-1
        if ( total > this_player()->query( "max_balance" ) )
       	{
       		total = this_player()->query( "max_balance" );
        	this_player()->set( "balance", total );
        }
        if (!total || total < 0)
        {
                this_player()->set("balance", 0);
                return notify_fail("您在敝商号没有存钱。\n");
        }
        write(this_object()->query("name")+"悄悄告诉你：您在敝商号共存有" + 
                MONEY_D->money_str(total) + "。\n");
        return 1;                                                               
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        if (query_temp("busy"))
           return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        me = this_player();                                                     
	if( me->is_busy() )
		return notify_fail("哟，抱歉，我这儿正忙着呢……您请稍候。\n");

        if (!arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
        {
           return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");
        }
           
        if((strsrch(to, "thousand") >= 0) ||
           (strsrch(to, "hundred") >= 0) ||
           (strsrch(to, "ten") >= 0) ||
           (strsrch(to, "100000") >= 0) ||
           (strsrch(to, "10000") >= 0) ||
           (strsrch(to, "1000") >= 0) ||
           (strsrch(to, "100") >= 0) ||
           (strsrch(to, "10") >= 0))
           return notify_fail("不能换成这种货币！\n");  

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if (!to_ob && file_size("/clone/money/" + to + ".c") < 0)
        {
           return notify_fail("你想兑换成什么？\n");
        }
        if (!from_ob)
        {
           return notify_fail("你身上没有带这种钱。\n");
        }
        if (amount < 1)
        {
           return notify_fail("你想白赚啊？\n");
        }
        if ((int)from_ob->query_amount() < amount)
        {
           return notify_fail("你带的" + from_ob->query("name") + "不够。\n");
        }
        bv1 = from_ob->query("base_value");
        if (!bv1)
        {
           return notify_fail("这样东西不值钱。\n");
        }
        bv2 = to_ob ? to_ob->query("base_value") : call_other("/clone/money/" + to, "query", "base_value" );
        if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
        if (amount == 0)
        {
           return notify_fail("这些" + from_ob->query("name") + "不够换。\n ");
        }

        // allowed to convert now
        set_temp("busy", 1);
        me->start_busy(5);

        from_ob->add_amount(-amount);

        if (!to_ob)
        {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me);
        }
        else
                to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
        chinese_number(amount), call_other("/clone/money/" + from, "query", "base_unit"), call_other("/clone/money/" + from, "query", "name"),
        chinese_number(amount * bv1 / bv2), call_other("/clone/money/" + to, "query", "base_unit"),
        call_other("/clone/money/" + to, "query", "name")), me);

//      from_ob->add_amount(-amount);
	me->start_busy(1);

        remove_call_out("enough_rest");
        call_out("enough_rest", 5);

        return 1;
}                                                                               

int do_deposit(string arg)                                                      
{
        string what;
        int amount;
//        int money_limit;
        object what_ob, me;

        if (query_temp("busy"))
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");
        me = this_player();
	if( me->is_busy() )
		return notify_fail("哟，抱歉，我这儿正忙着呢……您请稍候。\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
        {
                return notify_fail("命令格式：deposit:cun <数量> <货币单位>\n");
        }

        what_ob = present(what + "_money", me);
        if (!what_ob)
        {
                return notify_fail("你身上没有带这种钱。\n");
        }
        if (amount < 1)
        {
                return notify_fail("你想存多少" + what_ob->query("name") + "？\n");
        }                                                                       
        if ((int)what_ob->query_amount() < amount)
        {
                return notify_fail("你带的" + what_ob->query("name") + "不够。\n");
        }

        // deposit it
        set_temp("busy", 1);
/*
	if (me->query("age")==14) money_limit = 100;
	if (me->query("age")>14) money_limit = 100 + (me->query("age")-15) * 20;
	if (me->query("age")>20) money_limit = 200 + (me->query("age")-20) * 20;
	if (me->query("age")>30) money_limit = 400 + (me->query("age")-30) * 30;
	if (me->query("age")>40) money_limit = 800 + (me->query("age")-40) * 40;
	money_limit = money_limit*10000;

	if (me->query("balance") + what_ob->query("base_value") * amount > money_limit)
	{
                return notify_fail("你的存款额度已经用满了。\n");
	}
*/
        message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n",
                chinese_number(amount), what_ob->query("base_unit"),
                what_ob->query("name")), me);
        what_ob->add_amount(-amount);
        me->add("balance", call_other("/clone/money/" + what, "query", "base_value") * amount);
        
        // Added by zeratul 2001-1-1
        if ( me->query( "balance" ) > me->query( "max_balance" ) )
        {
        	tell_object( me, "你的存款额度已经用满了。\n");
        	me->set( "balance", me->query( "max_balance" ) );
        }

        remove_call_out("enough_rest");
        call_out("enough_rest", 5);
	me->start_busy(1);
        return 1;
}

int do_withdraw(string arg)
{
        int amount, v;
        string what;
        object me;

        if (query_temp("busy"))
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");
        me = this_player();
	if( me->is_busy() )
		return notify_fail("哟，抱歉，我这儿正忙着呢……您请稍候。\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
        {
                return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");
        }
        if (amount < 1)
        {
                return notify_fail("你想取出多少钱？\n");
        }
        if(amount >= 100)
        {
                return notify_fail("这么大的数目。本店没这么多零散现金。\n");
        }
        if (file_size("/clone/money/" + what + ".c") < 0)
        {
                return notify_fail("你想取出什么钱？\n");
        }
        what = "/clone/money/" + what;
        
        // Added by zeratul 2001-1-1
        if ( me->query( "balance" ) > me->query( "max_balance" ) )
        	me->set( "balance", me->query( "max_balance" ) );
        
        if ((v = amount * what->query("base_value")) > me->query("balance"))
        {
               return notify_fail("你存的钱不够取。\n");
        }

        set_temp("busy", 1);

        message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)), me);
        me->add("balance",  -v);
//        MONEY_D->pay_player(me, v = v * 9 / 10);
	//Modified by zeratul 2001-1-4
	MONEY_D->pay_player( me, v );

	me->start_busy(1);
        remove_call_out("enough_rest");
        call_out("enough_rest", 5);
        return 1;
}

