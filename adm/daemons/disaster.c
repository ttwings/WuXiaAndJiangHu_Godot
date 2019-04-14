// Last Modified by winder on Apr. 25 2001
// 浩劫系统的主程序

#include <ansi.h>

void copy_npc();
string query_site();
int query_children(string arg);
void verdict_time();
void set_hj_startT(int i);
int query_hj_startT();
void juedou();

string *factions=({
  "少林派",
  "武当派",
  "峨嵋派",
  "华山派",
  "全真教",
  "逍遥派",
  "明教",
  "北京城"
});
string faction;     //存放攻打的门派
int Cnpcend, count = 0;
int hj_startT = 0;
object lead;

//浩劫系统发生的主函数
void disaster(int sum)
{
  count = sum;
  LOGIN_D->set_dienpc(-1);
  set_hj_startT(time());
  faction = factions[count];
  message("channel:snow", HIM"【谣言】神秘组织的第"+chinese_number(count+1)+"个目标是血洗【"HIR+faction+HIM"】。\n"NOR, users());
  message("channel:snow",HIC"【"+HIM MUD_NAME+HIC"】由于大敌当前，从现在开始进入戒严状态！任何人不得临阵脱逃！\n"NOR, users());

  call_out("copy_npc",0);
}

//产生EXP and SKILL跟指定玩家相等的杀手(pker)
void copy_npc()
{
  object ob, *user;
  mapping skill_status,skl;
  string site;
  string *sname;
  string *skillname;
  int i, j, exp, lead_exp=0,skilllvl,m,n;
  int t=0,npc_num=0,copy_npc_time=1,npc_flag=0;

  user = users();
  j = sizeof(user);
  if (faction!="北京城")
  {
   for (i=0;i<j;i++)
   {
     if (!wizardp(user[i]) && user[i]->query("family/family_name")==faction)
          npc_num+=1;
    }
   if(npc_num<3) copy_npc_time=3;
   else copy_npc_time=2;
   npc_flag=0;
  }
  else
  { 
   if(j<40) copy_npc_time=5; 
   else     copy_npc_time=4;
   npc_num=j+1;
   npc_flag=1;
  }   
  if (npc_num==0)
   {
    message("channel:snow",HIM"【谣言】由于"+faction+"门下空无一人，神秘组织不战而胜，一举拿下了"+faction+"。\n"NOR, users());
    message("channel:snow", HIC"【闲聊】七杀门首领天杀星大笑道：没想到如此轻易得手，真是天助我也，哈。哈。哈。下一个！\n"NOR, users());
    message("channel:snow",HIC"【"+HIM MUD_NAME+HIC"】敌人暂时撤退了，现在解除戒严状态！\n"NOR, users());
    LOGIN_D->set_madlock(0);
    remove_call_out("verdict_time");
    call_out("disaster",10,count+1);
    return;
   }   
   else
   {
   for (t=0;t<copy_npc_time;t++)
   { 
     for (i=0;i<j;i++)
       { 
        if (wizardp(user[i])) continue; // 不copy巫师
        if(faction!="北京城")
         {
           if(user[i]->query("family/family_name")==faction)
              npc_flag=1;
           else
              npc_flag=0;
         }
        if (npc_flag==1)
        {       
          exp = (int) user[i]->query("combat_exp");
          if (lead_exp < exp)
           {
          lead_exp=exp;
          lead = user[i];
           }
           if (exp < 50000)
             ob = new("/clone/haojie/pker1");
           else if (exp < 300000)
             ob = new("/clone/haojie/pker2");
           else if (exp < 600000)
             ob = new("/clone/haojie/pker3");
           else if (exp < 1500000)
             ob = new("/clone/haojie/pker4");
           else if (exp < 2500000)
             ob = new("/clone/haojie/pker5");
           else if (exp < 4000000)
             ob = new("/clone/haojie/pker6");
           else if (exp < 6000000)
             ob = new("/clone/haojie/pker7");
           else if (exp < 8000000)
             ob = new("/clone/haojie/pker8");
           else
             { 
              ob = new("/clone/haojie/pker9");
              ob->set("combat_exp",exp);
              }         
           skl = user[i]->query_skills();
           skilllvl=20; 
           if (sizeof(skl))
            {
              skillname = sort_array( keys(skl), (: strcmp :) );
              for (m=0; m<sizeof(skl); m++)
              {
                if (skilllvl < skl[skillname[m]])
                   skilllvl = skl[skillname[m]];
              }        
            }           
            skill_status = ob->query_skills();
            sname = keys(skill_status);

            for(n=0; n<sizeof(skill_status); n++)                   
               ob->set_skill(sname[n], skilllvl); 
                           
            site = query_site();
            ob->move(site);
            message_vision("$N凶神恶煞的走了过来。\n",ob);
             }//npc_flag=1
            }//for all user    
          }//copytime
    remove_call_out("verdict_time");
    call_out("verdict_time",60);
   }
}

//根据门派随机产生pker的落脚地点
string query_site()
{
  mapping sites=([
    "少林派": ({"/d/shaolin/smdian","/d/shaolin/guangchang2","/d/shaolin/fzlou","/d/shaolin/guangchang1"}),
    "武当派": ({"/d/wudang/sanqingdian","/d/wudang/guangchang","/d/wudang/xuanyuegate","/d/wudang/donglang2"}),
    "峨嵋派": ({"/d/emei/huayanding","/d/emei/lianhuashi","/d/emei/ztpo1","/d/emei/xixiangchi"}),
    "华山派": ({"/d/huashan/zhenyue","/d/huashan/yunu","/d/huashan/square","/d/huashan/buwei1"}),
    "全真教": ({"/d/quanzhen/damen","/d/quanzhen/datang2","/d/quanzhen/houtang1","/d/quanzhen/houtang3"}),
    "逍遥派": ({"/d/xiaoyao/qingcaop","/d/xiaoyao/xiaodao1","/d/xiaoyao/xiaodao3","/d/xiaoyao/xiaodao4"}),
    "明教": ({"/d/mingjiao/ziweitang","/d/mingjiao/square","/d/mingjiao/qiandian","/d/mingjiao/tianweitang"}),
//    "北京城": ({"/d/beijing/dongcha1","/d/beijing/dongcha2","/d/beijing/wangfu3","/d/beijing/xichang1","/d/beijing/xichang2"}),
    "北京城" : ({"/d/beijing/weifu_men","/d/beijing/kang1","/d/beijing/dongcha2","/d/beijing/xichang2","/d/beijing/wangfu2","/d/beijing/tian_anm","/d/beijing/xidan1","/d/beijing/di_anmen"}),
  ]);

  return sites[faction][random(sizeof(sites[faction]))];
}

void juedou()
{
  object ob;
  int i, exp, skill, killer = 0,topexp=5000000;

  ob = new("/clone/haojie/zhanshu.c");
  ob->move(lead);
  message_vision(HIY"一张战书飘到了$N的面前。\n"NOR,lead);
  message("channel:snow",HIM"【谣言】"+"听说"+lead->name()+HIM"得到了一张七杀门首领天杀星的挑战书。\n"NOR, users());
  exp = lead->query("combat_exp");
  skill = lead->query_skill("parry",1);
  ob = new("/clone/haojie/tianshaxing.c");
  ob->set("pk_target",lead);
  ob->set("combat_exp",(int)topexp);
  ob->move("/d/beijing/tian_anm.c");
  message_vision("$N凶神恶煞的走了过来。\n",ob);
}

//取指定pker的人数
int query_children(string arg)
{
  object *ch;
  int i,sum = 0;

  ch = children(arg);
  for(i=0;i<sizeof(ch);i++)
    if(environment(ch[i])) sum++;
  return sum;
}

//定时判断浩劫发生的时间是否超过期限，超过则给予玩家惩罚
void verdict_time()
{
  object *user,*ob_list;
  int i, exp, parry, force,sum=0;
  int limit,killer,topexp;
  if(faction!="北京城")
   limit=1800;
  else 
   limit=2400;

//设置浩劫的期限为30分钟(1800秒)
  if( (time()-hj_startT) < limit )
  {
    sum += query_children("/clone/haojie/pker9.c");
    sum += query_children("/clone/haojie/pker8.c");
    sum += query_children("/clone/haojie/pker7.c");
    sum += query_children("/clone/haojie/pker6.c");
    sum += query_children("/clone/haojie/pker5.c");
    sum += query_children("/clone/haojie/pker4.c");
    sum += query_children("/clone/haojie/pker3.c");
    sum += query_children("/clone/haojie/pker2.c");
    sum += query_children("/clone/haojie/pker1.c");
    if (sum > 0) 
    {  
      remove_call_out("verdict_time");
      call_out("verdict_time",60);
     }
    else if (count+1 != sizeof(factions))
    {
      message("channel:snow", HIM"【谣言】"+faction+"弟子在"+lead->name()+"的带领下，杀得敌人溃不成军，大败而逃！\n"NOR, users());
      message("channel:snow", HIC"【闲聊】七杀门首领天杀星：他奶奶的，点子手硬，闪先！\n"NOR, users());
      message("channel:snow", HIC"【"+HIM MUD_NAME +HIC"】暂时击退敌人，江湖局势得到缓解，临时解除戒严状态！\n"NOR, users());
      LOGIN_D->set_madlock(0);
      remove_call_out("verdict_time");
      call_out("disaster",20,count+1);
    }
    else 
    {  
      user = users();
      for(i=0;i<sizeof(user);i++)
      { 
     	if (user[i]->query_temp("hj_killer") > killer) 
           {
          	lead = user[i];
          	killer=lead->query_temp("hj_killer");
           }
      if (user[i]->query("combat_exp")>topexp) 
          topexp= (int)user[i]->query("combat_exp");
      user[i]->delete_temp("hj_killer");
      }

      message("channel:snow", HIM"【谣言】各大门派接成联盟，在"+lead->name()+"的带领下，终于挫败了神秘组织的阴谋，江湖又恢复了往日的平静。\n"NOR, users());
      message("channel:snow",HIC"【"+HIM MUD_NAME+HIC"】敌方大败，江湖恢复平静，解除戒严状态！\n"NOR, users());
      message("channel:snow", HIC"【闲聊】七杀门首领天杀星仰天狂叫：我不服！！我不服！！！我不服！！！！\n"NOR, users());
      LOGIN_D->set_madlock(0);
      remove_call_out("verdict_time");
//      call_out("verdict_time",60);
      call_out("juedou",2);
    }
  }
  else
  {
  if (!LOGIN_D->get_madlock()) return;
  ob_list = children("/clone/haojie/pker1");
  for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }
  ob_list = children("/clone/haojie/pker2");
  for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
     }     
  ob_list = children("/clone/haojie/pker3");
  for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }
  ob_list = children("/clone/haojie/pker4");
  for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }  
   ob_list = children("/clone/haojie/pker5");
   for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }    
   ob_list = children("/clone/haojie/pker6");
   for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    } 
   ob_list = children("/clone/haojie/pker7");
   for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }     
   ob_list = children("/clone/haojie/pker8");
   for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }  
   ob_list = children("/clone/haojie/pker9");
   for(i=0; i<sizeof(ob_list); i++) 
    if(environment(ob_list[i]))
    {
      message_vision("$N说道：哈哈，弟兄们，撤！\n",ob_list[i]);
      destruct(ob_list[i]);
    }                            

  if (count+1 != sizeof(factions))
  {
    message("channel:snow",HIM"【谣言】"+faction+"弟子力战之下，伤亡惨重，从此消声匿迹。\n"NOR, users());
    message("channel:snow",HIC"【闲聊】七杀门首领天杀星冷哼一声：下一个！\n"NOR, users());
    message("channel:snow",HIC"【"+HIM MUD_NAME+HIC"】敌人暂时撤退了，现在解除戒严状态！\n"NOR, users());
    LOGIN_D->set_madlock(0);
    call_out("disaster",10,count+1);
  }
  else
  {
    message("channel:snow", HIM"【谣言】虽然各派奋力杀敌，无奈悬殊太大，还是败下阵来，一时间腥风血雨，武林一片混暗。\n"NOR, users());
    message("channel:snow",HIC"【"+HIM MUD_NAME+HIC"】七杀门大获全胜，江湖一片黑暗，现在解除戒严状态！大家快逃命吧!\n"NOR, users());
    LOGIN_D->set_madlock(0);
  }
 }
}

//设置和读取浩劫的开始时间
void set_hj_startT(int i)
{
  hj_startT = i;
}
int query_hj_startT()
{
  return hj_startT;
}
