// six-book.c
#include <ansi.h>
inherit ITEM;

int do_yanjiu(string arg);
void create()
{
	set_name( HIC"六脉神剑谱"NOR,({ "sixfinger book","book"}));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","这是一幅图。上面都是纵横交叉的直线、圆圈和弧形。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":         "six-finger"  ,//name of the skill
			"exp_required": 100000,        //minimum combat experience required
			"jing_cost":    20+random(20),// jing cost every time study this
			"difficulty":	20,           // the base int to learn this skill
			"min_skill":	0,            // the minimum level you can learn
			"max_skill":	99            // the maximum level you can learn
		]) );
	}
}
void init()
{
	add_action("do_yanjiu","yanjiu");
	add_action("do_yanjiu","research");
}
int do_yanjiu(string arg)
{
	object ob = this_object();
	object me = this_player();
	string skill,book;
	string msg;
	
	if (!present(ob,me)) return 0;

	if ((int)me->query_skill("literate",1)<1)
	{
		write("你是个文盲，先学点读书写字(literate)吧。\n");
		return 1;
	}

	if (me->is_busy() || me->is_fighting())
	{
		write("你正忙着呢。\n");
		return 1;
	}

	if (sscanf(arg,"%s from %s",skill,book)!=2)
	{
		write("研读绝技的指令是 yanjiu 绝技名 from book\n");
		return 1;
	}

	if (!id(book))
	{
		write("没有这本书。\n");
		return 1;
	}

	if (skill != "此去彼来" && skill != "驭剑气" 
	   && skill != "ciqu" && skill != "yuqi")
	{
		write("书上并没有介绍关于"+skill+"的内容。\n");
		return 1;
	}

	if (me->query("combat_exp")<1000000) 
	{
		write("你的实战经验太低，读不懂这么深奥的东西。\n");
		return 1;
	}

	if (me->query("jing")<100 ||
	    me->query("qi")<100 ||
	    me->query("neili")<200)
  {
  	write("你现在过于疲倦，无法专心下来研读新知。\n");
  	return 1;
  }
  
  switch(skill)
  {
  	case "ciqu":
  	case "此去彼来":
           if (me->query("can_perform/six-finger/ciqu"))
           {
                write("你不是已经会了吗？\n");
                return 1;
           }
           if (me->query_skill("six-finger", 1) < 120)
           {
                write("你六脉神剑不够熟练，无法研读此绝招！\n");
                return 1;
           }

           if (random (10) != 1)
           {
                write("你研究了半天，仍然无法将「此去彼来」融会贯通！\n");
                me->start_busy(15); 
                me->set("jing", 1);
                return 1;
           }
           msg = HIG "$N" HIG "翻看剑谱，仔细研究上面所记载的武学，霎那间忽有所悟"
                     "……\n" NOR;
           msg += HIW "$N" HIW "摊开双手，手指连弹，霎时间空气炙热，几"
                  "欲沸腾，六道剑气分自六穴，一起冲向天际" HIW "！\n" NOR;
           msg += HIG "$N" HIG "长叹一声，感慨万千，将内力收回丹田。\n" NOR; 
           message_vision(msg, me); 

                   me->improve_skill("finger", 1500000);
                   me->improve_skill("six-finger", 1500000);

           write(HIW "你学会了「" HIG "此去彼来" HIW "」。\n" NOR);
           me->set("can_perform/six-finger/ciqu", 1);
           destruct(this_object());
           return 1;
  	case "yuqi":
  	case "驭剑气":
           if (me->query("can_perform/six-finger/yuqi"))
           {
                write("你不是已经会了吗？\n");
                return 1;
           }
           if (me->query_skill("six-finger", 1) < 120)
           {
                write("你六脉神剑不够熟练，无法研读此绝招！\n");
                return 1;
           }
           if (me->query_skill("force", 1) < 120)
           {
                write("你内功火候不够，无法研读此绝招！\n");
                return 1;
           }

           if (random (20) != 1)
           {
                write("你研究了半天，仍然无法将「驭剑气」融会贯通！\n");
                me->start_busy(15);
                me->set("jing", 1);
                return 1;
           }
           msg = HIG "$N" HIG "翻看剑谱，仔细研究上面所记载的武学，霎那间忽有所悟"
                     "……\n" NOR;
           msg += HIM "$N" HIM "一声清啸，十指纷弹，顿觉六脉剑气已涌上心头，此起"
                  "彼伏、连绵不绝。霎时剑气如奔，连绵无尽的万道剑气豁然贯向虚空" HIM 
                  "！\n" NOR;
           msg += HIG "$N" HIG "长叹一声，感慨万千，将内力收回丹田。\n" NOR; 
           message_vision(msg, me); 

                   me->improve_skill("finger", 1500000);
                   me->improve_skill("six-finger", 1500000);

           write(HIW "你学会了「" HIG "驭剑气" HIW "」。\n" NOR);
           me->set("can_perform/six-finger,yuqi", 1);
           destruct(this_object());
           return 1;
  		break;
  	default:
  		return 0;
  }
  return 0;
}