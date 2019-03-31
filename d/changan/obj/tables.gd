extends Item
var prefixs  = [
	"大",
	"小",
	"黑",
	"方",
	"圆",
	"白漆",
	"青漆",
	"紫漆",
]

var names  = [
	"木",
	"仙",
	"镶玉",
	"兽脚",
]

var suffixs  = [
	"桌",
	"案",
]

func create():
#    set_name(prefixs[random(sizeof(prefixs))]+names[random(sizeof(names))]+suffixs[random(sizeof(suffixs))], {  "table"  }));
	set_weight(30000);
	set("long",  "这是一张桌子。\n"  );
	set("unit",  "张");
	set("material",  "stone");
	set("value",  2000);
	set("no_sell",  1);
	set("no_get",  1);

func init():
	var me  =  this_object();
	var where  =  environment(me);
#	if(where  &&  userp(where)):
#		remove_call_out("destruct_me");
#		call_out("destruct_me",900+random(900),me);

func destruct_me(me):
	destruct(me);
