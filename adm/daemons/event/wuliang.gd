# wuliang.c 事件：无量山玉壁剑舞
# for XKX100 , by Sir 2003.11.3

#include <ansi.h>

# 奖励
func do_bonus(room):
    var obs
    var msg
    var lvl
    var p_bonus
    var s_bonus
    var r
    var i

    obs = all_inventory(room);
    if (sizeof(obs) < 1):
        return;

    r = random(100);
    if (r == 0):
        msg = HIG + "【自然奇观】无量山玉壁剑舞\n"+ NOR;
        msg += HIW + "只见皎洁的月光下，两个飘逸绝伦的身影倒映在对面山壁之上，持剑翩翩起\n"
                "舞，剑光顿挫，仙影回翔。你不由惊叹：寰宇之中，竟有如此绝奥之技，今\n"
                "日有缘得见仙人之姿，实在是福分非浅。\n" + NOR;
        msg += HIG "你对仙人的剑舞颇有所感，武学上顿时有了新的领悟。\n" NOR;

        message("vision", msg, obs);
        # for ( i = 0 ; i < sizeof(obs); i++)  # 增加潜能基本剑法及基本身法
        for i in range(obs.size()):
            if( !living(obs[i]) || !userp(obs[i]) ) :
                continue;
			p_bonus = 5000 + random( 5000 );
			s_bonus = 1000 + random( 500 );
			obs[i].add("potential", p_bonus);
			obs[i].add("score",s_bonus);
            
			lvl = obs[i].query_skill("sword", 1);
            if (lvl >= 50 && lvl< 300 ):
                obs[i].set_skill("sword", lvl + 10);
            elif ( lvl >= 300 ):
                obs[i].set_skill("sword", lvl + 1);

            lvl = obs[i].query_skill("dodge", 1);
            if (lvl >= 50 && lvl< 300 ):
                obs[i].set_skill("dodge", lvl + 10);
            elif ( lvl >= 300 ):
                obs[i].set_skill("dodge", lvl + 1);

        message("channel:rumor", HIM"【谣言】"+"听说大理无量山又出仙人剑舞，仙影玄奇，令人匪夷所思。\n"NOR, users());    
    elif (r < 60) :
        msg = HIG + "【自然奇观】无量山玉壁仙影\n"+ NOR;
        msg += HIW + "皎洁的月光下，壁上能隐隐约约倒影出仙人之姿。实乃世间仅有。\n" + NOR;

        match (random(3)):
            0:
                msg += HIW + "只见对面无量山玉壁上仙影一闪即过，身形之敏捷，令你根本无法捕捉。\n" + NOR;
            1:
                msg += HIW + "只见无量山玉壁上闪过几道仙影，似乎是施展一种奇妙无比的武功绝学。\n" + NOR;
            _:
                msg += HIW + "忽然间两个飘逸绝伦的身影显映在对面山上，但仙影转瞬即逝，你根本无法看清。\n" + NOR;

        msg += HIG + "你受到了仙影的感悟，武学方面又有了一些体会。\n" + NOR;
        
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
                msg = WHT + "眼见皎洁的月光升起，可是一团云飘过，遮盖了月光，你眼前顿时一片漆黑。\n" + NOR;
            1:
                msg = WHT + "你目不转睛的注视着对面的玉壁，可刹那间雷声轰鸣，山风卷云，将月光遮了个严实。\n" + NOR;
            _:
                msg = WHT + "夜晚已至，可一团团浓厚的云层却笼罩着天空，你连对面的山头都无法看清。\n" + NOR;
        msg += HIG + "你不禁叹息道：“怎奈缘分未至，无缘窥视仙影！”\n" + NOR;

        message("vision", msg, obs);


# 事件触发
func trigger_event():
    var room;
    room = find_object("/d/xiaoyao/pubu")
    # 无量山玉壁剑舞
    if (objectp(room)):
        do_bonus(room);

func create(): 
	seteuid(getuid()); 
	message("channel:sys", HIR"【自然奇观】无量山玉壁剑舞。\n"NOR, users());
	trigger_event();
