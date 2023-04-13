# 店铺伙计程序

# inherit NPC;
extends Npc

func is_waiter():
	return 1;


# 修改属性
func do_modify(arg:String):
	write(SHOP_D.do_modify(this_object(), this_player(), arg));
	return 1;


# 标价货物
func do_stock(arg:String):
	write(SHOP_D.do_stock(this_object(), this_player(), arg));
	return 1;


# 取下货物
func do_unstock(arg:String):
	write(SHOP_D.do_unstock(this_object(), this_player(), arg));
	return 1;


# 查询货物列表
func do_list(arg:String):
	write(SHOP_D.do_list(this_object(), this_player(), arg));
	return 1;


# 购买货物
func do_buy(arg:String):
	return SHOP_D.do_buy(this_object(), this_player(), arg);


# 店主结帐
func do_jiezhang():
	write(SHOP_D.do_jiezhang(this_object(), this_player()));
	return 1;


# 设置、查询贵宾
func do_invite(arg:String):
	var msg;
	if (arg):
			msg = SHOP_D.do_invite(this_object(), this_player(), arg);
	else:
			msg = SHOP_D.list_invite(this_object(), this_player());
	write(msg);
	return 1;


# 设置、查询贵宾
func do_ban(arg:String):
	var msg;
	if (arg):
			msg = SHOP_D.do_ban(this_object(), this_player(), arg);
	else:
			msg = SHOP_D.list_ban(this_object(), this_player());
	write(msg);
	return 1;


#预约商品
func do_order(arg:String):
	var msg;
	if (arg):
			msg = SHOP_D.do_order(this_object(), this_player(), arg);
	else:
			msg = SHOP_D.list_order(this_object(), this_player());
	write(msg);
	return 1;


func init():
	if (this_player().query("id") == environment().query("owner")):
			add_action("do_stock", "stock");
			add_action("do_unstock", "unstock");
			add_action("do_jiezhang", ({ "reckoning", "jiezhang"));
			add_action("do_modify", "modify");
			add_action("do_invite", ({ "invite", "vip" ));
			add_action("do_ban", ({ "ban", "unwelcome", ));
	
	add_action("do_order","order");
	add_action("do_list", "list");
	add_action("do_buy", "buy");


func die():
	return;


func unconcious():
	die();


func restore():
	var file;
	if (stringp(file = this_object().query_save_file()) && file_size(file + __SAVE_EXTENSION__) > 0):
			return restore_object(file);
	return 0;

