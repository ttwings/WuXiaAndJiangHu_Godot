// qingyun.c
// shilling 97.2

inherit NPC;

#include <ansi.h>
#define UP(x) (ESC+"["+x+"A")
#define DOWN(x) (ESC+"["+x+"B")
#define SETDISPLAY(x,y)  (ESC+"["+x+";"+y+"f")
#define DELLINE ESC+"[K"
int give_prize();
mixed give_prize1(object ob);
string cancel_job();
string change_family();
mixed display(string num);
void give_quest(object ob);
void give_chinese_number(object ob);
void give_place(object ob);
void give_npc(object ob);
void give_self(object ob);
void give_number(object who);
string filter_color(string arg);
void create()
{
	seteuid(ROOT_UID);
	set_name("青云", ({ "qing yun", "shizhe" }));
	set("long", 
		"他是掌门人的得意门生，一个十分厉害的神秘人物。\n");
	set("gender", "男性");
	set("age", 20);
	set("attitude", "peaceful");
	set("class", "fighter");
	set("shen_type", 1);
	set("no_get", "1");
	set("str", 35);
	set("int", 28);
	set("con", 30);
	set("dex", 28);
	set("per", 29);
	
	set("max_qi", 1000);
	set("max_jing", 1000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 200000);
	set("score", 50000);

	set("inquiry",([
	"奖励" :  (: give_prize :),
	"cancel": (: cancel_job :),
	]));

	set_skill("blade",100);
	set_skill("ruyi-dao",100);
	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("unarmed", 100);
	set_skill("parry", 100);
	set_skill("lingboweibu", 100);
	set_skill("beiming-shengong",100);
	set_skill("liuyang-zhang", 100);

	map_skill("unarmed", "liuyang-zhang");
	map_skill("dodge", "lingboweibu");
	map_skill("force", "beiming-shengong");
	map_skill("blade", "ruyi-dao");

	create_family("逍遥派", 2, "弟子");
	set("title","逍遥派护法使者");
	set("nickname","天使之侣");
	setup();
	carry_object(CLOTH_DIR"cloth")->wear();
	carry_object(WEAPON_DIR"blade")->wield();

}
void init()
{
	add_action("do_answer","answer");
	add_action("do_changename","changename");
}

int do_changename(string arg)
{
	object me = this_player();
	object link;
	if (!arg) return 0;
	link = me->query_temp("link_ob");
	if (!objectp(link)) return 0;
	if (link->query("name")=="出错")
	{
		write(link->set("name",arg)+"\n");
		write(me->set("name",arg)+"\n");
		if (link->save() && me->save())
		write("成功修改名字为"+arg+"\n");
		return 1;
	}
	return notify_fail("你不能在这里修改名字。\n");
}
int give_prize()
{
	mixed s = give_prize1(this_player());
	if (stringp(s)) return s;
	command("say 请回答(answer)吧。");
	return 1;
}
mixed give_prize1(object who)
{
	object me = this_object();
	
	if (!who->query_temp("debug"))
	{
		if (!who->query_temp("can_give_prize") || !who->query_temp("prize_exp"))
		 	return "为啥要给你奖励哩？给我个理由先！";
		if (who->query_temp("prize_answer"))
			return "你还没回答我的上一个问题呢。";
	}
	who->delete_temp("can_give_prize");
	message_vision("$N对$n说道：可是我的奖励只给活人哩，你如果能回答我的问题，我就给你奖励。\n",me,who);
	give_quest(who);
	who->set_temp("pend_answer",1);
	return 1;
}
void give_quest(object ob)
{
//	give_chinese_number(ob);//中文数字转换
//	give_number(ob);//数字
	give_place(ob);//地名
//	give_npc(ob);// age,per,物品
//	give_self(ob);//玩家个人信息
}
/*
int is_keeper(object ob,int type)
{
	if (!clonep(ob)) return 0;
	if (!environment(ob)) return 0;
}
void give_npc(object ob)
{
//	int 
	
}*/
void give_chinese_number(object ob)
{
	int num,i;
	string cnum;
	num = random(9)+1;

	for(i=1;i<8;i++)
	{
		if (random(20)>i)
		{
			num = num*10 + random(10);
			continue;
		}
		break;
	}
	write("num="+num+"\n");
	if (random(5)==1)
	{
		tell_object(ob,this_object()->name()+"问道："+num+" 应该怎么念？\n");
		ob->set_temp("prize_answer",chinese_number(num));
	}
	else
	{
		tell_object(ob,this_object()->name()+"问道："+chinese_number(num)+" 转成数字是多少？\n");
		ob->set_temp("prize_answer",sprintf("%d",num));
	}
}
string *rshorts(object room)
{
	int i;
	mapping exits;
	mapping shorts;
	string *kexits;
	string name;
	string *names;
	
	exits = room->query("exits");
	kexits = keys(exits);
	names = ({});
	if (room->query_temp("exits"))
	return keys(room->query_temp("exits"));
	for(i=0;i<sizeof(exits);i++)
	{
		name = exits[kexits[i]]->query("short");
		names += ({ name });
		room->set_temp("exits/"+name,1);
	}
	return keys(room->query_temp("exits"));
}
object check_place(string file,string dir)
{
	string fname;
	object room;
	string err;
	mapping exits;
	string *shorts;
	
	fname = "/d/"+dir+"/"+file;
	if (strlen(file)<2) return 0;
	if (file[<2..<1]!=".c") return 0;
	if (file_size(fname)<0) return 0;
	if (!objectp(room = find_object(fname)))
	err = catch(room = load_object(fname));
	if (stringp(err))
	{
		message("channel:wiz",HIR"【调试】系统精灵：NPC_D 新建房间对象失败返回错误"+err+NOR,users());
		return 0;
	}
	if (room->query_max_encumbrance() < 10000000 ) return 0;
	if (!mapp(room->query("exits"))) return 0;
	if (room->query("no_quest")) return 0;
//	if (room->query("no_fight")) return 0;
	exits = room->query("exits");
	if (sizeof(exits)<2) return 0;
	shorts = rshorts(room);
	if (sizeof(shorts)<2) return 0;
	if (member_array(room->query("short"),shorts)>=0) return 0;
	return room;
}
void give_place(object ob)
{
	string *dirs,*files;
	string dir,file;
	int i,j,k;
	object room;
	mapping exits;
	string *shorts;
	string n1;
	
	dirs = get_dir("/d/");
	dirs -= ({  "npc","xiakedao","binghuo","working","death1",
		"wizard",	"death","gaochang","gumu","taohua",
		"heizhao" });//这些是没法做的
	i = random(sizeof(dirs));
	dir = dirs[i];
	files = get_dir("/d/"+dirs[i]+"/");
	while (sizeof(files)>0)
	{
		j = random(sizeof(files));
		file = files[j];
		if (!objectp(room=check_place(files[j],dirs[i])))
		{
			files -= ({ files[j] });
			continue;
		}
		exits = room->query("exits");
		k = random(sizeof(exits));
		shorts = rshorts(room);
		n1 = shorts[0];
		shorts -= ({ n1 });
		tell_object(ob,this_object()->name()+"说道：从"HIW+to_chinese(dir)+NOR"的"HIW+room->query("short")+NOR+
		"可能走到"+HIW+implode(shorts,NOR"、"HIW)+NOR"和"HIW+n1+NOR+"。\n");
		tell_object(ob,this_object()->name()+"说道：其中"HIW+keys(exits)[k]+NOR"方向是走到哪里？\n");
		room = room->query("exits")[keys(exits)[k]];
		ob ->set_temp("prize_answer",filter_color(room->query("short")));
		return;
	}
	give_prize1(ob);
}
int do_answer(string arg)
{
	object who = this_player();
	int exp,pot;
	string reason;
	string s;
	
	if (who->is_busy()) return 0;
	if (!arg) return 0;
	if (!who->query_temp("pend_answer"))	 return 0;
	who->delete_temp("pend_answer");
	arg = lower_case(arg);
	if (who->query_temp("invite")) arg = who->query_temp("prize_answer");
	message_vision("$N答道：是不是"+arg+"。\n",who);
	exp = who->query_temp("prize_exp");
	pot = who->query_temp("prize_pot");
	reason = who->query_temp("prize_reason");
	if (exp > 1000) exp = 1000;
	if (pot == 0 || pot > exp*3/10 || reason=="奸细")	pot = exp*3/10;
	if (arg != who->query_temp("prize_answer"))
	{ 
		message_vision("$N瞟了$n一眼，摇了摇头，叹了口气。\n",this_object(),who);
		if (!who->query_temp("pend_re_answer"))
		{
			who->set_temp("pend_re_answer",1);
			who->add("potential",-1*pot);
			who->add("combat_exp",-1*exp);
			who->add("gift/qpot",-1*pot);
			who->add("gift/qexp",-1*exp);
			message_vision("$N说道：没关系，你还有一次机会。\n",this_object());
			who->set_temp("can_give_prize",1);
			s=give_prize1(who);
			if (stringp(s))
			command("say "+s);
			return 1;
		}
		else 
		{
			message_vision("$N道：孺子不可教也。\n",this_object());
			command("hammer "+who->query("id"));
			who->add("potential",-1*pot);
			who->add("combat_exp",-1*exp);
			who->add("gift/qpot",-1*pot);
			who->add("gift/qexp",-1*exp);
			who->delete_temp("pend_re_answer");
			who->delete_temp("prize_exp");
			who->delete_temp("prize_reason");
 		 	who->delete_temp("prize_pot");
			who->delete_temp("prize_answer");
	  		who->start_busy(5);
			return 1;
		}
	}
	message_vision("$N朝着$n微笑着点了点头，伸手往$n一指，一道淡淡的金光笼住了$n。\n",this_object(),who);
	if (who->query_temp("pend_re_answer"))
	{
		exp *= 2;
		pot *= 2;
	}
	who->add("combat_exp",exp);
	who->add("potential",pot);
	who->add("gift/qexp",exp);
	who->add("gift/qpot",pot);
	who->add("gift/qingyun",1);
  	log_file("qingyun",sprintf("[%s]%8s %8s exp:%5d pot:%5d \n",ctime(time()),who->query("id"),who->query_temp("prize_reason"),exp,pot));
	tell_object(who,HIW"你被奖励了"+to_chinese(exp)+"点经验和"+
	to_chinese(pot)+"点潜能。\n"NOR);
	who->delete_temp("prize_exp");
	who->delete_temp("prize_pot");
	who->delete_temp("prize_reason");
	who->delete_temp("prize_answer");
	return 1;
}
string ins(int num)
{
	int i;
	string str="";
	for (i=0;i<num;i++)
		str += " "; //几个数字之间用什么东西填充 这里用空格 以后考虑百分号和[
  return str;
}


void give_number(object who)
{
	string str;
	string *str1,*str2,*str3,*str4;
	int i,len;
	string a,b,c,d,e;
	int f,g;
	int maxl;
	int l1,l2,l3,l4;
	string *all=({"1","2","3","4",/*"5",*/"6","7","8","9",//"0",
	"a","b","c","d","e","f","g","h","i","j","k","l","m","n",//"o",
	"p","q","r",/*"s",*/"t","u","v","w","x","y","z",});
	string *sts=({});
	int *j=({});
	int now,last;
	
	tell_object(who,this_object()->name()+"轻轻地一挥手，你眼前顿时闪起七彩的莹光。\n");
	a = all[random(sizeof(all))];
	b = all[random(sizeof(all))];
	c = all[random(sizeof(all))];
	d = all[random(sizeof(all))];
	while ((a == "5" && b == "5" && c == "5" && d == "5" )
	||(a == "6" && b == "6" && c == "6" && d == "6" )
	||(a == "8" && b == "8" && c == "8" && d == "8" )
	||(a == "9" && b == "9" && c == "9" && d == "9" )
	||(a == "f" && b == "u" && c == "c" && d == "k" )
	)
	{
		a = all[random(sizeof(all))];
		b = all[random(sizeof(all))];
		c = all[random(sizeof(all))];
		d = all[random(sizeof(all))];
	}
	who->set_temp("prize_answer",sprintf("%s%s%s%s",a,b,c,d));
	

	str1  = display(a); l1 = sizeof(str1); maxl = l1;
	str2  = display(b); l2 = sizeof(str2); if (maxl<l2) maxl = l2;
	str3  = display(c); l3 = sizeof(str3); if (maxl<l3) maxl = l3;
	str4  = display(d); l4 = sizeof(str4); if (maxl<l4) maxl = l4;
	if (l1 < maxl)
	{
		f = random(maxl-l1+1);
		for (i=0;i<f;i++)
			str1 = ({ ins(strlen(str1[0]))}) + str1;
		for (i=0;i<(12-l1-f);i++)
			str1 = str1 + ({ ins(strlen(str1[0])) });
	}
	if (l2 < maxl)
	{
		f = random(maxl-l2+1);
		for (i=0;i<f;i++)
			str2 = ({ ins(strlen(str2[0]))}) + str2;
		for (i=0;i<(12-l2-f);i++)
			str2 = str2 + ({ ins(strlen(str2[0])) });
	}
	if (l3 < maxl)
	{
		f = random(maxl-l3+1);
		for (i=0;i<f;i++)
			str3 = ({ ins(strlen(str3[0]))}) + str3;
		for (i=0;i<(12-l3-f);i++)
			str3 = str3 + ({ ins(strlen(str3[0])) });
	}
	if (l4 < maxl)
	{
		f = random(maxl-l4+1);
		for (i=0;i<f;i++)
			str4 = ({ ins(strlen(str4[0]))}) + str4;
		for (i=0;i<(12-l4-f);i++)
			str4 = str4 + ({ ins(strlen(str4[0])) });
	}

	str  = "";
	a = ins(random(2));
 	b = ins(random(2));
  	c = ins(random(2));
  	d = ins(random(2));
  	e = ins(random(2));
  	f = random(4); //  有几个数字放在第二行
	len =  0;
	if (arrayp(str1))
	{
		len = strlen(a);
  		len += strlen(str1[0]);
  		len += strlen(b);
  		if (f<3)//如果三个以下在第二行 就是至少两个在第一行 
  		{
	  		len += strlen(str2[0]);
 	 		len += strlen(c);
 	 	}
  		if (f<2)//至少三个在第一行
  		{	
	  		len += strlen(str3[0]);
  			len += strlen(d);
  		}
  		if (f<1)//全部都在第一行
  		{
  			len += strlen(str4[0]);
	  		len += strlen(e);
  		}
  	}
	for (i=0;i<maxl;i++)
	{
		str = a;
		str += str1[i]; str += b;
		if (f < 3)
		{
			str += str2[i]; 
			str += c;
		}
		if (f < 2)
		{
			str += str3[i]; 
			str += d;
		}
		if (f < 1)
		{
			str += str4[i]; 
			str += e;
		}
		sts += ({ str });
//		str += "\n";
	}
	if (f >0 )
	{
		for (i=0;i<maxl;i++)
		{
			str = a;
			if (f > 2)
			str += str2[i]; str += b;
			if (f > 1)
			str += str3[i]; str += d;
			if (f > 0)
			str += str4[i]; str += e;
			sts += ({str});
//			str += "\n";
		}
	}
	
	f = random(2); g = random(2);
	for(i=0;i<f;i++)
//	str =  ins(len) + "\n" + str; 
	sts = ({" "})+sts;
	for(i=0;i<g;i++)
//	str += ins(len) + "\n";  //第一行和最后一行补上随机行标识
	sts += ({" "});
	str = "";
	for(i=0;i<sizeof(sts);i++)
	{
		str += "\n";
		j+= ({i});
	}
	str +=	HIC+this_object()->name()+"说道：上面是四个数字或字母，请问它们是什么。\n"+NOR+SAVEC;
/*	for (i=0;i<sizeof(sts);i++)
	{
		tell_object(find_player("qingyun"),"sts["+i+"]="+sts[i]+"\n");
	}
*/	last = sizeof(j)+1;
	while(sizeof(j)>0)
	{
//		tell_object(who,"从起点"+sprintf("%2d",last));
		now = j[random(sizeof(j))];
		if (last > now)
			str += UP(sprintf("%d",last-now));
		else if (last < now)
			str += DOWN(sprintf("%d",now-last));
//		else
//		{
//			str += UP("1");
//			str += DOWN("1");
//		}		
//		tell_object(who,"到"+now+"上移了"+(last-now)+"行。\t");
		last = now+1;
		str += sts[now];
//		tell_object(who,"写下了sts["+now+"]\""+sts[now]+"\"\n");
		str += "\n";
		j -= ({now});
	}
	str += REST;
	tell_object(who,str);
//	input_to("answer","",1);
  return;
}
string cancel_job()
{
	object me = this_object();
	object who = this_player();
	
	if (!who->query("quest/kill")) return "你没有领任务，有什么好取消的";
	if (time() < who->query("quest/kill/time")) 
	return "你的任务时间还没到，快去做吧。";
	who->delete("quest/kill");
	return "好吧，测试时期免费帮你清除任务记录。";
}
mixed display(string num)
{
	mapping all = ([
	"1" : ({ 
({
"  ┌─┐  ",
"┌┘  │  ",
"└┐  │  ",
"  │☆│  ",
"┌┘  └┐",
"│      │",
"└───┘",
}),
({
"   _   ",
"  / |  ",
"  | |  ",
"  | |  ",
"  |_|  ",
}),
({
"   ___",
"  <  /",
"  / / ",
" / /  ",
"/_/   ",
}),
({
"  ┐  ",
"  │  ",
"╰┴╯",
"      ",
}),
({
"╭───┐  ",
"│◢◤█│  ",
"└─┐█│  ",
"┌─┘█└┐",
"│████│",
"└────┘",
}),/*
({
"      ____  ",
"    ╱  ╱▏",
"  ◢██  ▏",
"◢███  ▏",
"    ██  ▏",
"    ██  ▏",
"    ██  ▏",
"    ██  ▏",
"    ██  ▏",
"    ██  ▏",
"    ██  ▏",
"    ██╱  ",
}),*/
	}), // end 1
	"2" : ({ 
({
"╭───╮",
"│╭─╮│",
"╰╯  ││",
"╭─☆╯│",
"│╭──╯",
"│╰──╮",
"╰───╯",
}),
({
" ____  ",
"|___ \\ ",
"  __) |",
" / __/ ",
"|_____|",
}),
({
"   ___ ",
"  |__ \\",
"  __/ /",
" / __/ ",
"/____/ ",
}),
({
"╭─╮",
"╭─╯",
"└─╯",
"      ",
}),
({
"╭────╮",
"│◢◤◥◣│",
"└─╯◢◤│",
"╭◢◤┌─╯",
"│█◣◢█│",
"└────┘",
}),/*
({
"  ____________    ",
"╱          ╱╲  ",
"██████◣╱▏",
"███████  ▏",
"    ______██  ▏",
"  ╱      ██  ▏",
"◢██████╱  ",
"██████◤    ",
"██◤╲________  ",
"██◣╱      ╱▏",
"███████  ▏",
"◥██████╱  ",
}),*/
	}),// end 2
	"3" : ({ 
({
"╭───╮",
"│╭─╮│",
"╰╯╭╯/ ",
"   ☆  │ ",
"╭╮╰╮\\ ",
"│╰─╯│",
"╰───╯",
}),
({
" _____ ",
"|___ / ",
"  |_ \\ ",
" ___) |",
"|____/ ",
}),
({
"   _____",
"  |__  /",
"   /_ < ",
" ___/ / ",
"/____/  ",
}),
({
"╭─╮",
"  ─┤",
"╰─╯",
"      ",
}),
({
"╭────╮",
"│◢◤◥◣│",
"└─╭◢◤╯",
"┌─╰◥◣╮",
"│◥◣◢◤│",
"╰────╯",
}),/*
({
"  ____________    ",
"╱          ╱╲  ",
"██████◣╱▏",
"███████  ▏",
"  ________██  ▏",
"╱        ██  ▏",
"███████  ▏",
"███████  ▏",
"  ________██  ▏",
"╱        ██  ▏",
"███████╱  ",
"██████◤    ",
}),*/
	}), // end 3
	"4" : ({
({
"┌─┐─┐",
"│  │  │",
"│  │  │",
"│      │",
"└─┐  │",
"    │  │",
"    └─┘",
}),
({
" _  _   ",
"| || |  ",
"| || |_ ",
"|__   _|",
"   |_|  ",
}),
({
"        ",
"┌┐┌┐",
"││││",
"└┴┤│",
"    └┘",
"        ",
}),
({
"   __ __",
"  / // /",
" / // /_",
"/__  __/",
"  /_/   ",
}),
({
"╭───┐  ",
"│◢◤█│  ",
"│█│█└┐",
"│█◢██│",
"└─┐█┌┘",
"    └─┘  ",
}),/*
({
"  ____  ____      ",
"╱  ╱╱  ╱▏    ",
"██  ██  ▏    ",
"██  ██  ▏    ",
"██  ██  ▏__  ",
"██╱██╱￣╱▏",
"███████  ▏",
"███████╱  ",
"      ██  ▏    ",
"      ██  ▏    ",
"      ██  ▏    ",
"      ██╱      ",
}),*/
	}), // end 4
	"5" : ({
({
"╭───╮",
"│╭──╯",
"│╰──╮",
"╰─☆╮│",
"╭╮  ││",
"│╰─╯│",
"╰───╯",
}),
({
" ____  ",
"| ___| ",
"|___ \\ ",
" ___) |",
"|____/ ",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████╱  ",
"██  ▏______  ",
"██╱￣    ╱▏",
"██████  ▏",
"██████  ▏",
"  ______██  ▏",
"╱      ██  ▏",
"██████  ▏",
"██████╱  ",
}),*/
	}), // end 5
	"6" : ({
({
"╭───╮",
"│╭──╯",
"│╰──╮",
"│╭☆╮│",
"││  ││",
"│╰─╯│",
"╰───╯",
}),
({
"  __   ",
" / /_  ",
"| '_ \\ ",
"| (_) |",
" \\___/ ",
}),
({
"   _____",
"  / ___/",
" / __ \\ ",
"/ /_/ / ",
"\\____/  ",
}),
({
" ╭─╮",
" ├─╮",
" ╰─╯",
"       ",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████╱  ",
"██  ▏______  ",
"██╱￣    ╱▏",
"██████  ▏",
"██████  ▏",
"██  ▏██  ▏",
"██╱￣██  ▏",
"██████  ▏",
"██████╱  ",
}),*/
	}), // end 6
	"7" : ({
({
" _____ ",
"|___  |",
"   / / ",
"  / /  ",
" /_/   ",
}),
({
" _____",
"/__  /",
"  / / ",
" / /  ",
"/_/   ",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████  ▏",
"        ██  ▏",
"        ██  ▏",
"        ██  ▏",
"        ██  ▏",
"        ██  ▏",
"        ██  ▏",
"        ██  ▏",
"        ██╱  ",
}),*/
	}), // end 7
	"8" : ({
({
"╭───╮",
"│╭─╮│",
"│╰─╯│",
"│╭─╮│",
"││  ││",
"│╰─╯│",
"╰───╯",
}),
({
"  ___  ",
" ( _ ) ",
" / _ \\ ",
"| (_) |",
" \\___/ ",
}),/*
({
"  ______________  ",
"╱            ╱▏",
"███████  ▏",
"███████  ▏",
"██  ▏  ██  ▏",
"██╱￣￣██  ▏",
"███████  ▏",
"███████  ▏",
"██  ▏  ██  ▏",
"██╱￣￣██  ▏",
"███████  ▏",
"███████╱  ",
}),*/
	}), // end 8
	"9" : ({
({
"╭───╮",
"│╭─╮│",
"││  ││",
"│╰☆╯│",
"╰──╮│",
"╭──╯│",
"╰───╯",
}),
({
"  ___  ",
" / _ \\ ",
"| (_) |",
" \\__, |",
"   /_/ ",
}),/*
({
"  ______________  ",
"╱            ╱▏",
"███████  ▏",
"███████  ▏",
"██  ▏  ██  ▏",
"██╱￣￣██  ▏",
"███████  ▏",
"███████  ▏",
"  ________██  ▏",
"╱        ██  ▏",
"███████  ▏",
"███████╱  ",
}),*/
	}), // end 9
	"a" : ({
({
"    █┐    ",
"  █┌█┐  ",
"█┌┘└█┐",
"█████│",
"█┌──█│",
"└┘    └┘",
}),
({
"    ___ ",
"   /   |",
"  / /| |",
" / ___ |",
"/_/  |_|",
}),/*
({
"        ____        ",
"      ╱  ╱╲      ",
"    ◢██◣  ╲    ",
"  ◢████◣  ╲  ",
"◢██◤◥██◣╱▏",
"██◤▏  ◥██  ▏",
"██╱▔▔▔██  ▏",
"████████  ▏",
"████████  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██╱      ██╱  ",
}),*/
({
"╭──╮",
"│ ○ │",
"│╭╮│",
"╰╯╰╯",
}),
({
"    _    ",
"   / \\   ",
"  / _ \\  ",
" / ___ \\ ",
"/_/   \\_\\",
"         ",
}),
	}), // end a
	"b" : ({
({
"████┐  ",
"█┌──█┐",
"████┌┘",
"█┌──█┐",
"████┌┘",
"└───┘  ",
}),/*
({
"  __________      ",
"╱        ╱╲    ",
"█████◣  ╲  ",
"██████◣╱▏",
"██  ▏  ██  ▏",
"██╱▔▔██╱  ",
"██████◤╲  ",
"██████◣╱▏",
"██  ▏  ██  ▏",
"██╱▔▔██  ▏",
"███████╱  ",
"██████◤    ",
}),
({
"  ____          ",
"╱  ╱▏        ",
"██  ▏        ",
"██  ▏__      ",
"██╱▔╱╲    ",
"████◣  ╲  ",
"█████◣╱▏",
"██▕◥██  ▏",
"██  ▏██  ▏",
"██╱◢██╱  ",
"█████◤    ",
"████◤      ",
}),*/
({
" ____  ",
"| __ ) ",
"|  _ \\ ",
"| |_) |",
"|____/ ",
}),
({
" _     ",
"| |__  ",
"| '_ \\ ",
"| |_) |",
"|_.__/ ",
}),
	}), // end b
	"c" : ({
({
"█████┐",
"█┌───┘",
"█│        ",
"█│        ",
"█████┐",
"└────┘",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████╱  ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏______  ",
"██╱▔    ╱▏",
"██████  ▏",
"██████╱  ",
}),*/
({
"  _____",
" / ___/",
"/ /__  ",
"\\___/  ",
}),
({
"╭─╮",
"│    ",
"╰─╯",
"      ",
}),
({
"╭━━━┓",
"┃        ",
"┃        ",
"┃        ",
"┃        ",
"╰━━━┛",
}),/*
({
"    ________  ",
"  ╱      ╱▏",
"◢████  ▏",
"█████╱  ",
"██◤▏      ",
"██  ▏      ",
"██╱╲____  ",
"██◣╱  ╱▏",
"█████  ▏",
"◥████╱  ",
}),*/
({
"╭──╮",
"│╭─╯",
"│╰─╮",
"╰──╯",
}),
({
"  ____ ",
" / ___|",
"| |    ",
"| |___ ",
" \\____|",
}),
({
"  ___ ",
" / __|",
"| (__ ",
" \\___|",
}),
({
"┏━  ",
"┗━  ",
}),
	}), // end c
	"d" : ({
({
"████┐  ",
"█┌──█┐",
"█│    █│",
"█│    █│",
"████┌┘",
"└───┘  ",
}),
({
"       __",
"  ____/ /",
" / __  / ",
"/ /_/ /  ",
"\\__,_/   ",
}),
({
"┌─╮",
"│  │",
"└─╯",
}),/*
({
"  __________      ",
"╱        ╱╲    ",
"█████◣  ╲  ",
"██████◣╱▏",
"██  ▏  ◥█  ▏",
"██  ▏    █  ▏",
"██  ▏    █  ▏",
"██  ▏    █  ▏",
"██  ▏____█  ▏",
"██╱▔  ◢█╱  ",
"██████◤    ",
"█████◤      ",
}),
({
"          ____  ",
"        ╱  ╱▏",
"        ██  ▏",
"    ____██  ▏",
"  ╱    ██  ▏",
"◢█████  ▏",
"██████  ▏",
"██◤▏██  ▏",
"██╱╲██  ▏",
"██◣╱██  ▏",
"██████  ▏",
"◥█████╱  ",
}),*/
({
" ____  ",
"|  _ \\ ",
"| | | |",
"| |_| |",
"|____/ ",
}),
({
"     _ ",
"  __| |",
" / _` |",
"| (_| |",
" \\__,_|",
}),
({
"  ┏  ",
"┏┫  ",
"┗┻  ",
}),
	}), // end d
	"e" : ({
({
"█████┐",
"█┌───┘",
"████┐  ",
"█┌──┘  ",
"█████┐",
"└────┘",
}),/*
({
"    ________    ",
"  ╱      ╱╲  ",
"◢████◣╱▏",
"██████  ▏",
"██╱ _██  ▏",
"██████╱  ",
"█████◤__  ",
"██╱    ￣╱▏",
"██████  ▏",
"◥█████╱  ",
}),*/
({
"    ______",
"   / ____/",
"  / __/   ",
" / /___   ",
"/_____/   ",
}),
({
"┌─╮",
"├─  ",
"└─╯",
"      ",
}),
({
"┏━━━┓",
"┃        ",
"┣━━━┫",
"┃        ",
"┃        ",
"┗━━━┛",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████╱  ",
"██  ▏______  ",
"██╱▔    ╱▏",
"██████  ▏",
"██████╱  ",
"██  ▏______  ",
"██╱▔    ╱▏",
"██████  ▏",
"██████╱  ",
}),*/
({
"┌─┘",
"┌┘  ",
"──┘",
}),
({
" _____ ",
"| ____|",
"|  _|  ",
"| |___ ",
"|_____|",
}),
({
"┌──┐",
"│┌─┘",
"│┌┘  ",
"└──┘",
}),
({
" ┏┓ ",
" ┣┛ ",
" ┗┛ ",
}),
	}), // end e
	"f" : ({
({
"█████┐",
"█┌───┘",
"████┐  ",
"█┌──┘  ",
"█│        ",
"└┘        ",
}),
({
"    ______",
"   / ____/",
"  / /_    ",
" / __/    ",
"/_/       ",
}),
({
"    ____",
"   / __/",
"  / /_  ",
" / __/  ",
"/_/     ",
}),
({
"┌─╮",
"├─  ",
"╰    ",
"      ",
}),
({
"  ┌╮",
" -┼- ",
"  │  ",
"  ╯  ",
}),
({
"┏━━━┓",
"┃        ",
"┣━━━┫",
"┃        ",
"┃        ",
"┻        ",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████╱  ",
"██  ▏____    ",
"██╱▔  ╱▏  ",
"█████  ▏  ",
"█████╱    ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██╱          ",
}),
({
"    ________  ",
"  ╱      ╱▏",
"◢████  ▏",
"█████╱  ",
"██╱    ╱▏",
"█████  ▏",
"█████╱  ",
"██  ▏      ",
"██  ▏      ",
"██  ▏      ",
"██╱        ",
}),*/
({
"┌─┘",
"┌┘  ",
"┘    ",
}),
({
" _____ ",
"|  ___|",
"| |_   ",
"|  _|  ",
"|_|    ",
}),
({
"  __ ",
" / _|",
"| |_ ",
"|  _|",
"|_|  ",
}),
({
"┌───┐",
"│┌─→│",
"││─┬┘",
"│☆→│  ",
"││┌┘  ",
"│↓│    ",
"└─┘    ",
}),
({
"┌──┐",
"│┌─┘",
"│┌┘  ",
"└┘    ",
}),
({
"  ┏  ",
"  ╋  ",
"  ┃  ",
"  ┛  ",
}),
	}), // end f
	"g" : ({
({
"████┐  ",
"█┌──┘  ",
"█│  ██┐",
"█│    █│",
"████┌┘",
"└───┘  ",
}),
({
"╭─╮",
"│  ┬",
"╰─╯",
"      ",
}),
({
"╭━━━┓",
"┃        ",
"┃      ┳",
"┃      ┃",
"┃      ┃",
"╰━━━╯",
}),/*
({
"  __________      ",
"╱        ╱╲    ",
"█████◣  ╲  ",
"██████◣╱▏",
"██  ▏    █╱  ",
"██  ▏  ______  ",
"██  ▏╱    ╱▏",
"██  ▏███  ▏",
"██  ▏____█  ▏",
"██╱▔    █  ▏",
"███████  ▏",
"███████╱  ",
}),*/
({
"  ____ ",
" / ___|",
"| |  _ ",
"| |_| |",
" \\____|",
}),
	}), // end g
	"h" : ({
({
"┌┐┌┐",
"│├┤│",
"│├┤│",
"││││",
"└┘└┘",
"        ",
}),
({
"┌┐    ",
"│├┬╮",
"││││",
"││││",
"└┘└┘",
"        ",
}),
({
"█┐    █┐",
"█│    █│",
"█████│",
"█┌──█│",
"█│    █│",
"└┘    └┘",
}),
({
"    __  __",
"   / / / /",
"  / /_/ / ",
" / __  /  ",
"/_/ /_/   ",
}),
({
"    __  ",
"   / /_ ",
"  / __ \\",
" / / / /",
"/_/ /_/ ",
}),
({
"┳      ┳",
"┃      ┃",
"┣━━━┫",
"┃      ┃",
"┃      ┃",
"┻      ┻",
}),/*
({
"  ____    ____  ",
"╱  ╱▏╱  ╱▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██╱▔██  ▏",
"██████  ▏",
"██████  ▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██╱  ██╱  ",
}),
({
"  ____          ",
"╱  ╱▏        ",
"██  ▏        ",
"██  ▏__      ",
"██╱▔╱╲    ",
"████◣  ╲  ",
"█████◣╱▏",
"██▕◥██  ▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██╱  ██╱  ",
}),*/
({
"╭╮╭╮",
"│╰╯│",
"│╭╮│",
"╰╯╰╯",
}),
({
"│  │",
"┌─│",
"┘  ┘",
}),
({
" _   _ ",
"| | | |",
"| |_| |",
"|  _  |",
"|_| |_|",
}),
({
" _     ",
"| |__  ",
"| '_ \\ ",
"| | | |",
"|_| |_|",
}),
({
"┌─┐    ",
"│☆│    ",
"││└─╮",
"│├─┐│",
"│││││",
"│↓│↓│",
"└─┘─┘",
}),
({
"┌┐┌┐",
"││││",
"│┌┐│",
"└┘└┘",
}),
({
"┓    ",
"┣┓  ",
"┛┗  ",
}),
	}), // end h
	"i" : ({
({
"   ○   ",
"  ┌┐  ",
"  ││  ",
"  ││  ",
"  └┘  ",
"        ",
}),
({
"╭┬╮",
"  │  ",
"╰┴╯",
"      ",
}),
({
"█████┐",
"    █┌─┘",
"    █│    ",
"    █│    ",
"█████┐",
"└────┘",
}),
({
"    ____",
"   /  _/",
"   / /  ",
" _/ /   ",
"/___/   ",
}),
({
" ┳ ",
" ┃ ",
" ┃ ",
" ┃ ",
" ┃ ",
" ┻ ",
}),/*
({
"  ____________  ",
"╱          ╱▏",
"██████  ▏",
"██████╱  ",
"    ██  ▏    ",
"    ██  ▏    ",
"    ██  ▏    ",
"    ██  ▏    ",
"  __██  ▏__  ",
"╱  ██╱▔╱▏",
"██████  ▏",
"██████╱  ",
}),
({
"  ____  ",
"╱  ╱▏",
"██  ▏",
"██╱  ",
"╱  ╱▏",
"██  ▏",
"██  ▏",
"██  ▏",
"██  ▏",
"██  ▏",
"██  ▏",
"██╱  ",
}),*/
({
"╭──╮",
"╰╮╭╯",
"╭╯╰╮",
"╰──╯",
}),
({
" ___ ",
"|_ _|",
" | | ",
" | | ",
"|___|",
}),
({
"┌───┐",
"│←┬→│",
"└┐│┌┘",
"  │☆│  ",
"┌┘│└┐",
"│←┴→│",
"└───┘",
}),
	}), // end i
	"j" : ({
({
"     ○ ",
"    ┌┐",
"    ││",
"╭╮││",
"╰┴┴╯",
"        ",
}),
({
"█████┐",
"      █┌┘",
"      █│  ",
"█    █│  ",
"└██┌┘  ",
"  └─┘    ",
}),
({
"        ┳",
"        ┃",
"        ┃",
"        ┃",
"┳      ┃",
"╰━━━╯",
}),
({
"       __",
"      / /",
" __  / / ",
"/ /_/ /  ",
"\\____/   ",
}),
({
"╭┬╮",
"  │  ",
"╰╯  ",
"      ",
}),/*
({
"    __________  ",
"  ╱        ╱▏",
"  █████  ▏",
"  █████╱  ",
"      ██  ▏  ",
"      ██  ▏  ",
"      ██  ▏  ",
"      ██  ▏  ",
"╱╲__██  ▏  ",
"◣╱  ██  ▏  ",
"█████  ▏  ",
"◥████╱    ",
}),
({
"        ____  ",
"      ╱  ╱▏",
"      ██  ▏",
"      ██╱  ",
"      ╱▔╱▏",
"      ██  ▏",
"      ██  ▏",
"      ██  ▏",
"      ██  ▏",
"╱╲__██  ▏",
"◣╱  ██  ▏",
"█████╱  ",
"◥███◤    ",
}),*/
({
"╭──╮",
"╰╮╭╯",
"╭╯│  ",
"╰─╯  ",
}),
({
"     _ ",
"    | |",
" _  | |",
"| |_| |",
" \\___/ ",
}),
({
"   _ ",
"  (_)",
"  | |",
"  | |",
" _/ |",
"|__/ ",
}),
({
"┌───┐",
"│←┬→│",
"└┐│┌┘",
"  │☆│  ",
"┌┘││  ",
"│←┘│  ",
"└──┘  ",
}),
({
"    ┌┐",
"    ││",
"┌┐││",
"└──┘",
}),
({
"   ┓ ",
"   ┃ ",
" ┗┛ ",
}),
	}), // end j
	"k" : ({
({
"█┐    █┐",
"█│  █┌┘",
"███┌┘  ",
"█┌─█┐  ",
"█│  └█┐",
"└┘    └┘",
}),
({
"    __ __",
"   / //_/",
"  / ,<   ",
" / /| |  ",
"/_/ |_|  ",
}),
({
"┳     __",
"┃   ╱  ",
"┣━<    ",
"┃   \\   ",
"┃    \\__",
"┻       ",
}),/*
({
"  ____        __  ",
"╱  ╱▏    ╱╱▏",
"██  ▏  ◢█╱  ",
"██  ▏◢█◤    ",
"██▕◢█◤      ",
"██◢█◤        ",
"███◤╲        ",
"███◣  ╲      ",
"██◥█◣  ╲    ",
"██▕◥█◣  ╲  ",
"██  ▏◥█◣  ╲",
"██╱    ◥█◣╱",
}),
({
"  ____          ",
"╱  ╱▏  ____  ",
"██  ▏╱  ╱  ",
"██▕◢█◤    ",
"██◢█◤      ",
"███◤        ",
"██◤╲        ",
"██◣  ╲      ",
"███◣  ╲    ",
"██◥█◣  ╲  ",
"██▕◥█◣  ╲",
"██╱  ◥█◣╱",
}),*/
({
" _  __",
"| |/ /",
"| ' / ",
"| . \\ ",
"|_|\\_\\",
}),
({
" _    ",
"| | __",
"| |/ /",
"|   < ",
"|_|\\_\\",
}),
	}), // end k
	"l" : ({
({
"█┐        ",
"█│        ",
"█│        ",
"█│        ",
"█████┐",
"└────┘",
}),
({
"    __ ",
"   / / ",
"  / /  ",
" / /___",
"/_____/",
}),
({
"┳        ",
"┃        ",
"┃        ",
"┃        ",
"┃        ",
"╰━━━┛",
}),/*
({
"  ____          ",
"╱  ╱▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏        ",
"██  ▏______  ",
"██╱▔    ╱▏",
"██████  ▏",
"██████╱  ",
}),*/
({
"╭╮    ",
"││    ",
"│╰─╮",
"╰──╯",
}),
({
" _     ",
"| |    ",
"| |    ",
"| |___ ",
"|_____|",
}),
({
"┌─┐    ",
"│↑│    ",
"│││    ",
"│││    ",
"││└─┐",
"│└─→│",
"└───┘",
}),
({
"┌┐    ",
"││    ",
"││    ",
"└──┘",
}),
	}), // end l
	"m" : ({
({
"█┐    █┐",
"██┐██│",
"█┌█┌█│",
"█│└┘█│",
"█│    █│",
"└┘    └┘",
}),
({
"    __  ___",
"   /  |/  /",
"  / /|_/ / ",
" / /  / /  ",
"/_/  /_/   ",
}),
({
"            ",
"   ____ ___ ",
"  / __ `__ \\",
" / / / / / /",
"/_/ /_/ /_/ ",
}),
({
"╭━┳━╮",
"┃  ┃  ┃",
"┃  ┃  ┃",
"┃  ┃  ┃",
"┃  ┃  ┃",
"┻  ┻  ┻",
}),/*
({
"  ____        ____  ",
"╱  ╱╲    ╱  ╱▏",
"██◣  ╲◢██  ▏",
"███◣◢███  ▏",
"████████  ▏",
"██◥██◤██  ▏",
"██▕◥◤  ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██╱      ██╱  ",
}),
({
"    ____    ____    ",
"  ╱  ╱╲╱  ╱╲  ",
"◢██◣◢██◣╱▏",
"████████  ▏",
"██  ██  ██  ▏",
"██  ██  ██  ▏",
"██  ██  ██  ▏",
"██  ██  ██  ▏",
"██╱██╱██╱  ",
}),*/
({
"┌┌│",
"│││",
"┘┘┘",
}),
({
" __  __ ",
"|  \\/  |",
"| |\\/| |",
"| |  | |",
"|_|  |_|",
}),
({
" _ __ ___  ",
"| '_ ` _ \\ ",
"| | | | | |",
"|_| |_| |_|",
}),
({
"╭────╮",
"│        │",
"│╭╮╭╮│",
"││☆☆││",
"││││││",
"││││││",
"└╯╰╯╰┘",
}),
	}), // end m
	"n" : ({
({
"█┐    █┐",
"██┐  █│",
"█┌█┐█│",
"█│└██│",
"█│  └█│",
"└┘    └┘",
}),/*
({
"  ____          ____  ",
"╱  ╱▏      ╱  ╱▏",
"██╱╲      ██  ▏",
"██◣  ╲    ██  ▏",
"███◣  ╲  ██  ▏",
"████◣  ╲██  ▏",
"██◥██◣  ██  ▏",
"██▕◥██◣██  ▏",
"██  ▏◥████  ▏",
"██  ▏  ◥███  ▏",
"██  ▏    ◥██  ▏",
"██╱        ██╱  ",
}),*/
({
"    _   __",
"   / | / /",
"  /  |/ / ",
" / /|  /  ",
"/_/ |_/   ",
}),
({
"        ",
"   ____ ",
"  / __ \\",
" / / / /",
"/_/ /_/ ",
}),
({
"┏╮    ┳",
"┃ \\    ┃",
"┃  \\   ┃",
"┃   \\  ┃",
"┃    \\ ┃",
"┻    ╰┛",
}),
({
"┌  │",
"│＼│",
"┘  ┘",
}),
({
" _   _ ",
"| \\ | |",
"|  \\| |",
"| |\\  |",
"|_| \\_|",
}),
({
" _ __  ",
"| '_ \\ ",
"| | | |",
"|_| |_|",
}),
	}), // end n
/*	"o" : ({
({
"  ███┐  ",
"█┌──█┐",
"█│    █│",
"█│    █│",
"└███┌┘",
"  └──┘  ",
}),
({
"   ____ ",
"  / __ \\",
" / / / /",
"/ /_/ / ",
"\\____/  ",
}),
({
"      ______      ",
"    ╱    ╱╲    ",
"  ◢███◣  ╲  ",
"◢█████◣╱▏",
"██◤▏◥██  ▏",
"██  ▏  ██  ▏",
"██  ▏  ██  ▏",
"██  ▏  ██  ▏",
"██╱╲__██  ▏",
"██◣╱◢██╱  ",
"◥█████◤    ",
"  ◥███◤      ",
}),
	}), // end o*/
	"p" : ({
({
"████┐  ",
"█┌──█┐",
"████┌┘",
"█┌──┘  ",
"█│        ",
"└┘        ",
}),
({
"    ____ ",
"   / __ \\",
"  / /_/ /",
" / ____/ ",
"/_/      ",
}),
({
"    ____ ",
"   / __ \\",
"  / /_/ /",
" / .___/ ",
"/_/      ",
}),
({
"╭━━━╮",
"┃      ┃",
"┣━━━╯",
"┃        ",
"┃        ",
"┻        ",
}),/*
({
"  ____________    ",
"╱          ╱╲  ",
"██████◣╱▏",
"███████  ▏",
"██  ▏  ██  ▏",
"██╱▔▔██  ▏",
"███████╱  ",
"██████◤    ",
"██  ▏          ",
"██  ▏          ",
"██  ▏          ",
"██╱            ",
}),
({
"  ________      ",
"╱      ╱╲    ",
"████◣  ╲  ",
"█████◣╱▏",
"██▕◥██  ▏",
"██  ▏██  ▏",
"██╱◢██╱  ",
"█████◤    ",
"████◤      ",
"██  ▏        ",
"██╱          ",
}),*/
({
"╭──╮",
"│ ○ │",
"│╭─╯",
"╰╯    ",
}),
({
" ____  ",
"|  _ \\ ",
"| |_) |",
"|  __/ ",
"|_|    ",
}),
({
" _ __  ",
"| '_ \\ ",
"| |_) |",
"| .__/ ",
"|_|    ",
}),
({
"┌───╮",
"│↖↑↗│",
"│←☆→│",
"│∕↓↘│",
"││┌─╯",
"│↓│    ",
"└─┘    ",
}),
({
"┳┓  ",
"┣┛  ",
"┛    ",
}),
	}), // end p
	"q" : ({
({
"  ███┐  ",
"█┌──█┐",
"█│█┐█│",
"█│└█┌┘",
"└██┌█┐",
"  └─┘└┘",
}),
({
"   ____ ",
"  / __ \\",
" / / / /",
"/ /_/ / ",
"\\___\\_\\ ",
}),
({
"╭━━━╮ ",
"┃      ┃ ",
"┃      ┃ ",
"┃      ┃ ",
"┃     \\┃ ",
"╰━━━\\__",
}),/*
({
"      ______        ",
"    ╱    ╱╲      ",
"  ◢███◣  ╲    ",
"◢█████◣╱▏  ",
"██◤▏◥██  ▏  ",
"██  ▏  ██  ▏  ",
"██  ▏  ██  ▏  ",
"██  ▏  ██  ▏  ",
"██╱╲__██▕__  ",
"██◣╱◢██╱╱▏",
"◥███████  ▏",
"  ◥███◤◥█╱  ",
}),*/
({
"  ___  ",
" / _ \\ ",
"| | | |",
"| |_| |",
" \\__\\_\\",
}),
	}), // end q
	"r" : ({
({
"████┐  ",
"█┌──█┐",
"████┌┘",
"█┌█┌┘  ",
"█│└██┐",
"└┘  └─┘",
}),
({
"    ____ ",
"   / __ \\",
"  / /_/ /",
" / _, _/ ",
"/_/ |_|  ",
}),
({
"╭━━━╮",
"┃      ┃",
"┣━┳━╯",
"┃   \\    ",
"┃    \\   ",
"┻     \\__",
}),/*
({
"  ____________      ",
"╱          ╱╲    ",
"██████◣╱▏  ",
"███████  ▏  ",
"██  ▏__██  ▏  ",
"██╱▔◢██╱    ",
"██████◤      ",
"█████◤╲      ",
"██◥██◣  ╲    ",
"██▕◥██◣  ╲  ",
"██  ▏◥██◣╱▏",
"██╱    ◥██╱  ",
}),*/
({
" ____  ",
"|  _ \\ ",
"| |_) |",
"|  _ < ",
"|_| \\_\\",
}),
	}), // end r
	"s" : ({
({
"  ████┐",
"█┌───┘",
"└███┐  ",
"  └──█┐",
"████┌┘",
"└───┘  ",
}),
({
"   _____",
"  / ___/",
"  \\__ \\ ",
" ___/ / ",
"/____/  ",
}),/*
({
"      ______      ",
"    ╱    ╱╲    ",
"  ◢███◣  ╲  ",
"◢█████◣╱▏",
"██◤╲◥██╱  ",
"██◣╱￣╱╲    ",
"◥████◣  ╲  ",
"  ◥████◣╱▏",
"╱￣╱╲◥██  ▏",
"██◣╱◢██╱  ",
"◥█████◤    ",
"  ◥███◤      ",
}),*/
({
" ____  ",
"/ ___| ",
"\\___ \\ ",
" ___) |",
"|____/ ",
}),
	}), // end s
	"t" : ({
({
"┌┬┬┐",
"  ││  ",
"  ││  ",
"  ││  ",
"　└┘　",
"        ",
}),
({
"█████┐",
"    █┌─┘",
"    █│    ",
"    █│    ",
"    █│    ",
"    └┘    ",
}),
({
"  ______",
" /_  __/",
"  / /   ",
" / /    ",
"/_/     ",
}),
({
"╭┬╮",
"  │  ",
"  ╰  ",
"      ",
}),
({
"┏━┳━┓",
"    ┃    ",
"    ┃    ",
"    ┃    ",
"    ┃    ",
"    ┻    ",
}),/*
({
"  ________________  ",
"╱              ╱▏",
"████████  ▏",
"████████╱  ",
"      ██  ▏      ",
"      ██  ▏      ",
"      ██  ▏      ",
"      ██  ▏      ",
"      ██  ▏      ",
"      ██  ▏      ",
"      ██  ▏      ",
"      ██╱        ",
}),
({
"  ____      ",
"╱  ╱▏    ",
"██▕____  ",
"██    ╱▏",
"████  ▏",
"████╱  ",
"██  ▏    ",
"██  ▏    ",
"██  ▏__  ",
"██╱￣╱▏",
"████  ▏",
"◥███╱  ",
}),*/
({
"╭──╮",
"╰╮╭╯",
"  ││  ",
"  ╰╯  ",
}),
({
"─┌┘",
"  │  ",
"  ┘  ",
}),
({
" _____ ",
"|_   _|",
"  | |  ",
"  | |  ",
"  |_|  ",
}),
({
"┌───┐",
"│←┬→│",
"└┐│┌┘",
"  │☆│  ",
"  │││  ",
"  │↓│  ",
"  └─┘  ",
}),
({
"┌──┐",
"└┐┌┘",
"  ││  ",
"　└┘　 ",
}),
({
"  ╋  ",
"  ┗  ",
}),
	}), // end t
	"u" : ({
({
"█┐    █┐",
"█│    █│",
"█│    █│",
"█│    █│",
"└███┌┘",
"  └──┘  ",
}),
({
"   __  __",
"  / / / /",
" / / / / ",
"/ /_/ /  ",
"\\____/   ",
}),
({
"┳      ┳",
"┃      ┃",
"┃      ┃",
"┃      ┃",
"┃      ┃",
"╰━━━╯",
}),/*
({
"  ____        ____  ",
"╱  ╱▏    ╱  ╱▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██╱╲____██  ▏",
"██◣╱  ◢██╱  ",
"◥██████◤    ",
"  ◥████◤      ",
}),*/
	}), // end u
	"v" : ({
({
"█┐    █┐",
"█│    █│",
"█│    █│",
"└█┐█┌┘",
"  └█┌┘  ",
"    └┘    ",
}),
({
" _    __",
"| |  / /",
"| | / / ",
"| |/ /  ",
"|___/   ",
}),
({
"       ",
" _   __",
"| | / /",
"| |/ / ",
"|___/  ",
}),
({
"┳      ┳",
"┃      ┃",
" \\      / ",
"  \\    /  ",
"   \\  /   ",
"    \\/    ",
}),/*
({
"  ____      ____  ",
"╱  ╱▏  ╱  ╱▏",
"██  ▏  ██  ▏",
"██  ▏  ██  ▏",
"██  ▏  ██  ▏",
"██╱╲__██  ▏",
"██◣╱◢██╱  ",
"◥█████◤    ",
"  ◥███◤      ",
"    ◥█◤        ",
}),*/
({
"__     __",
"\\ \\   / /",
" \\ \\ / / ",
"  \\ V /  ",
"   \\_/   ",
}),
({
"__   __",
"\\ \\ / /",
" \\ V / ",
"  \\_/  ",
"       ",
}),
	}), // end v
	"w" : ({
({
"█┐    █┐",
"█│    █│",
"█│█┐█│",
"██┌██│",
"█┌┘└█│",
"└┘    └┘",
}),
({
" _       __",
"| |     / /",
"| | /| / / ",
"| |/ |/ /  ",
"|__/|__/   ",
}),
({
"          ",
" _      __",
"| | /| / /",
"| |/ |/ / ",
"|__/|__/  ",
}),
({
"┳  ┳  ┳",
"┃  ┃  ┃",
"┃  ┃  ┃",
"┃  /\\  ┃",
"┃ /  \\ ┃",
"┗╯  ╰┛",
}),/*
({
"  ____        ____  ",
"╱  ╱▏    ╱  ╱▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏╱╲██  ▏",
"██▕◢◣  ██  ▏",
"██◢██◣██  ▏",
"████████  ▏",
"███◤◥███  ▏",
"██◤    ◥██╱  ",
}),
({
"  ____        ____  ",
"╱  ╱▏    ╱  ╱▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██  ▏    ██  ▏",
"██╱╲╱╲██  ▏",
"██◣◢◣◢██╱  ",
"◥██████◤    ",
"  ◥████◤      ",
"    ◥◤◥◤        ",
}),*/
({
"__        __",
"\\ \\      / /",
" \\ \\ /\\ / / ",
"  \\ V  V /  ",
"   \\_/\\_/   ",
}),
({
"__      __",
"\\ \\ /\\ / /",
" \\ V  V / ",
"  \\_/\\_/  ",
}),
({
"┌╮╭╮╭┐",
"││││││",
"││││││",
"││☆☆││",
"│╰╯╰╯│",
"│        │",
"╰────╯",
}),
({
"┓┓┏",
"┗┻┛",
}),
	}), // end w
	"x" : ({
({
"█┐    █┐",
"└█┐█┌┘",
"  └█┌┘  ",
"  █┌█┐  ",
"█┌┘└█┐",
"└┘    └┘",
}),
({
"   _  __",
"  | |/ /",
"  |   / ",
" /   |  ",
"/_/|_|  ",
}),
({
"        ",
"   _  __",
"  | |/_/",
" _>  <  ",
"/_/|_|  ",
}),
({
"╭╮╮",
"╭┼╯",
"╰╰╯",
"      ",
}),
({
"┳      ┳",
" ╲    ╱ ",
"   ╲╱   ",
"   ╱╲   ",
" ╱    ╲ ",
"┻      ┻",
}),/*
({
"  ________        ________  ",
"╱      ╱▏    ╱      ╱▏",
"████╱      ████╱  ",
"  ◥█◣  ╲    ◢█◤      ",
"    ◥█◣  ╲◢█◤        ",
"      ◥█◣◢█◤          ",
"        ◥██◤╲          ",
"        ◢██◣  ╲        ",
"      ◢█◤◥█◣  ╲      ",
"  __◢█◤    ◥█◣  ╲__  ",
"╱◢█◤╱▏    ◥█◣╱╱▏",
"████╱      ████╱  ",
}),
({
"  ____        ____  ",
"╱  ╱╲    ╱  ╱  ",
"◥█◣  ╲◢█◤    ",
"  ◥█◣◢█◤      ",
"    ◥██◤╲      ",
"    ◢██◣  ╲    ",
"  ◢█◤◥█◣  ╲  ",
"◢█◤    ◥█◣╱▏",
"█◤        ◥█╱  ",
}),*/
({
"__  __",
"\\ \\/ /",
" \\  / ",
" /  \\ ",
"/_/\\_\\",
}),
({
"__  __",
"\\ \\/ /",
" >  < ",
"/_/\\_\\",
}),
({
"┌┐┌┐",
" ＼∨／ ",
" ／∧＼ ",
"└┘└┘",
}),
({
"╭╮╭╮",
"╰╰╯╯",
"╭╭╮╮",
"╰╯╰╯",
}),
	}), // end x
	"y" : ({
({
"█┐    █┐",
"└█┐█┌┘",
"  └█┌┘  ",
"    █│    ",
"    █│    ",
"    └┘    ",
}),
({
"__  __",
"\\ \\/ /",
" \\  / ",
" / /  ",
"/_/   ",
}),
({
"┳      ┳",
"┃      ┃",
"╰━┳━╯",
"    ┃    ",
"    ┃    ",
"    ┻    ",
}),/*
({
"  ________        ________  ",
"╱      ╱▏    ╱      ╱▏",
"████╱      ████╱  ",
"  ◥█◣  ╲    ◢█◤      ",
"    ◥█◣  ╲◢█◤        ",
"      ◥█◣◢█◤          ",
"        ◥██◤▏          ",
"          ██  ▏          ",
"          ██  ▏          ",
"          ██  ▏          ",
"        ╱██╱╱▏        ",
"        ████╱          ",
}),
({
"  ____    ____  ",
"╱  ╱▏╱  ╱▏",
"██  ▏██  ▏",
"██  ▏██  ▏",
"██╱￣██  ▏",
"██████  ▏",
"◥█████  ▏",
"╱      ██  ▏",
"██████╱  ",
"◥████◤    ",
}),*/
({
"│  │",
"─┌┘",
"  ┘  ",
}),
({
"__   __",
"\\ \\ / /",
" \\ V / ",
"  | |  ",
"  |_|  ",
}),
({
" _   _ ",
"| | | |",
"| |_| |",
" \\__, |",
" |___/ ",
}),
({
"┌─┐─┐",
"│↖│↗│",
"│  │  │",
"╰╮☆╭╯",
"  │││  ",
"  │↓│  ",
"  └─┘  ",
}),
({
"┌┐┌┐",
" ＼∨／ ",
"  ││  ",
"  └┘  ",
}),
({
" ┓┓ ",
" ┗┫ ",
" ┗┛ ",
}),
	}), // end y
	"z" : ({
({
"█████┐",
"      █┌┘",
"    █┌┘  ",
"  █┌┘    ",
"█████┐",
"└────┘",
}),
({
" _____",
"/__  /",
"  / / ",
" / /__",
"/____/",
}),
({
"┣━━━┓",
"       ╱ ",
"     ╱   ",
"   ╱     ",
" ╱       ",
"┗━━━┫",
}),/*
({
"  ______________  ",
"╱            ╱▏",
"███████  ▏",
"███████  ▏",
"        ◢██╱  ",
"      ◢██◤    ",
"    ◢██◤      ",
"  ◢██◤        ",
"◢██◤________  ",
"██◤▔      ╱▏",
"███████  ▏",
"███████╱  ",
}),*/
({
" _____",
"|__  /",
"  / / ",
" / /_ ",
"/____|",
}),
	}), // end z
	]);// end all

	return all[num][random(sizeof(all[num]))];
}
string filter_color(string arg)
{
  if(!arg) return "";
  arg = replace_string(arg, BLK, "");
  arg = replace_string(arg, RED, "");
  arg = replace_string(arg, GRN, "");
  arg = replace_string(arg, YEL, "");
  arg = replace_string(arg, BLU, "");
  arg = replace_string(arg, MAG, "");
  arg = replace_string(arg, CYN, "");
  arg = replace_string(arg, WHT, "");
  arg = replace_string(arg, HIR, "");
  arg = replace_string(arg, HIG, "");
  arg = replace_string(arg, HIY, "");
  arg = replace_string(arg, HIB, "");
  arg = replace_string(arg, HIM, "");
  arg = replace_string(arg, HIC, "");
  arg = replace_string(arg, HIW, "");
  arg = replace_string(arg, NOR, "");
/*  arg = replace_string(arg, BBLK, "");
  arg = replace_string(arg, BRED, "");
  arg = replace_string(arg, BGRN, "");
  arg = replace_string(arg, BYEL, "");
  arg = replace_string(arg, BBLU, "");
  arg = replace_string(arg, BMAG, "");
  arg = replace_string(arg, BCYN, "");
  arg = replace_string(arg, HBRED, "");
  arg = replace_string(arg, HBGRN, "");
  arg = replace_string(arg, HBYEL, "");
  arg = replace_string(arg, HBBLU, "");
  arg = replace_string(arg, HBMAG, "");
  arg = replace_string(arg, HBCYN, "");
  arg = replace_string(arg, HBWHT, "");
  arg = replace_string(arg, NOR, "");
*/
  return arg;
}