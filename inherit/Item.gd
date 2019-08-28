extends GameObject

class_name Item

########################################  F_MOVE #####################################
#var weight : int = 0
#var encumb : int = 0
#var max_encumb : int = 0
func query_encumbrance():
	return encumb
func over_encumbranced():
	return encumb > max_encumb

func query_max_encumbrance():
	return max_encumb
	
func set_max_encumbrance(e:int):
	max_encumb = e

func add_encumbrance(w:int):
	encumb += w;
	if( encumb < 0 ):
		print_debug(self,"O encumbrance underflow")
		return
		# log_file("move.bug", sprintf("%O encumbrance underflow.\n", this_object()));
	if( encumb > max_encumb ) :
		this_object().over_encumbrance();
	if( environment() ) :
		environment().add_encumbrance(w);

func over_encumbrance():
#	if( !interactive(this_object()) ) :
#		return;
	tell_object(this_object(), "你的负荷过重了！\n");

func query_weight() :
	return weight
func set_weight(w:int):
	if( !environment() ) :
		weight = w;
		return;
	if( w!=weight ) :
		environment().add_encumbrance( w - weight );
	weight = w;

# This is the "current" weight of an object, which is used on weight
# checking in move().
func weight() :
	return weight + encumb;

func move(dest, silently:int = 1):
	var ob
	var env
	var inv
	var me = this_object()
	var where = environment()
	var exits
	var str1
	var dirs
#	var time = NATURE_D.game_time()
	var i
	var w

	# If we are equipped, unequip first.
	if( query("equipped") && !me.unequip() ):
		return notify_fail("你没有办法取下这样东西。\n");

	# Find the destination ob for moving.
	if( objectp(dest) ):
		ob = dest;
	elif( stringp(dest) ) :
#		call_other(dest, "???");
#		ob = find_object(dest);
		if(!ob) :
			return notify_fail("move: destination unavailable.\n");
	else:
		return notify_fail(sprintf("move: invalid destination %O.\n", dest));

	# Check if the destination ob can hold this object.
	# Beforce checking it, we check if the destination is environment of
	# this_object() (or environment of its environment). If it is, then
	# this could be like get something from a bag carried by the player.
	# Since the player can carry the bag, we assume he can carry the this
	# object in the bag and encumbrance checking is unessessary.
	env = me;
	
	while(environment(env)) :
		env = environment(env)
		if( env==ob ) :
			break;
	if( !env && ob.query_encumbrance() + weight() > ob.query_max_encumbrance() ):
		if( ob==this_object() ):
			return notify_fail(me.name() + "对你而言太重了。\n");
		else:
			return notify_fail(me.name() + "对" + ob.name() +"而言太重了。\n");

	# Move the object and update encumbrance
	w = weight();
	if( environment() ) :
		environment().add_encumbrance( - w);
	move_object(ob);
	if( !me) :
		return 0;
	ob.add_encumbrance(w);

	return 1;		

# TODO. 先测试，后完善
#func move_object(ob):
#	print_debug(ob.name())
#	self.add_temp("objects",ob)

########################################  name ####################
func set_name_cn(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2

#var my_id
func set_name(name,id):
	set("name", name);
	set("id", id);
#	dbase.name = name
#	dbase.id = id
	my_id = id;

func name(raw=true):
	var st
	var mask;
	mask = query_temp("apply/name")
	if( !raw && sizeof(mask) ):
		return mask[sizeof(mask)-1];
	else:
		st = query("name")
		if( stringp(st) ):
			return st;
		else:
			return file_name(this_object());

func short(raw=true):
	var party;
	var guard
	var degree
	var party_title
	var title
	var nick
	var string
	var str1
	var mask;
	string = query("short")
	if !stringp(string) :
		string = name(raw) + "(" + query("id") + ")";

	return string
	pass

func long(raw=1):
	var st
	var extra
	var mask;
	mask = query_temp("apply/long")
	if( !raw && sizeof(mask) ):
		st = mask[sizeof(mask)-1];
	elif( !stringp(query("long")) ):
		st = short(raw) + "。\n";
	
	extra = this_object().extra_long()
	if( stringp(extra) ):
		st += extra;

	return st;

func extra_long():
	# todo
	pass		


