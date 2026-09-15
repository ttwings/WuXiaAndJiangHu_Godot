# /*  <SecCrypt CPL V3R05>  */
 
#include <armor.h>

# inherit CLOTH;
extends Cloth

func create():
	set_name("绸袍", "choupao");
	set_weight(3000);
	# if(  clonep()  )
	# 	set_default_object(__FILE__);
	# else  {
	set_attr("long","一件丝绸长袍，质的和裁剪都不错．\n");
	set_attr("material",  "cloth");
	set_attr("unit",  "件");
	set_attr("value",  600);
	set_attr("armor_prop/armor",  4);
	set_attr("armor_prop/personality",  1);
	setup();

