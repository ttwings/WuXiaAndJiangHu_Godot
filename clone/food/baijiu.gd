extends Food

func create():
	set_name_cn("粗磁酒瓶","cu_ci_jiu_ping");
	set_weight(800);
#  if (clonep())
#    set_default_object(__FILE__);
#  else
	set_attr("long", "一个用来装酒的粗磁酒瓶，能装两，三斤白酒。\n");
	set_attr("unit", "个");
	set_attr("value", 100);
	set_attr("max_liquid", 15);
	set_attr("liquid", {
        "type": "alcohol",
        "name": "老白干",
        "remaining": 15,
        "drunk_supply": 15,
    });
