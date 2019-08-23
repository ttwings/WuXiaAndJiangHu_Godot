# /*  <SecCrypt CPL V3R05>  */
 
# //

#include  <ansi.h>

# inherit  ITEM;
extends Item

var prefixs  = ["锦面","缎面","鹅绒","丝绣",]
var names  =  ["","大","扶手","靠背","折叠","安乐",]
var suffixs  =  ["长椅","躺椅",]

func create():
	set_name(prefixs[random(sizeof(prefixs))]+names[random(sizeof(names))]+suffixs[random(sizeof(suffixs))], "chair");
	set_weight(28000);
	set("long",  "这是一把椅子。\n"  );
	set("unit",  "把");
	set("material",  "stone");
	set("value",  2000);
	set("no_sell",  1);
	set("no_get",  1);
	setup();

func _init():
	create()
	var me = this_object();
	var where = environment(me);
#	if  (where  &&  userp(where)):
#		remove_call_out("destruct_me");
#		call_out("destruct_me",900+random(900),me);

func  destruct_me(me):
	destruct(me);

func sizeof(array):
	if not array is Array :
		return 0
	else:
		return array.size()
		
func random(n:int):
	return randi()%n		