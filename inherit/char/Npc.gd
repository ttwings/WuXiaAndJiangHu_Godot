extends Char
class_name Npc

func carry_object(file):
	var ob
	ob = new_ob(file)
	if( !objectp(ob) ) :
		return 0;
	# 将物品移动到人物身上
	ob.move(this_object());
	return ob;
	
func add_money(type:String,amount:int):
	var ob;

	ob = carry_object("/clone/money/" + type);
	if( !ob ) :
		return 0;
	ob.set_amount(amount);

# This function is called by the reset() of the room that creates this
# npc. When this function is called, it means the room demand the npc
# to return its startroom.
func return_home(home:Room):
	# Are we at home already?
	if( !environment() || environment()==home ):
		return 1;

	# Are we able to leave?
	if(!living(this_object()) || this_object().query_temp("noliving") || is_fighting() ):
		return 0;
		
	# let me leave ,add by sir
	if( !mapp(environment().query("exits")) && this_object().query_temp("let_me_leave")<=5 ):
		this_object().add_temp("let_me_leave",1);
		return 0;

	# Leave for home now.
	message("vision", this_object().name() + "急急忙忙地离开了。\n",environment(), this_object());
	return move(home);

# This is the chat function dispatcher. If you use function type chat
# message, you can either define your own functions or use the default
# ones.
func chat():
	var msg;
	var chance
	var rnd;

	if( !environment() ) :
		return 0;
	var str1 = "chat_chance_combat"  if is_fighting() else  "chat_chance"
	chance = int(query(str1))
	if( chance < 0):
		return 0;
	msg = query("chat_msg_combat" if is_fighting()  else "chat_msg")	
	if( arrayp(msg)):
		if( random(100) < chance ):
			rnd = random(sizeof(msg));
			if( stringp(msg[rnd]) ):
				say(msg[rnd]);
			elif( functionp(msg[rnd]) ):
				return evaluate(msg[rnd]);
		return 1;

# Default chat function: Let the npc random move to another room.
func random_move():
	var exits;
	var dirs;
	exits = environment().query("exits")
	if( !mapp(exits) ) :
		return 0;
	dirs = keys(exits);
	command("go " + dirs[random(sizeof(dirs))]);