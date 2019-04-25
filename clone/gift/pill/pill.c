#include <ansi.h>
inherit ITEM;
int query_autoload()
{
  return 1;
}

void create()
{
  set_name(HIW "补药" NOR, ({"bu yao", "yao"}));
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", HIY "这是一颗增加内功的补药。\n" NOR);
    set("unit", "课");
    set("value", 10000);
    set("weight", 300);
    //增加的技能名为force
    //如果不为force 那后面的force_point表示增加精力
    set("pill_skill", "force");
    // 是否为特殊武功
    set("skill_mapped", 1);

    //增加武功多少技能点
    set("pill_point", 100);

    //增加多少内力或者精力
    set("force_point", 1);

    //加武功成功的描述
    set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
    //加武功失败的描述  这两项仅当pill_point定义时
    set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);

    // 增加内力或精力的描述，如果有前面两条信息，则应作缺省
    set("pill_msg3", HIM "你感到内力又雄厚了一些。\n" NOR);
    set("pill_msg4", HIR "你感到内息澎湃，难以吸收药力。\n" NOR);
  }
  setup();
}

init()
{
  add_action("do_eat", "eat");
}
int do_eat(string arg)
{
  string skill;
  int pot1, pot2, time;
  object me = this_player();
  int jingli_limit = me->query_skill("taoism", 1) * 10;
  int neili_limit = me->query_skill("force") * 10;
  pot1 = query("pill_point");
  pot2 = query("force_point");
  time = query("pill_point") / 40;
  //假设20000点熟练度 就是500condition ==187 min ~= 3hour

  //非技能型的药物重新计算效用时间
  if (!query("pill_point"))
    time = 400 + query("force_point") * 10;
  if (!id(arg))
    return 0;
  if ((int)me->query_condition("pill_drug") > 0)
  {
    write("你觉得现在内息未定，经脉隐隐还能感到真气冲荡，不敢贸然服食。\n");
    return 1;
  }
  if (me->is_busy())
  {
    write("你正忙着呢。\n");
    return 1;
  }
  me->apply_condition("pill_drug", time);
  message_vision(HIY + "$N" + HIY + "服下一" + query("unit") + query("name") + HIY + "，开始运功吸收药力。\n" NOR, me);
  log_file("gift/eat_skill", sprintf("%-20s eat %-10s [%s]\n", me->query("name") + "(" + me->query("id") + ")", this_object()->name(), ctime(time())));

  // 如果该药物有增加技能的功能，则加之
  if (query("pill_skill") && query("pill_point"))
  {
    // 判断增加的技能是否为特殊技能
    if (query("skill_mapped") >= 1)
      skill = me->query_skill_mapped(query("pill_skill"));
    else
      skill = query("pill_skill");
    tell_object(me, query("pill_msg1"));
    me->improve_skill(skill, pot1);
  }
  // 如果该药物有增加功力的功能，则加之
  if (query("pill_skill") && query("force_point"))
  {
    // 内功型药物增加内力，否则则增加精力
    if (query("pill_skill") == "force")
    {
      // 提供出信息
      if (me->query("max_neili") < neili_limit && query("pill_msg3"))
        tell_object(me, query("pill_msg3"));
      else if (me->query("max_neili") >= neili_limit && query("pill_msg4"))
        tell_object(me, query("pill_msg4"));
      //增加
      me->add("max_neili", pot2 + random(pot2));
      if (me->query("neili") < me->query("max_neili"))
        me->set("neili", me->query("max_neili"));
    }
    else
    {
      // 提供出信息
      if (me->query("max_jingli") < jingli_limit && query("pill_msg3"))
        tell_object(me, query("pill_msg3"));
      else if (me->query("max_jingli") >= jingli_limit && query("pill_msg4"))
        tell_object(me, query("pill_msg4"));
      //增加
      me->add("max_jingli", pot2 + random(pot2));
      if (me->query("jingli") < me->query("max_jingli"))
        me->set("jingli", me->query("max_jingli"));
    }
  }
  me->start_busy(random(3) + 3);

  destruct(this_object());

  return 1;
}
