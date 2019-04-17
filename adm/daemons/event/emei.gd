# emei.c 事件：峨嵋金顶日出
# for XKX100 , by Sir 2003.11.3

#include <ansi.h>

# 奖励
func do_bonus(room):
    var obs;
    var msg;
	var lvl
	var p_bonus
	var s_bonus;
    var r,i;

    obs = all_inventory(room);
    if (sizeof(obs) < 1):
        return;

    r = random(365);
    if (r == 0):
        msg = HIY + "【自然奇观】峨嵋佛光\n" + NOR;
        msg += HIR + "只见太阳一点一点的升了起来，倏的眼前一亮，一道光晕出现在云际，\n朦朦胧胧似乎有一个佛影立在当中，令人叹羡不已。\n" + NOR;
        msg += HIG + "你冥冥中仿佛得到了佛主的指示，登时有茅塞顿开的感觉。\n" + NOR;


        # 佛门弟子增加佛学技能
		# for ( i = 0 ; i < sizeof(obs); i++)
		for i in obs.size() :
			if( !living(obs[i]) || !userp(obs[i]) ) :
				continue;
			p_bonus = 5000 + random( 5000 );
			s_bonus = 1000 + random( 500 );
			obs[i].add("potential", p_bonus);
			obs[i].add("score",s_bonus);
			if (obs[i].query("class") == "bonze"):
				lvl = obs[i].query_skill("buddhism", 1);
				if (lvl >= 50 && lvl< 200 ):
					obs[i].set_skill("buddhism", lvl + 1);
				lvl = obs[i].query_skill("mahayana", 1);
				if ( lvl >= 50 && lvl < 200):
					obs[i].set_skill("mahayana", lvl + 1);
				lvl = obs[i].query_skill("lamaism", 1);
				if (lvl >= 50 && lvl <200 ):
					obs[i].set_skill("lamaism", lvl + 1);


        message("vision", msg, obs);
		message("channel:rumor", HIM + "【谣言】"+"听说峨嵋金顶佛光出现，令人叹为观止，赞叹不已。\n" + NOR, users());

	elif (r < 250):
		msg = HIY + "【自然奇观】峨嵋日出\n"+ NOR;
		msg +=HIG + "在峨嵋山上欣赏日出令人心旷神怡，格外领略峨嵋山的隽秀险奇。\n"+ NOR;
		
		match (random(3)):
			0:
				msg += HIY +"一轮红日跃出天际，映射得层峦叠翠分外妖娆，茫茫云海，尽披红妆。\n"+ NOR;
			1:
				msg += HIY +"忽然间一轮红日跃了上来，天地之间登时辉煌无比，只射得你眼睛都无法睁开。\n"+ NOR;
			_:
				msg += HIY +"蓦然眼前金光四射，一轮红日冉冉升起。\n"+ NOR;

        msg += HIG +"你心头闪过一道灵光，似乎受到了某种启迪。\n"+ NOR;
        
		# for ( i = 0 ; i < sizeof(obs); i++)
		for i in range(obs.size()):
			if( !living(obs[i]) || !userp(obs[i]) ) :
				continue;
			p_bonus = 500 + random( 500 );
			s_bonus = 200 + random( 200 );			
			obs[i].add("potential", p_bonus);
			obs[i].add("score", s_bonus);


        message("vision", msg, obs);

        
	else:
		match (random(3)):
			
			0:
				msg = WHT "眼见太阳朦朦胧胧的就要升上来，却见一片乌云飘过，遮了个严严实实。\n" NOR;
			1:
				msg = WHT "你眼前越来越亮，但是雾气好重，让你什么都看不清楚。\n" NOR;
			_:
				msg = WHT "天边渐渐的发白，但是一层一层的云气将日头压得光芒一丝都看不见。\n" NOR;

        msg += HIG "你心中连叹：“太可惜了！”\n" NOR;

        message("vision", msg, obs);


#事件触发
func trigger_event():
    var room;
	room = find_object("/d/emei/jinding")
    # 峨嵋金顶日出
    if (objectp(room)):
        do_bonus(room);


func create() :
	seteuid(getuid()); 
	message("channel:sys", HIR"【自然奇观】峨嵋金顶日出。\n"NOR, users());
	trigger_event();