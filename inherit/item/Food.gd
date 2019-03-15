extends GameObject

class_name Food

func do_eat(player):
#	if( !living(this_player()) || this_player()->query_temp("noliving") )
#		return 1;
#	if( this_player()->query("jing")<0 || this_player()->query("qi")<0 )
#		return notify_fail("你太累了，实在没力气吃什么了。\n");
#	if( !this_object()->id(arg) ) return 0;
#	if( !present(this_object(), this_player()))
#		return notify_fail("你要吃什么东西？\n");
#	if( this_player()->is_busy() )
#		return notify_fail("别急，慢慢吃，小心别噎着了。\n");
#	if( !query("food_remaining") )
#		return notify_fail( name() + "已经没什么好吃的了。\n");
#	if( (int)this_player()->query("food") >=
#		(int)this_player()->max_food_capacity() )
#		return notify_fail("你已经吃太饱了，再也塞不下任何东西了。\n");

	Global.this_player().add("food", 30);
	print(query("food_supply"))
	print_debug(Global.this_player().query("food"))
#	if( this_player()->is_fighting() ) this_player()->start_busy(2);
#
#	// This allows customization of drinking effect.
#	if( query("eat_func") ) return 1;
#
	set("value", 0);
	if query("food_remaining") > 0 :
		add("food_remaining", -1);
	if( query("food_remaining") <= 0 ):
		return message_vision("$N将剩下的"+name()+"吃得干干净净。\n",player);
#		if( !this_object().finish_eat() ):
		destruct(this_object());
	else:
		return message_vision("$N拿起" + name()+"咬了几口。\n",player);
#//	this_player()->start_busy(1);
#	return 1;
#}
	# print("do_eat")
	pass
