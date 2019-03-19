/*  <SecCrypt CPL V3R05>  */
 
//

#include  <ansi.h>

inherit  ITEM;

string  *prefixs  =  ({
    "锦面",
    "缎面",
    "鹅绒",
    "丝绣",
});

string  *names  =  ({
    "",
    "大",
    "扶手",
    "靠背",
    "折叠",
    "安乐",
});

string  *suffixs  =  ({
    "长椅",
    "躺椅",
});

void  create()
{
    set_name(prefixs[random(sizeof(prefixs))]+names[random(sizeof(names))]+
                      suffixs[random(sizeof(suffixs))],  ({  "chair"  }));
    set_weight(28000);
    set("long",  "这是一把椅子。\n"  );
    if(  clonep()  )
        set_default_object(__FILE__);
    else  {
        set("unit",  "把");
        set("material",  "stone");
        set("value",  2000);
        set("no_sell",  1);
        set("no_get",  1);
    }
    setup();
}

void  init  ()
{
    object  me  =  this_object();
    object  where  =  environment(me);

    if  (where  &&  userp(where))
    {
        remove_call_out  ("destruct_me");
        call_out  ("destruct_me",900+random(900),me);
    }
}

void  destruct_me  (object  me)
{
    destruct  (me);
}
