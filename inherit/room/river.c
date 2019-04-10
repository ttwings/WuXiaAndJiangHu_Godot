//   feature/bank.c 
#include <ansi.h>
int do_cross();
int do_yell(string arg);
void check_trigger();
void on_board(object boat,string from,string to);
void arrive(object boat,string from,string to);
object find_boat(string from,string to);

#define BOAT "/clone/misc/boat"

inherit ROOM;
void create()
{
	set("short","岸边");
	set("long",@long
这是一条河的边上，可以坐船到对岸。如果轻功够好，
也可以自己施展轻功过河。
long
);
	set("yell_about", "船家");             // yell 船家
	set("river_type", "江");               // 江面上传来回响
  set("need_dodge",300);                 // 需要多少轻功
  set("busy_msg",				"只听得江面上隐隐传来：“别急嘛，这儿正忙着呐……\n");
  set("come_msg_out",		"一叶扁舟缓缓地驶了过来，艄公将一块踏脚板搭上堤岸，以便乘客上下。\n");
	set("come_msg_in",		"艄公说“到啦，上岸吧”，随即把一块踏脚板搭上堤岸。\n");
	set("wait_msg",				"岸边一只渡船上的老艄公说道：正等着你呢，上来吧。\n");
	set("leave_msg_out",	"艄公把踏脚板收了起来，竹篙一点，扁舟向江心驶去。\n");
	set("leave_msg_in",		"艄公把踏脚板收起来，说了一声“坐稳喽”，竹篙一点，扁舟向江心驶去。\n");
  set("item_desc/river", HIC "\n只见近岸处有一叶小舟，也许大声喊("
                         HIY "yell" HIC ")一声船家(" HIY "boat" HIC
                        ")就\n能听见。倘若你自负轻功绝佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏江而过。\n" NOR);
	set("boat_short", "渡船");		
	set("boat_desc",  @LONG
一叶小舟，最多也就能载七、八个人。一名六十多岁的老艄公手持
长竹篙，正在船尾吃力地撑着船。
LONG);																	 // 渡船上的描述
	set("from",       file_name(this_object()));      // 这趟船的起点
	set("to",         __DIR__"hanshui2");  // 船的终点 /*   必选   */
	setup();
}

void init()
{
	add_action("do_yell","yell");
	add_action("do_cross","cross");
}

int do_cross()
{
        object me, arrive;
        string msg;
        string go_msg;
        string come_msg;
        int can = 0;
        int need=query("need_dodge");
        string dskill;

        me = this_player();
        arrive = find_object(query("to"));
        if (! arrive)
                arrive = load_object(query("to"));
        if (! arrive)
        {
                tell_object(me, "你举目望去，发现水面雾气极浓，什么都看不清。\n");
                return 1;
        }
        if (! me->query_skill("dodge", 1))
        {
                tell_object(me, "你大眼一瞪？干什么，跳河自杀么？\n");
                return 1;
        }
        dskill = me->query_skill_mapped("dodge");
        
				if (me->query_skill("king-of-dragon",1) > 0)
        {
        	can = 1;
        	go_msg   = SKILL_D("king-of-dragon")->river_go_msg();
        	come_msg = SKILL_D("king-of-dragon")->river_come_msg();
        }        
        else if (dskill && ( me->query_skill(dskill,1) * (SKILL_D(dskill)->river_point()) >= need ) )
        {
        	can = 1;
        	go_msg   = SKILL_D(dskill)->river_go_msg();
        	come_msg = SKILL_D(dskill)->river_come_msg();
        }
        else if (me->query_skill("dodge",1) >= need )
        {
        	can = 1;
        }        
        if (can != 1) 
        {
        	tell_object(me, "你掂量了一下，觉得自己的轻功似乎还没练到家。\n");
        	return 1;
        }
        if (me->query("neili") < 300)
        {
                tell_object(me, "你的内力不够，还是先休息一下吧。\n");
                return 1;
        }
        if (!stringp(go_msg))
        	go_msg = HIW "\n只见$N" HIW "身形微微一晃，已然飘出丈许，以"
                "足尖轻点水面向对岸踏波掠去，漾起层层微澜。\n身形洋洋"
                  "洒洒，若彩蝶飞扬，甚是逍遥。便在众人惊叹轻功绝妙间"
                 "，早已没了踪影。\n\n" NOR;
        if (!stringp(come_msg))
          come_msg = HIW "\n忽见水面上雾气散开，一人踏波"
                          "逐浪，竟大踏步掠过江来！\n\n" NOR;

        me->add("neili", -200);
        message_vision(go_msg, me);
        me->move(arrive);
        come_msg = replace_string(come_msg,"$N",me->name());
        tell_room(environment(me), come_msg , ({ me }));
        return 1;
}

int do_yell(string arg)
{
	string dir;

	if( !arg || arg=="" ) return 0;

	if( arg=="boat" ) arg = query("yell_about");
	if( (int)this_player()->query("age") < 16 )
		message_vision("$N使出吃奶的力气喊了一声：“" + arg + "”\n",this_player());
	else if( (int)this_player()->query("neili") > 500 )
		message_vision("$N吸了口气，一声“" + arg +"”，声音中正平和地远远传了出去。\n", this_player());
	else
			message_vision("$N鼓足中气，长啸一声：“" + arg + "！”\n", this_player());
	if( arg==query("yell_about"))
		check_trigger();
	else
		message_vision(query("river_type")+"面上远远传来一阵回声：“" + arg + "～～～”\n", this_player());
	return 1;
}

void check_trigger()
{
	object boat;

	if(!query("exits/enter") )
	{
		boat = find_boat(query("from"),query("to"));
		if((int)boat->query("yell_trigger")==0 )
		{
				message("vision",query("come_msg_out"), this_object() );
				set("exits/enter", file_name(boat));
				message("vision",query("come_msg_in") , boat);
				boat->set("exits/out", file_name(this_object()));
				boat->set("yell_trigger", 1);
				remove_call_out("on_board");
				call_out("on_board", 15 , boat, file_name(this_object()),query("to"));
		}
		else
			message("vision","只听得"+query("river_type")+"面上隐隐传来：“别急嘛，这儿正忙着呐……”\n",this_object() );
	}
	else 
		message("vision",query("wait_msg"), this_object() );
}

void on_board(object boat,string from,string to) // 起航
{
	object from_room;
	int i;
	object *inv;
	
	from_room = find_object(from);
	if( !from_room || !from_room->query("exits/enter") ) return;

	message("vision", query("leave_msg_out"), from_room );
	from_room->delete("exits/enter");

	message("vision",query("leave_msg_in"), boat );
	boat->delete("exits/out");

	inv = all_inventory(boat);
	for (i=0;i<sizeof(inv);i++)
	{
		if (userp(inv[i]))
		{
				remove_call_out("arrive");
				call_out("arrive", 20 ,boat,from,to);
		    return;
		}
	}
	destruct(boat);
}

void arrive(object boat,string from,string to)//到岸
{
	object to_room;
	if (!to_room = find_object(to))
	 to_room = load_object(to);

	message("vision",query("come_msg_in"),boat );
	boat->set("exits/out", file_name(to_room));

  message("vision",query("come_msg_out"),to_room);
	to_room->set("exits/enter",file_name(boat));

  remove_call_out("on_board");
  call_out("on_board",20,boat,to,from); //到岸20秒后 从终点返回起点
}

object find_boat(string from,string to)
{
	object boat;
	object *boats;
	int i;
	boats = children(BOAT);
	for(i=0;i<sizeof(boats);i++)
	{
		if (clonep(boats[i]))
		  {
		  	if (stringp(boats[i]->query("from")) &&	boats[i]->query("from")==from) 
		  	{
		  		boat = boats[i];
		  	  return boat;
		  	}
		  	if (stringp(boats[i]->query("to")) && boats[i]->query("to") == from)
		  	{
		  		boat = boats[i];
		  		return boat;
		  	}
		  }
	}
	seteuid(getuid());
	boat = new(BOAT);
	boat->set("from",from);
	boat->set("to"  ,to  );
	boat->set("short",query("boat_short"));
	boat->set("long", query("boat_desc"));
	return boat;
}