// qiantang.c 事件：钱塘江潮信
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
	
	msg = HIW "【自然奇观】钱塘江潮信\n"NOR;
	msg += HIC "每年八月十八钱塘江涨潮，非常准时，故称之为潮信。 \n"
	          "每次潮水来临时波涛汹涌，气势逼人，十分壮观。\n";NOR;
        msg += HIC "只听“隆隆”一阵雷鸣响过，潮水如涌一般的向岸边卷来。\n"
                  "刹那间，漫江沸腾，波涛万顷，潮高丈馀，万马奔腾，真有\n"
                  "“涛来势转雄，猎猎驾长风。雷震云霓里，山飞霜雪中”的\n"
                  "壮丽气势！正所谓“远若素练横江，声如金鼓；近则亘如山\n"
                  "岳，奋如雷霆”。一时间你不禁沉浸当中，天地万物都已然\n"
                  "忘怀了。\n" NOR;
                                   
        msg += HIG "你望着汹涌的潮水，若有所悟，对武功又有了新的体会。\n" NOR;
        message("vision", msg, obs);

	message("channel:rumor", HIM"【谣言】"+"八月十八又到了，听说不少人前往钱塘江观潮。\n"NOR, users()); 
	        
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
}

// 事件触发
void trigger_event()
{
        object room;
                
        // 钱塘江潮信
        if (objectp(room = find_object("/d/hangzhou/qiantang")))
                do_bonus(room);
                
}

void create() 
{ 
	seteuid(getuid()); 
	message("channel:sys", HIR"【自然奇观】钱塘江潮信。\n"NOR, users());
	trigger_event();
}