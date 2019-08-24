tool
extends EditorPlugin

var TranslationEditor = load("res://addons/zylann.translation_editor/tools/translation_editor.tscn")

var _main_control = null


func _enter_tree():
	print("Translation editor plugin Enter tree")
	
	var editor_interface = get_editor_interface()
	var base_control = editor_interface.get_base_control()
	
	_main_control = TranslationEditor.instance()
	_main_control.configure_for_godot_integration(base_control)
	_main_control.hide()
	editor_interface.get_editor_viewport().add_child(_main_control)


func _exit_tree():
	print("Translation editor plugin Exit tree")
	# The main control is not freed when the plugin is disabled
	_main_control.queue_free()
	_main_control = null


func has_main_screen():
	return true


func get_plugin_name():
	return "Localization"


func get_plugin_icon():
	return preload("icons/icon_translation_editor.svg")


func make_visible(visible):
	_main_control.visible = visible


