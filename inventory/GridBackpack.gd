extends TextureRect

var items = []

var grid = {}
var cell_size =  32
var grid_width = 0
var grid_height = 0

func _ready() -> void:
	var s = get_grid_size(self)
	grid_width = s.x
	grid_height = s.y
	
	for x in range(grid_width):
		grid[x] = {}
		for y in range(grid_height):
			grid[x][y] = false
			
func insert_item(item):
	var item_pos = item.rect_global_position + Vector2(cell_size / 2,cell_size / 2)
	var g_pos = pos_to_grid_coord(item_pos)
	var item_size = get_grid_size(item)			
	if is_grid_space_available(g_pos.x, g_pos.y, item_size.x, item_size.y):
		set_grid_space(g_pos.x, g_pos.y, item_size.x, item_size.y, true)
		item.rect_global_position = rect_global_position + Vector2(g_pos.x, g_pos.y) * cell_size
		items.append(item)
		return true
	else:
		return false

func grab_item(pos):
	var item = get_item_under(pos)
	if item == null:
		return
		
	var item_pos = item.rect_global_position + Vector2(cell_size / 2, cell_size / 2)
	var g_pos = pos_to_grid_coord(item_pos)
	var item_size = get_grid_size(item)
	set_grid_space(g_pos.x, g_pos.y, item_size.x, item_size.y, false)
	
	items.remove(items.find(item))
	update()
	print_debug(items.size())
	return item	
		
		
		
		
func get_item_under(pos):
	for item in items:
		if item.get_global_rect().has_point(pos):
			return item
	return null	

func set_grid_space(x, y, w, h, state):
	for i in range(x, x + w):
		for j in range(y , y + h):
			grid[i][j] = state
	
func is_grid_space_available(x, y, w, h):
	if x < 0 or y < 0 :
		return false
	if x + w >  grid_width or y + h > grid_height :
		return false
	for i in range(x, x + w):
		for j in range(y, y + h):
			if grid[i][j]:
				return false
	return true	
	
	
func pos_to_grid_coord(pos):
	var local_pos = pos - rect_global_position
	
	var results = {}
	results.x = int(local_pos.x / cell_size)
	results.y = int(local_pos.y / cell_size)
	print_debug(results)
	return results	
	
	
func get_grid_size(item):
	var results = {}
	var s = item.rect_size
	results.x = clamp(int(s.x / cell_size),1,500)
	results.y = clamp(int(s.y / cell_size),1,500)
	return results
	
		
func insert_item_first_available_spot(item):
	for y in range(grid_height):
		for x in range(grid_width):
			if !grid[x][y]:
				item.rect_global_position = rect_global_position + Vector2(x,y) * cell_size
				if insert_item(item):
					return true
	return false	
	
func _draw() -> void:
	for i in range(grid_width):
		for j in range(grid_height):
			if grid[i][j]:
				draw_circle(Vector2(i,j)*cell_size + Vector2(cell_size/2,cell_size/2),8,Color.red)	