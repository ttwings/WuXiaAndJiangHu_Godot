@tool

extends ImageTexture

@export var color1 = Color("#666666"): set = _set_color1
@export var color2 = Color("#999999"): set = _set_color2

@export var cell_size: int = 10: set = _set_cell_size

func _init():
	_update_image()

func _set_cell_size(p_size):
	cell_size = p_size
	_update_image()

func _set_color1(p_color):
	color1 = p_color
	_update_image()

func _set_color2(p_color):
	color2 = p_color
	_update_image()

func _update_image():
	var image = Image.new()
	image.create(cell_size * 2, cell_size * 2, false, Image.FORMAT_RGBA8)
	image.fill(color2)
	false # image.lock() # TODOConverter40, Image no longer requires locking, `false` helps to not break one line if/else, so it can freely be removed
	for x in range(cell_size):
		for y in range(cell_size):
			image.set_pixel(x, y, color1)
	for x in range(cell_size, cell_size * 2):
		for y in range(cell_size, cell_size * 2):
			image.set_pixel(x, y, color1)
	false # image.unlock() # TODOConverter40, Image no longer requires locking, `false` helps to not break one line if/else, so it can freely be removed
	create_from_image(image)
