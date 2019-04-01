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
	set("unit",  "把");
	set("value",  700);
	set("material",  "steel");
	set("long",  "这是一把用来练舞的剑，剑身细长，轻巧尤锋利。\n");
	set("wield_msg",  "$N抽出一把剑身细长的剑，握在手中。\n");
	set("unequip_msg",  "$N放下手中的$n。\n");
	set("weapon_prop/courage",  4);
	# }
	# init_sword(40);
	setup();

