extends Food


func create():
	set_name_cn("细雕青竹筒","xi_diao_zhu_tong");
	set_weight(600);
#  if( clonep() )
#    set_default_object(__FILE__);
#  else {
	set("long", "这是一根尺把长的三节蟠虬雕花青竹筒。\n");
	set("unit", "根");
	set("value", 120);
	set("max_liquid", 100); 
	set("wield_msg", "$N抽出细雕青竹筒，顺手晃荡了一下里面的水。\n");
	set("unwield_msg", "$N将细雕青竹筒插回腰间。\n");
	set("liquid", {
    	"type": "water",
		"name": "清泉碧竹茶",
		"remaining": 90,
  	} );
#  init_stick(2);
#  setup();

func _init():
	create()