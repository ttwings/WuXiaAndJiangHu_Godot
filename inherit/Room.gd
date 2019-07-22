extends GameObject

class_name Room

var doors = {};

func query_max_encumbrance():
	return 100000000000

func make_inventory(file:String):
	var ob;

#	ob = new_ob(file);
	ob = load(file).new()
	ob.move(this_object());
	ob.set("startroom", file_name(this_object()));
	return ob;

func reset():
	var ob_list
	var ob
	var list
	var i
	var j

	#
	# Check loaded objects to match the objects specified in "objects"
	# while query("objects") is 
	# ([ <object filename>: <amount>, ..... ])
	# and query_temp("objects") is
	# ([ <object filename>: ({ob1, ob2, ...}), .... ])
	#
	set("no_clean_up", 0);
	ob_list = query("objects");
	if( !mapp(ob_list) ) :
		return;
	ob = query_temp("objects")
	if( !mapp(ob) ):
#        ob = allocate_mapping(sizeof(ob_list));
		ob = []
	list = keys(ob_list);
	# for(i=0; i<sizeof(list); i++) {
#	for i in sizeof(list) :
#		# Allocate an array if we have multiple same object specified.
#		if(intp(ob_list[list[i]]) && ob_list[list[i]] > 1 ):
#			ob[list[i]] = ob_list[list[i]];


		#  todo    
		# match(ob_list[list[i]]) :
		#     1:  if( !ob[list[i]] ):
		#         ob[list[i]] = make_inventory(list[i]);
		#         if( environment(ob[list[i]]) != this_object() && ob[list[i]]->is_character() ) :
		#         if( !ob[list[i]]->return_home(this_object()) )
		#             add("no_clean_up", 1);
		#     }
		#     break;
		# default:
		#     for(j=0; j<ob_list[list[i]]; j++) {
		#         # If the object is gone, make another one.
		#         if( !objectp(ob[list[i]][j]) ) {
		#             ob[list[i]][j] = make_inventory(list[i]);
		#             continue;
		#         }
		#         # Try to call the wandering npc come back here.
		#         if( environment(ob[list[i]][j]) != this_object()
		#         &&	ob[list[i]][j]->is_character() ) {
		#             if( !ob[list[i]][j]->return_home(this_object()) )
		#                 add("no_clean_up", 1);
		#         }
		#     }
		# }
#    }
	set_temp("objects", ob);
#}

func _init():
	self.reset();
	create()