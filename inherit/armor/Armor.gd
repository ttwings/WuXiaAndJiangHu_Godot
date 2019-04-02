# # armor.c

#include <armor.h>
# Standard inheritable armor objects.
extends Equip

const HEAD		= "/inherit/armor/head"
const NECK		= "/inherit/armor/neck"
const CLOTH		= "/inherit/armor/cloth"
const ARMOR		= "/inherit/armor/armor"
const SURCOAT	= 	"/inherit/armor/surcoat"
const WAIST		= "/inherit/armor/waist"
const WRISTS	= 	"/inherit/armor/wrists"
const SHIELD	= 	"/inherit/armor/shield"
const FINGER	= 	"/inherit/armor/finger"
const HANDS		= "/inherit/armor/hands"
const BOOTS		= "/inherit/armor/boots"

# Standard armor types
const TYPE_HEAD		= "head"
const TYPE_NECK		= "neck"
const TYPE_CLOTH	= "cloth"
const TYPE_ARMOR	= "armor"
const TYPE_SURCOAT	= "surcoat"
const TYPE_WAIST	= "waist"
const TYPE_WRISTS	= "wrists"
const TYPE_SHIELD	= "shield"
const TYPE_FINGER	= "finger"
const TYPE_HANDS	= "hands"
const TYPE_BOOTS	= "boots"
# inherit EQUIP;

func setup():
	if( clonep(this_object()) ) :
		return;

	set("armor_type", TYPE_ARMOR);
	if(!query("armor_apply/dodge")
		and	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );
