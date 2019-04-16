# apprentice.c
# From ES2
# Modified by Xiang for XKX (12/15/95)

#include <dbase.h>

func is_apprentice_of(ob):
	var family;
	family = query("family")
	if( !mapp(family ) ) :
		return 0;

	if( family["master_id"] == ob.query("id") && family["master_name"] == ob.query("name") ):
		return 1;
	return 0;	


func assign_apprentice(title:String, privs:int):
	var family;
	family = query("family")
	if( !mapp(family) ) :
		return;

	family["title"] = title;
	family["privs"] = privs;

	if( userp(this_object()) || !query("title") ) :
		if( family["generation"]==1 ) :
			set("title", family["family_name"] + "开山祖师");
		else :
			set("title", sprintf("%s第%s代%s", family["family_name"],
				chinese_number(family["generation"]), family["title"]));


# This is used for NPC, or start a new family for a player.
func create_family(family_name:String, generation:int, title:String):
	var family;

	family = allocate_mapping(6);

	family["family_name"] = family_name;
	family["generation"] = generation;

	set("family", family);

	# priv = -1 for ALL privileges.
	assign_apprentice( title, -1 );


func recruit_apprentice(ob):
	var my_family
	var family;

	if( ob.is_apprentice_of( this_object() ) ):
		return 0;
	if( !mapp(my_family = query("family")) ):
		return 0;

	family = allocate_mapping(sizeof(my_family));
	family["master_id"] = query("id");
	family["master_name"] = query("name");
	family["family_name"] = my_family["family_name"];
	family["generation"] = my_family["generation"] + 1;
	family["enter_time"] = time();
	ob.set("family", family);
	ob.assign_apprentice("弟子", 0);
	return 1;


