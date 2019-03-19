/*  <SecCrypt CPL V3R05>  */
 
//  magua.c

#include  <armor.h>

inherit  CLOTH;

void  create()
{
	set_name("马褂",  ({  "magua"}));
	set_weight(3000);
	if(  clonep()  )
		set_default_object(__FILE__);
	else  {
		set("long",  "一件淡青色的马褂．\n");
   		set("unit",  "件");
		set("value",  500);
		set("material",  "cloth");
		set("armor_prop/armor",  5);
   	}
	setup();
}

