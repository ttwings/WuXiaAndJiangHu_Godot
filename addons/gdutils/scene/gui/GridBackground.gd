@tool
extends TextureRect
@export var color1 = Color("#666666"): set = _set_color1
@export var color2 = Color("#999999"): set = _set_color2
@export var cell_size: int = 10: set = _set_cell_size

var grid_texture = preload("../../resource/GridBackgroundTexture.gd").new()

func _init():
	self.texture = grid_texture
	self.expand = true
	self.stretch_mode = TextureRect.STRETCH_TILE

func _set_color1(p_color):
	color1 = p_color
	grid_texture.color1 = p_color

func _set_color2(p_color):
	color2 = p_color
	grid_texture.color2 = p_color

func _set_cell_size(p_size):
	cell_size = p_size
	var cell_size_dpi_related = int(p_size * DisplayServer.screen_get_dpi() / 72.0)
	grid_texture.cell_size = cell_size_dpi_related


