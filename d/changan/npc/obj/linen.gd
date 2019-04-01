# /*  <SecCrypt CPL V3R05>  */
 
# //  linen.c

#include <armor.h>

# inherit CLOTH;
extends Cloth
func create():
	set_name("´Ö²¼ÒÂ","linen");
	set_weight(3000);
	# if( clonep()  )
	# 	set_default_object(__FILE__);
	# else {
	set("material",  "cloth");
	set("unit",  "¼þ");
	set("value",  0);
	set("armor_prop/armor",  1);
	setup();
