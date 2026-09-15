# /*  <SecCrypt CPL V3R05>  */
 
# //  pink_cloth.c

#include  <armor.h>
#include  <ansi.h>

# inherit  CLOTH;
extends Cloth
func create():
	set_name(HIG  "轻纱长裙"  NOR,  ({  "skirt",  "cloth"  })  );
	set_weight(1000);
	# if(  clonep()  )
		set_default_object(__FILE__);
	# else  {
	set_attr("long",  "一条朦朦胧胧的纱裙，闻起来还有一股淡香。\n");
	set_attr("unit",  "条");
	set_attr("value",  0);
	set_attr("material",  "cloth");
	set_attr("armor_prop/armor",  1);
	set_attr("armor_prop/personality",  3);
	set_attr("female_only",  1);
	setup();

# //int  query_autoload()  {  return  1;  }

