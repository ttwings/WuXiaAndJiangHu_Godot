inherit ROOM;

void init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
	remove_call_out("force_open");
	call_out("force_open",300);
}

int is_open() {return stringp(query("exits/"+query("door_dir")));}
varargs void open_door(object ob)
{
	if (objectp(ob))
		set("exits/"+query("door_dir"),ob);
	else
	  set("exits/"+query("door_dir"),query("outroom"));
}
void close_door(){	delete("exits/"+query("door_dir"));}
int query_inside_person()
{
	object *inv;
	int i,count;
	
	inv = all_inventory();
	count = 0;
	for (i=0;i<sizeof(inv);i++)
		if (userp(inv[i])) count++;
	
	return count;
}
int query_sleeping_person()
{
	object *inv;
	int i,count;
	
	inv = all_inventory();
	count = 0;
	for (i=0;i<sizeof(inv);i++)
		if (userp(inv[i]) && inv[i]->query_temp("noliving/sleeped")) count++;
	
	return count;
}

void close_men()
{
	object room;

	if(!objectp( room = find_object(query("outroom")) ))
		room = load_object(query("outroom"));
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
}

int do_close(string arg)
{
	if ( !is_open() )
		return notify_fail("门已经是关着的了。\n");

	if (!arg || (arg != "men" && arg != "door"))
		return notify_fail("你要关什么？\n");

	message_vision("$N想把门关上。\n", this_player());

	remove_call_out("close_men");
	call_out("close_men", 0);

	return 1;
}

int do_open(string arg)
{
	object room;
	object me = this_player();

	if (is_open())
		return notify_fail("大门已经是开着了。\n");

	if (!arg || (arg != "men" && arg != "door" && arg != query("door_dir")))
		return notify_fail("你要开什么？\n");

	if(!objectp( room = find_object(query("outroom"))) )
		room = load_object(query("outroom"));
	if(objectp(room))
	{
		open_door();
		message_vision("$N轻手轻脚地把门打开。\n", this_player());
		room->open_door(__FILE__);
		
		if (me->query_temp("sleeped"))
		message("vision", "吱地一声，"+me->query("name")+"精神焕发地从里面把门打开了。\n",room);
		else
		message("vision", "梆地一声，"+me->query("name")+"从里面把门打开，一脸的不耐烦。\n",room);
		
		remove_call_out("close_men");
		call_out("close_men", 10);
	}

	return 1;
}

int force_open()
{
	object room;
	if(!objectp( room = find_object(query("outroom"))) )
		room = load_object(query("outroom"));
	if( !objectp(room) )	return 0;
	if( query_inside_person() <= 0 )	return 0;
	
	open_door();
	room->open_door(__FILE__);
	message("vision","外面突然响起粗重的脚步声，由远而近，到门前停了下来．．．\n"+query("force_name")+"啪地把门打开，伸个头进来，一脸狐疑：呆大半天了还不出去，搞什么鬼？\n", room);
	remove_call_out("close_men");
	call_out("close_men", 10);
}