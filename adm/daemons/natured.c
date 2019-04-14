// natured.c
// Last Modified by Winder on Aug. 25 2001

#include <ansi.h>
// #define TIME_TICK ((time()-1270000000)*60)
//#define TIME_TICK ((time()-1111000000)*365)//现实一秒mud365秒
					   //现实一天mud365天(一年)
#define TIME_TICK ((time()%(60*24*3600))*365)//mud中60年一轮=现实中60天
static int current_day_phase;
mapping *day_phase;

//飞贼任务与隐士任务的标识
int thief_yinshi = 3;

string *weather_msg = ({
	"天空中万里无云",
	"几朵淡淡的云彩妆点著清朗的天空",
	"白云在天空中飘来飘去",
	"厚厚的云层堆积在天边",
	"天空中乌云密布",
});

mapping *read_table(string file);
void init_day_phase();

void create()
{
	day_phase = read_table("/adm/etc/nature/day_phase");
	init_day_phase();
}

void init_day_phase()
{
	mixed *local;
	int i, t;

	// Get minutes of today.
	local = localtime(TIME_TICK);
	t = local[2] * 60 + local[1];
	// hour * 60 + minutes

	// Find the day phase for now.
	for( i=0; i < sizeof(day_phase); i++)
		if( t >= day_phase[i]["length"] )
			t -= (int)day_phase[i]["length"];
		else break;

	current_day_phase = (i==0? sizeof(day_phase)-1: i - 1);
	current_day_phase = (i==0? sizeof(day_phase)-1: i - 1);
	// MUD 运行时间久了，时间会有偏差，这里是调整程序，每小时执行一次
	message("channel:sys", HIR"【系统】泥巴时间对齐系统时间，一小时一次。\n"NOR, users());
	remove_call_out("init_day_phase");
	call_out("init_day_phase", 3600);

	// Since in our time scale, 1 minute == 1 second in RL, so we don't need
	// any conversion before using this number as call_out dalay, if you
	// changed the time scale, be sure to convert it.

	call_out("update_day_phase", (int)day_phase[(current_day_phase+1) % sizeof(day_phase)]["length"]-t);
}

void update_day_phase()
{
	remove_call_out("update_day_phase");

	current_day_phase = (++current_day_phase) % sizeof(day_phase);
	message("outdoor:vision", HIG"【窗外】"NOR + day_phase[current_day_phase]["time_msg"] + NOR"。\n", users());
	if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);

	call_out("update_day_phase", day_phase[current_day_phase]["length"]);
}
void event_midnight()
{
	string get_month, get_day;
	get_day = CHINESE_D->chinese_monthday(TIME_TICK);
	get_month = CHINESE_D->chinese_month(TIME_TICK);
	switch(get_month)
	{
		//spring weather
		case "三":
		case "四":
		case "五":
			switch(random(3))
			{
			case 0:
				day_phase = read_table("/adm/etc/nature/spring_rain"); break;
			case 1:
				day_phase = read_table("/adm/etc/nature/spring_sun"); break;
			case 2:
				day_phase = read_table("/adm/etc/nature/spring_wind"); break;
			}
			break;
		//summer weather
		case "六":
		case "七":
		case "八":
			switch(random(3))
			{
			case 0:
				day_phase = read_table("/adm/etc/nature/summer_rain"); break;
			case 1:
				day_phase = read_table("/adm/etc/nature/summer_sun"); break;
			case 2:
				day_phase = read_table("/adm/etc/nature/summer_wind"); break;
			}
			break;
		//autumn weather
		case "九":
		case "十":
		case "十一":
			switch(random(3))
			{
			case 0:
				day_phase = read_table("/adm/etc/nature/autumn_rain"); break;
			case 1:
				day_phase = read_table("/adm/etc/nature/autumn_sun"); break;
			case 2:
				day_phase = read_table("/adm/etc/nature/autumn_wind"); break;
			}
			break;
		//winter weather
		case "十二":
		case "一":
		case "二":
			switch(random(3))
			{
			case 0:
				day_phase = read_table("/adm/etc/nature/winter_rain"); break;
			case 1:
				day_phase = read_table("/adm/etc/nature/winter_sun"); break;
			case 2:
				day_phase = read_table("/adm/etc/nature/winter_wind"); break;
			}
			break;
		default:
			day_phase = read_table("/adm/etc/nature/day_phase");
	}
}

object create_thief( )
{
	mapping skill_status,name;
	string *sname;	
	object obj;
	int skilllvl,topexp;
	int i;
	
	seteuid(getuid());
	if (thief_yinshi==0)	obj = new("/clone/quest/questfeizei");
	if (thief_yinshi==1)	obj = new("/clone/quest/questyinshi");
	if (random(2) == 0)
	{
	        if (thief_yinshi==1) name = NAME_D->woman_name();
		obj->set("gender", "女性");
	}
	else
	{
		if (thief_yinshi==1) name = NAME_D->man_name();
		obj->set("gender", "男性");
	}
        if (thief_yinshi==1) obj->set("fname", name["name"]);
/* skilllvl && exp for 飞贼 */    
     if (thief_yinshi==0)
        {
       	   i=random(5);
           if( i==0 )   
	       { topexp = 500000+random(500000);
                 skilllvl=100+random(50);
                 obj->set("str_lvl",1);
                } 
           else if( i==1 )   
	       { topexp = 1000000+random(1000000);
                 skilllvl=150+random(75);
                 obj->set("str_lvl",2);
                }          
           else if( i==2 )   
	       { topexp = 3000000+random(3000000);
                 skilllvl=200+random(100);
                 obj->set("str_lvl",3);
                }    
            else if( i==3 )   
	       { topexp = 5000000+random(5000000);
                 skilllvl=250+random(125);
                 obj->set("str_lvl",4);
                }  
             else if( i==4 )   
	       { topexp = 8000000+random(8000000);
                 skilllvl=300+random(150);
                 obj->set("str_lvl",5);
                }                        
         }
/* skilllvl && exp for 隐士*/
      if (thief_yinshi==1)
          { 
            skilllvl=250;
            topexp=3000000;            		
	   }          
            
      	obj->set("combat_exp", topexp); 
	NPC_D->copy_skill(obj);
 	if (mapp(skill_status = obj->query_skills()))
 	{
 		sname = keys(skill_status);
 		for(i=0;i<sizeof(skill_status);i++)
 		{
 			obj->set_skill(sname[i],skilllvl);
 		}
 	}
	return obj;
}
void event_morning()
{
	string *dir, *file, place;
	object yinshi;
	object room;
	int i,j,flag=0;

        thief_yinshi=1;
        yinshi=create_thief();
//选择地点
	dir = get_dir("/d/");
	i = random(sizeof(dir));
	file = get_dir("/d/"+dir[i]+"/");
	j = random(sizeof(file));
	if(  	file[j][<2..<1]!=".c" ||
		dir[i]=="death" ||
		dir[i]=="wizard" ||
		dir[i]=="working" ||
		dir[i]=="binghuo" ||
		dir[i]=="xiakedao" ||
		dir[i]=="npc" )
	     {
		    dir[i]="wuyi";
	    	    file[j]="sangufeng";
		    room = load_object("/d/wuyi/sangufeng");
	      }
   if(!objectp(room) && !( room = find_object("/d/"+dir[i]+"/"+file[j]) ))
		room = load_object("/d/"+dir[i]+"/"+file[j]);
	 if (room->query_max_encumbrance() < 10000000)
	 {
	 	dir[i]="wuyi";
	 	file[j]="sangufeng";
	  room = load_object("/d/wuyi/sangufeng");
	}
	yinshi->move(room);
	CHANNEL_D->do_channel(yinshi, "sys",yinshi->query("name")+"在"+room->query("short")+"(/d/"+dir[i]+"/"+file[j]+")。\n");	        				
        message("channel:snow", HIY"【江湖传闻】"HIC + "听说在"+ to_chinese(dir[i]) + "一带隐居着一位武林前辈，江湖人士纷纷前往寻访！\n"NOR,users() );
//还原标识
	thief_yinshi=3;              
}

void event_afternoon()
{       
	object *ob_list;
	int i;
	ob_list = children("/clone/quest/questyinshi");
                for(i=0; i<sizeof(ob_list); i++) 
		if(environment(ob_list[i]))
		{
			message_vision("$N笑道：天要黑了，我也该走啦！\n",ob_list[i]);
			destruct(ob_list[i]);
                }
}
	
void event_night()
{
	object badguy;
	object room;
	int num;
	num=random(15);
	thief_yinshi=0;
        if ( num == 0)
        {
		if(objectp(room=load_object("/d/city/shilijie4")))
		 badguy= create_thief();
		 badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "扬州城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
        else if ( num == 1)
        {
		if(objectp(room=load_object("/d/beijing/tian_anm")))
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "北京城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
        else if ( num == 2)
        {
		if(objectp(room=load_object("/d/changan/center")))
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "长安城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 3)
        {
		if(objectp(room=load_object("/d/fuzhou/dongjiekou")))
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "福州城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 4)
        {
		if(objectp(room=load_object("/d/quanzhou/guangchang")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "泉州城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 5)
        {
		if(objectp(room=load_object("/d/suzhou/baodaiqiao")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "苏州城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 6)
        {
		if(objectp(room=load_object("/d/hangzhou/jujingyuan")) )
		badguy= create_thief();
		badguy->move(room);		
		message("channel:snow", HIM"【官府通告】"HIR + "杭州城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 7)
        {
		if(objectp(room=load_object("/d/wuxi/guangchang")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "无锡城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
        else if ( num == 8)
        {
		if(objectp(room=load_object("/d/xiangyang/guangchang")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "襄阳城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 9)
        {
		if(objectp(room=load_object("/d/yueyang/zhongxin")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "岳阳城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 10)
        {
		if(objectp(room=load_object("/d/chengdu/guangchang")))
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "成都城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
         else if ( num == 11)
        {
		if(objectp(room=load_object("/d/dali/center")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "大理城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
        }
        else if ( num == 12)
        {
		if(objectp(room=load_object("/d/lingzhou/center")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "灵州城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
	}
       else if ( num == 13)
        {
		if(objectp(room=load_object("/d/foshan/street3")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "佛山镇中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
        }
       else 
        {
		if(objectp(room=load_object("/d/jiangling/xijie2")) )
		badguy= create_thief();
		badguy->move(room);
		message("channel:snow", HIM"【官府通告】"HIR + "江陵城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！\n"NOR,users() );
         }
//还原标识
       thief_yinshi=3;
}

void event_dawn()
{
	object *ob_list;
	int i;
	ob_list = children("/clone/quest/questfeizei");
                for(i=0; i<sizeof(ob_list); i++) 
		if(environment(ob_list[i]))
		{
			message_vision("$N笑道：天亮了，东西也到手了，我闪！\n",ob_list[i]);
			destruct(ob_list[i]);
                }
}
// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase

void event_noon()
{
	object *ob;
	int i, skill,con,con1,con2,con3;
	string get_month,ill,msg;
	get_month = CHINESE_D->chinese_month(TIME_TICK);
	switch(get_month)
	{
		case "三":
		case "四":
		case "五":
			ill = "ill_kesou";
			msg = HIG"忽然喉头一阵痕痒，你感觉似乎要咳嗽了。\n"NOR;
			break;
		case "六":
		case "七":
		case "八":
			ill = "ill_zhongshu";
			msg = HIG"突然你胸臆之间一阵翻腾，你中暑了。\n"NOR;
			break;
		case "九":
		case "十":
		case "十一":
			ill = "ill_shanghan";
			msg = HIG"陡的你打了个冷战，头昏沉沉的，你得伤寒病了。\n"NOR;
			break;
		case "十二":
		case "一":
		case "二":
			ill = "ill_dongshang";
			msg = HIG"你肢体末端一阵僵直，看来你被冻伤了。\n"NOR;
			break;
	}
	if(random(2))
	{
		ill = "ill_fashao";
		msg = HIG"你偶感风寒，竟而发起烧来。\n"NOR;
	}
	ob = users();
	for(i=0; i<sizeof(ob); i++)
	{
		if( !environment(ob[i]) ) continue;
		if( !environment(ob[i])->query("outdoors") ) continue;
		if( ob[i]->query("age")==14 ) continue;
		con1 = ob[i]->query("qi");
		con2 = ob[i]->query("max_qi");
		(int)con = con1/con2*50;//形成第一个生病判断条件
		con3 = ob[i]->query("neili");
		con2 = ob[i]->query("max_neili");
		if( con2 == 0) con2 = 1;
		(int)con1 = con3/con2*50;//形成第二个生病判断条件
		if(random(con)+random(50)+random(con1)<25)
		{
			ob[i]->apply_condition(ill, 10+random(40));
			tell_object(ob[i], msg);
		}
	}
}

string outdoor_room_description()
{
	return "    "+day_phase[current_day_phase]["desc_msg"]+NOR"。\n";
}
string outdoor_room_event()
{
	return day_phase[current_day_phase]["event_fun"];
}
string game_time()
{
	return CHINESE_D->chinese_date(TIME_TICK);
}

mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i=0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !pointerp(field) ) {
			field = explode( line[i], ":" );
			continue;
		}
		if( !pointerp(format) ) {
			format = explode( line[i], ":" );
			continue;
		}
		break;
	}

	for( rn = 0, fn = 0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !fn ) data += ({ allocate_mapping(sizeof(field)) });
		sscanf( line[i], format[fn], data[rn][field[fn]] );
		fn = (++fn) % sizeof(field);
		if( !fn ) ++rn;
	}
	return data;
}

mapping *query_day_phase() { return day_phase; }

