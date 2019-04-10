inherit ROOM;

void init()
{
	add_action("do_knock", "knock");
	add_action("do_push",  "push");
}
int is_open() {return stringp(query("exits/"+query("door_dir")));}
varargs void open_door(object ob)
{
	if (objectp(ob))
		set("exits/"+query("door_dir"),ob);
	else
	  set("exits/"+query("door_dir"),query("restroom"));
}
void close_door(){	delete("exits/"+query("door_dir"));}

int close_men()
{
	object room;

	room = find_object(query("restroom"));
	if(!objectp(room)) room = load_object(query("restroom"));
	if(objectp(room))
	{
		if (  is_open() ) 
		{
			close_door();
			message("vision", query("door_name")+"吱吱呀呀地自己合上了。\n", this_object());
			room->close_door();
			message("vision", query("door_name")+"吱吱呀呀地自己合上了。\n", room);
		}
	}
	else message("vision", "发现错误，请通知巫师解决。.\n", room);
}

int do_knock(string arg)
{
	object room;

	if (is_open())
	return notify_fail(query("door_name")+"已经是开着了。\n");

	if (!arg || (arg != "door" && arg != "men"))
	return notify_fail("你要敲什么？\n");

	room = find_object(query("restroom"));
	if(! objectp(room) )
	room = load_object(query("restroom"));	

	if(objectp(room))
	{
		message("vision","外面传来一阵敲门声，你从门缝往外一瞧，是"+this_player()->query("name")+"一脸焦急地站在门外，\n看样子也想进来休息。\n", room);
		if (room->query_sleeping_person() > 0)
		{
		message_vision(
"$N刚轻轻地敲了一下门，就听见里面传出一阵雷鸣般的鼾声，\n"
"显然里面的人睡得跟死猪似的，怎么敲都没用了。\n",
			this_player());
		}
		else if (room->query_inside_person() > 0)
		{
			switch( random(2) )
			{
				case 0:
				message_vision(
"$N轻轻地敲了敲门，只听见里面有人很不耐烦地吼到：\n"
"“刚躺下就来敲门！我睡着了，听不见！！！”\n",	this_player());
					break;
				case 1: 
					message_vision(
"$N轻轻地敲了敲门，只听见里面有些响动，\n"
"好象有人在踱来踱去，拿不定主意是否开门。\n", this_player());
					break;
			}	   	
		}
		else
		{
		message_vision("$N轻轻地敲了敲门：咚、咚、咚．．．咚、咚、咚．．．\n",this_player());
		}
	}
	return 1;
}

int do_push(string arg)
{
	object room;

	if (is_open())
	return notify_fail("门已经是开着了。\n");

	if (!arg || (arg != "door" && arg != "men"))
	return notify_fail("你要推什么？\n");

	room = find_object(query("restroom"));
	if(! objectp(room) )
	room = load_object(query("restroom"));	
	
	if(objectp(room))
	{
		if( room->query_inside_person()<=0 )
		{
			open_door();
			message_vision("$N轻轻地把门推开。\n", this_player());
			room->open_door(__FILE__);
			remove_call_out("close_men");
			call_out("close_men", 10);
		}
		else 
		{
			message_vision("$N想把门推开，却发觉门被人从里面闩上了。\n",this_player());
		}
	}

	return 1;
}

string look_men()
{
	object room;

	if (is_open()) return (query("open_door_msg"));

	if(!objectp( room = find_object(query("restroom"))) )
	room = load_object(query("restroom"));

	if( objectp(room) && room->query_person_inside() > 0 )
		return (query("inside_msg"));
	return (query("no_one_msg"));
}


