# /*  <SecCrypt CPL V3R05>  */
 
# //  magua.c

#include  <armor.h>

inherit  CLOTH;

extends Cloth

func create():
	set_name("马褂","magua");
	set_weight(3000);
	# if(  clonep()  )
	# 	set_default_object(__FILE__);
	# else  {
	set_attr("long",  "一件淡青色的马褂．\n");
   	set_attr("unit",  "件");
	set_attr("value",  500);
	set_attr("material",  "cloth");
	set_attr("armor_prop/armor",  5);
   	
	setup();

