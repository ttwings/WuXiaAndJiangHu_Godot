// mailbox.c
// Last Modified by sir on 5.5.2002
// 限制玩家收信总数为100封 wiz不受此限制

#include <ansi.h>
#define MAX_MAIL 20 //玩家收信总数

inherit ITEM;
inherit F_SAVE;
mapping *mails;

void get_mail_text(mapping mail, string str);
void confirm_copy(string yn, mapping mail);

void create()
{
	set_name("信箱", ({ "mailbox", "box" }) );
	set("long",
		"这是个人信箱，但信件内容对巫师无法保密，请勿谈及个人隐私：\n\n"
		"mailto  <某人>            寄信给别人。\n"
		"forward <信件编号> <某人> 将某封信转寄给别人。\n"
		"from                      查看信箱中的信件。\n"
		"read    <信件编号>        阅读某一封信件。\n"
		"discard <信件编号>        丢弃一封信件。\n"
	);
	set("unit", "个");
	set("no_drop", 1);
	set("no_steal", 1);
	set("no_put", 1);
	set("no_beg", 1);
	set("no_get", 1);
	set("no_insert", 1);

	seteuid(getuid());
}
int set_owner(string id)
{
	set("owner_id", id);
	return restore();
}
void init()
{
	object ob;
	int i, j = 0;

	if( this_player() && environment()==this_player() )
	{
		set_owner( (string)this_player()->query("id") );
		this_player()->set_temp("mbox_ob", this_object());
		set_name(this_player()->name(1)+"的信箱", ({"mailbox", "box"}));
		add_action("do_mail", "mailto");
		add_action("do_forward", "forward");
		add_action("do_from", "from");
		add_action("do_read", "read");
		add_action("do_discard", "discard");
	}
	if (!present(this_object(), this_player())) return 0;
	if( !pointerp(mails) || !sizeof(mails) ) return 0;
	for(i=0; i<sizeof(mails); i++)
		if(mails[i]["read"] == "N") j++;
	if( j >0 )
		tell_object(this_player(), HIG"绿林邮差跑步过来递给你"+chinese_number(j)+"封信，然后转身疾步离去。\n"NOR);
}

string query_save_file()
{
	string id;

	if( !stringp(id = query("owner_id")) ) return 0;
	return DATA_DIR + "mail/" + id[0..0] + "/" + id;
}

void receive_mail(string rcvr,mapping mail)
{
	object ppl, ob, obj;

	ob = FINGER_D->acquire_login_ob(rcvr);
	ppl = find_player(rcvr);
	if (!ppl) obj = ob;
	else obj = ppl;
	if(sizeof(mails) >=MAX_MAIL && !wizardp(this_player()) && !wizardp(ppl))
	{ 
		if (obj->query("id")==this_player()->query("id"))
			write("你信箱已经满了！\n");
		else
		{
			write(HIR"对方信箱已经满了。你没法寄出此信！\n"NOR);
			tell_object(obj,HIR"你的信箱已经满了，别人已经无法寄信给你，快整理整理吧！\n"NOR);
		}
		mails = mails;
		save();
	}
	else
	{
		if( !pointerp(mails) ) mails = ({ mail });
		else mails += ({ mail });
		save();
		if (obj->query("id")==this_player()->query("id"))
			write("你已经成功备份了！\n");
		else 
		{
			tell_object(obj,HIG"绿林邮差跑步过来递给你一封信，然后转身疾步离去。\n"NOR);
			write(HIG"信已发送成功。\n"NOR);
		}
	}
}

void send_mail(string rcvr, mapping mail)
{
	object ppl, ob, mbx, obj;
	int i;

	for (i = 0; i < sizeof(rcvr); i++) 
	if (rcvr[i]<'a' || rcvr[i]>'z') 
	{
		 write("没有这个人存在。\n");
		 return;
	}
	// Acquire the login object of receiver and mark the arrival of newmail.
	ob = FINGER_D->acquire_login_ob(rcvr);
	if( !ob ) 
	{
		write("没有这个人存在。\n");
		return;
	}

	// Get the mailbox or make a new one if not found.
	ppl = find_player(rcvr);
	if (!ppl) obj = ob;
	else obj = ppl;
	if (obj->query("env/no_mail"))
	{
		tell_object(this_player(), HIR"人家不想收你的信啦。\n"NOR);
		return;
	}
	else
	{
		mbx = obj->query_temp("mbox_ob");
	}
	if( !mbx )
	{
		mbx = new(MAILBOX_OB);
		mbx->set_owner(rcvr);
	}

	// Receive the mail and destruct the objects if receiver is off-line.
	mbx->receive_mail(rcvr,mail);
	if(!ppl)
	{
		destruct(mbx);
		destruct(ob);
	}
}

int do_mail(string arg)
{
	mapping mail;
	object me = this_player();

	if( me!=environment() ) return 0;
	if( !arg || arg=="" ) return notify_fail("你要给谁寄信？\n");
	mail = ([
		"from":	me->name(1)+"("+me->query("id")+")",
		"title": "无题",
		"to": arg,
		"time": time(),
		"text": "",
		"read": "N"
	]);
	write("信件标题：");
	input_to("get_mail_title", mail);
	return 1;
}

void get_mail_title(string str, mapping mail)
{
	if( str!="" ) mail["title"] = str;
	write("信件内容：\n");
	this_player()->edit( (: get_mail_text, mail :) );
}

void get_mail_text(mapping mail, string str)
{
	mail["text"] = str;
	if( sizeof(mails)>=MAX_MAIL && !wizardp(this_player()) )
	{
		write("您信箱已经满了！请及时清理。\n");
		confirm_copy("nonono", mail);
	}
	else
	{
		write("您要给自己留一份备份吗(y/n)？[n]");
		input_to("confirm_copy", mail);
	}
}

void confirm_copy(string yn, mapping mail)
{
	if( ( yn[0]=='y' || yn[0]=='Y' ) )
	receive_mail(this_player()->query("id"), mail);
	send_mail(mail["to"], mail);
}

int do_from()
{
	int i;

	if (!present(this_object(), this_player())) return 0;
	if( !pointerp(mails) || !sizeof(mails) )
	{
		write("您的信箱中目前没有任何信件。\n");
		return 1;
	}
	write("您的信箱中现在共有 " + sizeof(mails) + " 封信件：\n\n");
	for(i=0; i<sizeof(mails); i++)
		printf("%4s %2d %-40s "HIY"来自"NOR"：%-20s\n",
			mails[i]["read"] == "N" ? HIR"未阅"NOR : HIG"已阅"NOR,
			i+1, mails[i]["title"], mails[i]["from"]);
	write("\n");

	return 1;
}

int do_read(string arg)
{
	int num;

	if (!present(this_object(), this_player())) return 0;
	if( !arg || !sscanf(arg, "%d", num) )
		return notify_fail("您要读哪一封信？\n");
	if( !pointerp(mails) || num < 1 || num > sizeof(mails) )
		return notify_fail("没有这个编号的信件。\n");
	num --;
	printf("信件标题：%s\n寄 信 人：%s\n寄信时间：%s\n\n%s\n", mails[num]["title"], mails[num]["from"], ctime(mails[num]["time"]), mails[num]["text"] );
	mails[num]["read"]="Y";
	save();

	return 1;
}

int do_discard(string arg)
{
	int num;

	if (!present(this_object(), this_player())) return 0;
	if( !arg || !sscanf(arg, "%d", num) )
		return notify_fail("您要丢弃哪一封信？\n");
	if( !pointerp(mails) || num > sizeof(mails) )
		return notify_fail("没有这个编号的信件。\n");
	num --;
	if(num == 0) mails = mails[num+1..sizeof(mails)-1];
	else mails = mails[0..num-1] + mails[num+1..sizeof(mails)-1];
	save();
	write("丢弃成功。\n");

	return 1;
}

int do_forward(string arg)
{
	string dest;
	int num;
	mapping m;

	if (!present(this_object(), this_player())) return 0;
	if( !arg || sscanf(arg, "%d %s", num, dest)!=2 )
		return notify_fail("您要将哪一封信转寄给别人？\n");
	if( !pointerp(mails) || num > sizeof(mails) )
		return notify_fail("没有这个编号的信件。\n");
	num --;
	m = ([]);
	m["title"] = mails[num]["title"];
	m["text"] = mails[num]["text"];
	m["time"] = mails[num]["time"];
	m["from"] = mails[num]["from"]+"/转寄自"+this_player()->query("name");
	m["to"] = dest;
	m["read"]="N";
	send_mail( dest, m );

	return 1;
}

void owner_is_killed() { destruct(this_object()); }
