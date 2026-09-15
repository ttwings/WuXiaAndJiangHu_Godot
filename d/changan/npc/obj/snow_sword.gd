# /*  <SecCrypt CPL V3R05>  */
 
#include  <weapon.h>

# inherit  SWORD;
extends Sword
func create():
	set_name("风回雪舞剑","snowsword");
	set_weight(400);
	# if(  clonep()  )
	# 	set_default_object(__FILE__);
	# else  {
	set_attr("unit",  "把");
	set_attr("value",  700);
	set_attr("material",  "steel");
	set_attr("long",  "这是一把用来练舞的剑，剑身细长，轻巧尤锋利。\n");
	set_attr("wield_msg",  "$N抽出一把剑身细长的剑，握在手中。\n");
	set_attr("unequip_msg",  "$N放下手中的$n。\n");
	set_attr("weapon_prop/courage",  4);
	# }
	# init_sword(40);
	setup();

