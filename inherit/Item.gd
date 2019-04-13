extends GameObject

class_name Item
#
#// item.c
#
##include <dbase.h>
##include <move.h>
##include <name.h>
#
#inherit F_CLEAN_UP;
#inherit F_DBASE;
#inherit F_MOVE;
#inherit F_NAME;
#
#void setup()
#{
#	seteuid(getuid());
#	set("weight",100);
#}

func setup():
	setuid(getuid())
	set("weight",100)

########################################  move #####################################
var weight : int = 0
var encumb : int = 0
var max_encumb : int = 0
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
#		todo
#	me.remove_all_enemy();  # by qingyun
	ob.add_encumbrance(w);

	##################################
# 	# If we are players, try look where we are.
# 	if( interactive(me)			# are we linkdead?
# 		&& living(me)			# are we still concious?
# 		&& !me.query_temp("noliving")	# are we still concious?
# 		&& userp(me)			# are we still concious?
# 		&& !silently )
# 	{
# 		if( query("env/brief") )
# 		{
# 			tell_object(me, HIC+environment().query("short") + NOR + " -\n");
# 		}
# 		else
# 		if( query("env/brief1") )
# 		{
# 			str = HIC+environment().query("short") + NOR + " -\n";
# 			inv = all_inventory(environment());
# 	  if (sizeof(inv)<20)
# 			  for(i=0; i<sizeof(inv); i++)
# 			  {
# 				  if( inv[i]==me ) continue;
# 				  if( inv[i].query("no_shown")) continue;
# 				  if( !me.visible(inv[i]) ) continue;
# 				  str += "  " + inv[i].short() + "\n";
# 			  }
# 	  else
# 		str += listob(inv);
# 			 tell_object(me, str);
# 		}
# 		else
# 		if( query("env/brief2") )
# 		{
# 			str = HIC+environment().query("short") + NOR + " -\n";
# 			inv = all_inventory(environment());
# 	  if (sizeof(inv)<20)
# 			  for(i=0; i<sizeof(inv); i++) 
# 			  {
# 				  if( inv[i]==me ) continue;
# 				   if( inv[i].query("no_shown")) continue;
# 				  if( !me.visible(inv[i]) ) continue;
# 				  str += "  " + inv[i].short() + "\n";
# 			  }
# 	  else
# 		str += listob(inv);
# 			if( mapp(exits = environment().query("exits")) )
# 			{
# 				dirs = keys(exits);
# /*				for(i=0; i<sizeof(dirs); i++)
# 					if( (int)env.query_door(dirs[i], "status") & DOOR_CLOSED ) dirs[i] = 0;
# 				dirs -= ({ 0 });
# */
# 				if ( environment().query("outdoors") &&
# 					!present("fire", this_object()) &&
# 					!wizardp(this_object()) &&
# 					((strsrch(time, "亥时") >= 0) ||
# 					 (strsrch(time, "子时") >= 0) ||
# 					 (strsrch(time, "丑时") >= 0) ||
# 					 (strsrch(time, "寅时") >= 0) ))
# 					str += "    天色太黑了，你看不清明显的出路。\n";
# 				else if( sizeof(dirs)==0 )
# 					str += "    这里没有任何明显的出路。\n";
# 				else if( sizeof(dirs)==1 )
# 					str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
# 				else
# 					str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
# 					implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
# 			}
# 			tell_object(me, str);
# 		}
# 		else
# 			command("look");
# 	}

	return 1;		


########################################  name ####################
func set_name_cn(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2

var my_id
func set_name(name,id):
	set("name", name);
	set("id", id);
	my_id = id;

func name(raw=1):
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

func short(raw=1):
	var party;
	var guard
	var degree
	var party_title
	var title
	var nick
	var string
	var str1
	var mask;
#
#	if( !stringp(string = query("short")) ):
#		string = name(raw) + "(" + capitalize(query("id")) + ")";
#
#	if( !this_object().is_character() ) :
#		return string;
#
#	if (!raw) :
#		if (query_temp("pending/exercise") != 0):
#			return name() + "正坐在地下修炼内力。";
#		elif (query_temp("pending/respirate") != 0):
#			return name() + "正坐在地下吐纳炼精。";
#	}
#
#        if( !raw && sizeof(mask = query_temp("apply/short")) ):
#                str = str(mask[sizeof(mask)-1]);
##	if( !raw && stringp(str1 = (string)query_temp("apply/short")) ) {
##		str = (string)mask[sizeof(mask) - 1];
##		return (string)query_temp("apply/short");
##		if (stringp(str1))
##		  	str += str1;
##	}
#	else: 
#		if( stringp(nick = query("nickname")) ):
#			str = sprintf("「%s」%s", nick, str);
#
#		if( stringp(title = query("title")) ) :
#			# 叛师过的无门派人士改称隐士。Modified by Spacenet@FXLT
#			if (title == "普通百姓" && query("betrayer")):
#				title = "隐士";
#			str = sprintf("%s%s%s", title,(nick?"":" "), str);
#		if ( mapp(party = query("party")) ) :
#			party_title = party["party_name"] + party["rank"];
#			str=sprintf("%s%s%s%s", party_title,(title?"":""),(nick?"":" "), str);
#		if ( stringp(degree = query("degree")) ) :
#			str = sprintf("%s%s%s%s%s",degree,(party_title?"":""),(title?"":""),(nick?"":" "), str);
#		if ( stringp(guard = query("guard")) ) :
#			str = sprintf("%s%s%s%s%s%s",guard,(degree?"":""),(party_title?"":""),(title?"":""),(nick?"":" "), str);
#
#	if( !raw ) :
#		if( this_object().is_ghost() ) :
#			str = HIB "(鬼气) " NOR + str;
#		# if( query_temp("netdead") ) :
#		# 	str += HIG" <断线中>" NOR;
#		# if( in_input() ) str += HIC" <输入文字中>" NOR;
#		# if( in_edit() ) str += HIY" <编辑档案中>" NOR;
#		# if( query_temp("boss_screen") ) :
#		# 	str += HIG" <逃避老板中>" NOR;
#		if( query_temp("bixie/cimu") ) :
#			str += HIR + " <失明中>" + NOR;
#		if( query_temp("noliving/sleeped") ) :
#			str += HIR + " <睡梦中>"  + NOR;
#		if( query_temp("noliving/fakedie") ) :
#			str += HIR + " <装死中>"  + NOR;
#		if( query_temp("noliving/jingzuo") ) :
#			str += HIR + " <静坐中>"  + NOR;
#		if( query_temp("noliving/journey") ) :
#			str += HIR + " <旅途中>"  + NOR;
#		if( query_temp("noliving/unconcious") ):
#			str += HIR + " <昏迷不醒>" +  NOR;
#		if( interactive(this_object()) && query_idle(this_object())>120):
#			str += HIM +  " <发呆中>"  + NOR;
#		if( !living(this_object()) ):
#			str += HIR + query("disable_type") + NOR;
#	return str;
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

#############################  combined  #################################

var amount;

func query_amount() :
	return amount;

func destruct_me() :
	destruct(this_object())

func set_amount(v:int):
	if( v < 0 ) error("combine:set_amount less than 1.\n");
# //	if( v==0 ) destruct(this_object()); 
	if( v==0 ) :
		# ::move(VOID_OB);
		call_out("destruct_me", 1);
	else :
		amount = v;
		this_object().set_weight(v * int(query("base_weight")));

func add_amount(int v) :
	set_amount(amount+v)

func short():
	if (query_amount()>1):
		return chinese_number(query_amount()) + query("base_unit") + ::short();
	else:
		return ::short();

func move(mixed dest, int silent):
	var env
	var inv;
	var i
	var total;
	var file;

	if( ::move(dest, silent) ) {
#		if( living(env = environment()) ) {
		env = environment();
		file = base_name(this_object());
		inv = all_inventory(env);
		total = (int)query_amount();
		for(i=0; i<sizeof(inv); i++) :
			if( inv[i]==this_object() ) :
				continue;
			if( base_name(inv[i])==file ) :
				total += (int)inv[i].query_amount();
				destruct(inv[i]);
		set_amount(total);
		return 1;
