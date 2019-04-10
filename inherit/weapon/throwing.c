// throwing.c

#include <weapon.h>

inherit COMBINED_ITEM;
inherit F_EQUIP;

varargs void init_throwing(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", (int)flag | SECONDARY);
//	set("flag", 8);
}

void setup()
{
	// ::setup();
	seteuid(getuid());

	if( clonep(this_object()) ) return;

	set("skill_type", "throwing");
	set("rigidity", 1);
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :));
		set("verbs", ({ "throw" }) );
	}
}

