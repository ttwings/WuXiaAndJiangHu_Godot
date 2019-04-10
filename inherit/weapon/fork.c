// fork.c

#include <weapon.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

varargs void init_fork(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", (int)flag | POINTED | SECONDARY);
//	set("flag", 1);
	set("skill_type", "fork");
	set("rigidity", (int)(damage/3));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "impale", "pierce", "thrust" }) );
	}
}

