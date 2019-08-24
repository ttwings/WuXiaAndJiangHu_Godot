tool
extends WindowDialog

const Locales = preload("locales.gd")

signal language_selected(language)

onready var _filter_edit = get_node("VBoxContainer/FilterEdit")
onready var _languages_list = get_node("VBoxContainer/LanguagesList")
onready var _ok_button = get_node("VBoxContainer/Buttons/OkButton")

var _hidden_locales = []


func configure(hidden_locales):
	_hidden_locales = hidden_locales
	refresh_list()


func refresh_list():
	_languages_list.clear()
	
	var filter = _filter_edit.text.strip_edges()
	var locales = Locales.get_all_locales()

	# Hidden root
	_languages_list.create_item()
	
	for locale in locales:
		if _hidden_locales.find(locale[0]) != -1:
			continue
		if filter != "" and locale[0].findn(filter) == -1:
			continue
		var item = _languages_list.create_item()
		item.set_text(0, locale[0])
		item.set_text(1, locale[1])
	
	_ok_button.disabled = true


func submit():
	var item = _languages_list.get_selected()
	emit_signal("language_selected", item.get_text(0))
	hide()


func _on_OkButton_pressed():
	submit()


func _on_CancelButton_pressed():
	hide()


func _on_LanguagesList_item_selected():
	_ok_button.disabled = false


func _on_LanguagesList_nothing_selected():
	_ok_button.disabled = true


func _on_LanguagesList_item_activated():
	submit()


func _on_FilterEdit_text_changed(new_text):
	refresh_list()
