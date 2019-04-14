// hspb.c 事件：衡山水帘洞瀑布
// for XKX100 , by Sir 2003.11.3

#include <ansi.h>

// 奖励
private void do_bonus(object room)
{
        object *obs;
        object ob;
        string msg;
        int lvl,p_bonus,s_bonus;
        int r,i;

        obs = all_inventory(room);
        if (sizeof(obs) < 1)
                return;

        r = random(365);
        if (r == 0)
        { 
        	msg = HIY "【自然奇观】衡山水帘洞激流\n"NOR;
                msg += HIG "只听轰隆隆声音大做，振聋发聩，令人心惧神摇！你抬头看去，只见\n"
                          "黄昏中水帘洞笼罩在层层雾气之中，分外妖娆。洞外水流飞泻，气势惊人！\n" NOR;
                msg += HIG "你望着湍急的瀑布飞练，为这世间美景惊叹不已，从"
                           "中不禁领悟到了武学的道理。\n" NOR; 
                for ( i = 0 ; i < sizeof(obs); i++)  // 增加潜能基本内功及潜能
                {
                	if( !living(obs[i]) || !userp(obs[i]) ) continue;
			p_bonus = 5000 + random( 5000 );
			s_bonus = 1000 + random( 500 );
			obs[i]->add("potential", p_bonus);
			obs[i]->add("score",s_bonus);
                        
			lvl = obs[i]->query_skill("force", 1);
                        if (lvl >= 50 && lvl< 300 )
                               	obs[i]->set_skill("force", lvl + 10);
                        else if ( lvl >= 300 )
                               	obs[i]->set_skill("force", lvl + 1);

                }

                message("vision", msg, obs);
                message("channel:rumor", HIM"【谣言】"+"听说衡山水帘洞瀑布激流澎湃，奇景非凡，无数游人叹羡不已。\n"NOR, users());
               
        } else 
        if (r < 250) 
        {	
        	msg = HIY "【自然奇观】衡山水帘洞瀑流\n"NOR;
                msg += HIY "一阵轰隆轰隆的声音传来，你抬头一看，只见黄昏中瀑布腾起层层雾气。\n" NOR;
                switch (random(3)) 
                { 
                case 0: 
                        msg += HIY "看着这壮丽的瀑流，你不禁感叹，正所谓「飞流直"
                                    "下三千尺，疑是银河落九天」啊。\n" NOR; 
                        break; 
                case 1: 
                        msg += HIY "瀑流就像一席倒挂的白帘，气势如虹，天地都不禁为之失色。\n" NOR; 
                        break; 
                default: 

                        msg += HIY "瀑流直如水银泄地一般，水花四溅。\n" NOR; 
                        break; 
                } 
                msg += HIG "观赏着飞流直下的水瀑，你不由得感叹自然造化的奇妙，隐"
                           "隐对武学也有了一点领会。\n" NOR; 
                           
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
                switch (random(3))
                {
                case 0:
                        msg = WHT "瀑流渐渐缓了下来。\n" NOR;
                        break;
                case 1:
                        msg = WHT "瀑流总是不见有增强的趋势。\n" NOR;
                        break;
                default:
                        msg = WHT "瀑流有如小桥流水，叮叮咚咚，离你所期望的相差甚远。\n" NOR;
                        break;
                }
                msg += HIG "你心中大感失望。\n" NOR;

                message("vision", msg, obs);
        }
} 
 
// 事件触发 
void trigger_event() 
{ 
        object room; 
        // 衡山水帘洞瀑布 
        if (objectp(room = find_object("/d/henshan/shuiliandong"))) 
                do_bonus(room); 
} 

void create() 
{ 
	seteuid(getuid()); 
	message("channel:sys", HIR"【自然奇观】衡山水帘洞瀑布。\n"NOR, users());
	trigger_event();
}