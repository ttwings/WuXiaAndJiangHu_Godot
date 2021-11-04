# # armor.c

#include <armor.h>
# Standard inheritable armor objects.
extends GameObject

class_name Armor

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
const TYPE_HEAD		= "head"		# 头冠
const TYPE_NECK		= "neck"		# 项链
const TYPE_CLOTH	= "cloth"		# 衣服
const TYPE_ARMOR	= "armor"		# 护甲
const TYPE_SURCOAT	= "surcoat"   	# 外套
const TYPE_WAIST	= "waist"		# 腰带
const TYPE_WRISTS	= "wrists"		# 护腕
const TYPE_SHIELD	= "shield"		# 盾牌
const TYPE_FINGER	= "finger"		# 手指
const TYPE_HANDS	= "hands"		# 手套
const TYPE_BOOTS	= "boots"		# 靴子
# inherit EQUIP;



func wear():
	var owner
	var armor_prop
	var applied_prop
	var apply
	var type;
	# # Only character object can wear armors.
	# if( !(owner = environment()).is_character() ) return 0;
	owner = environment()
	if( !owner.is_character() ):
		return 0;
	# If already worn, just recognize it.
	if( query("equipped") ) :
		return 1;
	armor_prop = query("armor_prop")
	
	# Check if we have "armor_prop" defined.
	if( !mapp(armor_prop) || query("weapon_prop/damage")>0 ):
#	if( !mapp(armor_prop = query("armor_prop")) )
		return notify_fail("你只能穿戴可当作护具的东西。\n");

	type = query("armor_type");
	if( owner.query_temp("armor/" + type) ):
		return notify_fail("你已经穿戴了同类型的护具了。\n");

	owner.set_temp("armor/" + type, this_object());
	apply = keys(armor_prop);
	applied_prop = owner.query_temp("apply");
	if( !mapp(applied_prop) ):
		applied_prop = {};
	# for(int i = 0; i<sizeof(apply); i++):
	for i in apply:
		if( undefinedp(applied_prop[apply[i]]) ):
			applied_prop[apply[i]] = armor_prop[apply[i]];
		else:
			applied_prop[apply[i]] += armor_prop[apply[i]];
	owner.set_temp("apply", applied_prop);
	set("equipped", "worn");
	return 1;
	
	
func unequip():
	var owner
	var weapon
	var prop
	var applied_prop
	var apply
	var equipped
	
	owner = environment()
	if !owner.is_character():
		return 0;
	equipped = query("equipped")
	if( !stringp(equipped) ):
		return notify_fail("你目前并没有装备这样东西。\n");

	if( equipped == "second_wield"):
		delete("equipped");
		return 1;

	if( equipped=="wielded" ):
		weapon = owner.query_temp("weapon")
		if( weapon == this_object() ):
			owner.delete_temp("weapon");
		elif(owner.query_temp("secondary_weapon") == this_object() ):
			owner.delete_temp("secondary_weapon");
		prop = query("weapon_prop");
		owner.delete_temp("use_apply_action");
		if (weapon):
			weapon.delete_temp("use_apply_skill");
		prop = query("weapon_prop");
		owner.delete_temp("perf_quick");
		owner.reset_action();
	elif( equipped=="worn" ):
		owner.delete_temp("armor/" + query("armor_type") );
		prop = query("armor_prop");

	apply = keys(prop);
	applied_prop = owner.query_temp("apply");
#	for(int i = 0; i<sizeof(apply); i++)
	for i in sizeof(apply):
		# To support array apply, we cannot add_temp() here.
		applied_prop[apply[i]] -= prop[apply[i]];

	delete("equipped");
	weapon = owner.query_temp("secondary_weapon");
	if(weapon):
		weapon.unequip();
		weapon.wield();
	return 1;	

func create():
	pass


# Init armor types

func init_head():
	set("armor_type", TYPE_HEAD);
	if( !query("armor_apply/dodge") && weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );

func init_neck():
	set("armor_type", TYPE_NECK);
	if( !query("armor_apply/dodge")	&& weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );

func init_cloth():
	set("armor_type", TYPE_CLOTH);
	if( !query("armor_apply/dodge") &&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );
		
func init_armor():
	set("armor_type", TYPE_ARMOR);
	if(!query("armor_apply/dodge") and weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );
	
func init_surcoat():
	set("armor_type", TYPE_SURCOAT);
	if( !query("armor_apply/dodge")	&& weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );

func init_wrists():
	set("armor_type", TYPE_WAIST);
	if( !query("armor_apply/dodge")	&&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );

func init_waist():
	set("armor_type", TYPE_WAIST);
	if( !query("armor_apply/dodge")	&&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );
		
func init_shield():
	set("armor_type", TYPE_SHIELD);
	if( !query("armor_apply/dodge")	&&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );	

func init_finger():
	set("armor_type", TYPE_FINGER);
	if( !query("armor_apply/dodge") &&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );	

func init_hands():
	set("armor_type", TYPE_HEAD);
	if( !query("armor_apply/dodge") && weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );	

func init_boots():
	set("armor_type", TYPE_BOOTS);
	if( !query("armor_apply/dodge") &&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );	
