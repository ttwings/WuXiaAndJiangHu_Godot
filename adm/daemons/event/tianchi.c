// emei.c 事件：长白山天池流星
// for XKX100 , by Sir 2003.11.3

#include <ansi.h>

// 奖励
private void do_bonus(object room)
{
        object *obs;
        string msg;
        int lvl,p_bonus,s_bonus;
        int r,i;

        obs = all_inventory(room);
        if (sizeof(obs) < 1)
                return;

        r = random(365);
        if (r == 0)
        {
        	msg = HIW "【自然奇观】天池流星雨\n"NOR;
                msg += HIC "只听天空骤然传来一阵刺耳的摩擦声，你仰望上苍，发现穹苍里已豁然出现\n"
                           "无数颗流星。夜陨如雨飞坠，锋芒划空，尔落入天池之中，又再激起万股七\n"
                           "色浪涛，漆黑夜穹竟犹如白昼一般。你不禁感叹，大自然之威，当真神鬼莫\n"
                           "测。\n" NOR;

                msg += HIG "你仔细的观察了流星雨的全过程，发现其中竟有很多奥秘可以融于武学。\n" NOR;
                
                for ( i = 0 ; i < sizeof(obs); i++)  // 增加潜能基本轻功基本暗器
                {
                	if( !living(obs[i]) || !userp(obs[i]) ) continue;                
			p_bonus = 5000 + random( 5000 );
			s_bonus = 1000 + random( 500 );
			obs[i]->add("potential", p_bonus);
			obs[i]->add("score",s_bonus);
                        
			lvl = obs[i]->query_skill("throwing", 1);
                        if (lvl >= 50 && lvl< 300 )
                               	obs[i]->set_skill("throwing", lvl + 10);
                        else if ( lvl >= 300 )
                               	obs[i]->set_skill("throwing", lvl + 1);
                                	
                        lvl = obs[i]->query_skill("dodge", 1);
                        if (lvl >= 50 && lvl< 300 )
                               	obs[i]->set_skill("sword", lvl + 10);
                        else if ( lvl >= 300 )
                               	obs[i]->set_skill("sword", lvl + 1);
                }
                
                
                message("vision", msg, obs);
                message("channel:rumor", HIM"【谣言】"+"听说长白山天池上夜空竟现流星雨，五彩缤纷，煞为壮观。\n"NOR, users());
        } else
        if (r < 40)
        {
        	msg = HIW "【自然奇观】夜空流星\n"NOR;
                msg += HIC "只听远处一阵刺耳的摩擦声，举目望去，发现竟有流星从天边划过，怎奈距\n"
                          "隔委实太远，根本无法看清。\n" NOR;

                msg += HIG "你观罢流星，隐隐的对武学有了一丝体会。\n" NOR;

                for ( i = 0 ; i < sizeof(obs); i++)
                {
                	if( !living(obs[i]) || !userp(obs[i]) ) continue;
			p_bonus = 500 + random( 500 );
			s_bonus = 200 + random( 200 );			
			obs[i]->add("potential", p_bonus);
			obs[i]->add("score", s_bonus);
		}      
                message("vision", msg, obs);

        } else
        {
                switch (random(2))
                {
                case 0:
                        msg = WHT "眼见天边一片明亮，知是流星雨将至，可怎奈间隔遥且云层厚，却无缘得见。\n" NOR;
                        break;
                default:
                        msg = WHT "眼见天边一片明亮，但是水气，雾气和云层交杂，让你什么都看不清楚。\n" NOR;
                        break;
                }
                msg += HIG "你心中连叹：“太可惜了！”\n" NOR;

                message("vision", msg, obs);
        }
}

// 事件触发
void trigger_event()
{
        object room;

        // 长白山天池夜陨
        if (objectp(room = find_object("/d/guanwai/tianchi1")))
                do_bonus(room);
}

void create() 
{ 
	seteuid(getuid()); 
	message("channel:sys", HIR"【自然奇观】长白山天池流星。\n"NOR, users());
	trigger_event();
}
