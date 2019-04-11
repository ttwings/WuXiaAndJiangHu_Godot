// clone/shop/hesanqi.c
// Last modified by winder 2003.10.20
// 商业系统的初级阶段：小贩的商令管理者。

inherit NPC;
inherit F_BANKER;

#include <ansi.h>

int do_join(string arg);
int do_unjoin(string arg);
int do_yao();
int do_decide();

void create()
{
	set_name("何三七", ({ "he sanqi", "he", "sanqi" }));
	set("long", @LONG
浙南雁荡山高手何三七，自幼以卖馄饨为生，学成武功后，仍是挑
着副馄饨担游行江湖，这副馄饨担可是他的标记。他虽一身武功，
但自甘淡泊，以小本生意过活，武林中人说起来都是好生相敬。天
下市巷中卖馄饨的何止千万，但既卖馄饨而又是武林中人，那自是
非何三七不可了。
LONG);
	set("gender", "男性");
	set("age", 59);
	set("attitude", "peaceful");
	set("per", 21);
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 30);

	set("max_qi", 3500);
	set("max_jing", 2000);
	set("neili", 3000);
	set("max_neili", 300);
	set("jiali", 200);

	set("combat_exp", 500000);
	set("shen_type", 1);

	set_skill("hand", 140);
	set_skill("cuff", 140);
	set_skill("parry", 140);
	set_skill("dodge", 140);

	set_skill("changquan", 140);
	set_skill("sanshou", 140);
	set_skill("yanfly", 140);

	map_skill("parry", "changquan");
	map_skill("cuff", "changquan");
	map_skill("hand", "sanshou");
	map_skill("dodge", "yanfly");

	prepare_skill("cuff", "changquan");
	prepare_skill("hand", "sanshou");

	set("inquiry", ([
		"入会"     : "在我这，可以加入("HIY"join"CYN")商业协会。\n"NOR,
		"加入"     : "在我这，可以加入("HIY"join"CYN")商业协会。\n"NOR,
		"商业协会" : "在我这，可以加入("HIY"join"CYN")商业协会。\n"NOR,
	]));

	create_family("雁荡派", 5, "弟子");

	setup();
	carry_object(CLOTH_DIR"cloth")->wear();
}

void init()
{
	add_action("do_check", "check");
	add_action("do_check", "chazhang");
	add_action("do_convert", "convert");
	add_action("do_convert", "duihuan");
	add_action("do_deposit", "deposit");
	add_action("do_deposit", "cun");
	add_action("do_withdraw", "withdraw");
	add_action("do_withdraw", "qu");
	add_action("do_join", "join");
	add_action("do_decide", "decide");
	add_action("do_yao", "yao3");
	add_action("do_unjoin", "unjoin");
	delete_temp("busy");
}

int do_join(string arg)
{
	object me = this_player(), ob = this_object();

	if (! arg || arg != "商业协会")
		return notify_fail(CYN+ob->query("name")+"一楞，说道：你要加入什么？我这里是商业协会。\n" NOR);
	if (me->query("is_vendor"))
		return notify_fail(CYN+ob->query("name")+"皱了皱眉，说道：你不是已经加入商业协会了么？\n" NOR);
	if (me->query("bad_vendor"))
		return notify_fail(CYN+ob->query("name")+"冷笑一声，说道：既然你已经脱离了商业协会，又回来作甚？\n" NOR);
	tell_object(me, CYN+ob->query("name")+"点了点头，说道：你真的打算(" HIY "decide" NOR + CYN ")加入商业协会么？可考虑清楚了？\n" NOR);
	me->set_temp("want_join", 1);
	return 1;
}

int do_unjoin(string arg)
{
	object me = this_player(), ob = this_object();

	if (! arg || arg != "商业协会")
		return notify_fail(CYN+ob->query("name")+"皱了皱眉，说道：你打算脱离什么？说话不清不楚的。\n" NOR);
	if (! me->query("is_vendor"))
		return notify_fail(CYN+ob->query("name")+"冷笑一声，没理你。\n"NOR);
	tell_object(me,CYN+ob->query("name")+"叹了口气，说道：如果脱离商业协会，以后可不能反悔。你真打算(" HIY "decide" NOR + CYN ")这么做么？\n" NOR);
	me->set_temp("want_tuoli", 1);
	return 1;
}

int do_decide()
{
	object ob, me = this_player();

	if (me->query_temp("want_join"))
	{
		message_vision(HIC "$N" HIC "对着$n" HIC "微笑道：如今世道钱乃万能之物，以后好好干吧。\n" NOR, this_object(), me);

		me->set("is_vendor", 1);
		me->delete_temp("want_join");

		ob = new(__DIR__"shangling");
		ob->move(this_object());
		command("give shang ling to " + me->query("id"));
		return 1;
	}
	else
		if (me->query_temp("want_tuoli"))
		{
			message_vision(HIC "$N" CYN "对着$n" HIC "点点头，人各有志，从此以后你我再无瓜葛。\n" NOR, this_object(), me);
			me->delete("is_vendor");
			me->set("bad_vendor", 1);
			me->delete_temp("want_tuoli");

			if (objectp(ob = present("shang ling", me)));
			{
				message_vision(HIR "$N" HIR "将$n" HIR "的" NOR + ob->name(1) + HIR "注销了。\n" NOR, this_object(), me);
				destruct(ob);
			}
			return 1;
		 }

	 return notify_fail( CYN+ob->query("name")+"瞄了你一眼，皱了皱眉，没理你。\n" NOR);
}

int do_yao()
{
	object ob, me = this_player();
	
	ob = this_object();
	if (me->query("bad_vendor"))
		return notify_fail(CYN+ob->query("name")+"不耐烦道：走开，走开。你又回来作甚？\n" NOR);

	if (! me->query("is_vendor"))
		return notify_fail(CYN+ob->query("name")+"瞄了你一眼，没理你。\n" NOR);

	if (objectp(present("shang ling", me)))
		return notify_fail(CYN+ob->query("name")+"皱了皱眉道：我的天，你连这都要骗？果然是奸商的料。\n" NOR);

	if (me->query_temp("shang-ling"))
		return notify_fail(CYN+ob->query("name")+"皱眉道：刚才我不是才给了你一张么？那么快就弄丢了？\n" NOR);

	if (SHOP_D->is_owner(me->query("id")))
		return notify_fail(CYN+ob->query("name")+"微笑道：你现在不是已经开店了么？还要这个干嘛。\n" NOR);

	ob = new(__DIR__"shangling");
	ob->move(this_object());
	me->set_temp("shang-ling", 1);
	command("give shang ling to " + me->query("id"));
	command("say 吃饭的家伙自己保管好，别老是来烦我。");
	return 1;
}
