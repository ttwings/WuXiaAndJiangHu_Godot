// hook.c

#include <weapon.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

varargs void init_hook(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
//	set("flag", (int)flag | EDGED);
	set("flag", (int)flag | EDGED | SECONDARY);
	set("skill_type", "hook");
	set("rigidity", (int)(damage/4));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "chop", "hack"}) );
	}
}

