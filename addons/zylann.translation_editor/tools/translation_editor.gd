tool
extends Panel

const CsvLoader = preload("csv_loader.gd")
const PoLoader = preload("po_loader.gd")
const Locales = preload("locales.gd")
const StringEditionDialog = preload("string_edition_dialog.tscn")
const LanguageSelectionDialog = preload("language_selection_dialog.tscn")
const ExtractorDialog = preload("extractor_dialog.tscn")

const MENU_FILE_OPEN = 0
const MENU_FILE_SAVE = 1
const MENU_FILE_SAVE_AS_CSV = 2
const MENU_FILE_SAVE_AS_PO = 3
const MENU_FILE_ADD_LANGUAGE = 4
const MENU_FILE_REMOVE_LANGUAGE = 5
const MENU_FILE_EXTRACT = 6

const FORMAT_CSV = 0
const FORMAT_GETTEXT = 1

onready var _file_menu = get_node("VBoxContainer/MenuBar/FileMenu")
onready var _edit_menu = get_node("VBoxContainer/MenuBar/EditMenu")
onready var _search_edit = get_node("VBoxContainer/Main/LeftPane/Search/Search")
onready var _clear_search_button = get_node("VBoxContainer/Main/LeftPane/Search/ClearSearch")
onready var _string_list = get_node("VBoxContainer/Main/LeftPane/StringList")
onready var _translation_tab_container = \
	get_node("VBoxContainer/Main/RightPane/VSplitContainer/TranslationTabContainer")
onready var _notes_edit = get_node("VBoxContainer/Main/RightPane/VSplitContainer/VBoxContainer/NotesEdit")
onready var _status_label = get_node("VBoxContainer/StatusBar/Label")

var _string_edit_dialog = null
var _language_selection_dialog = null
var _remove_language_confirmation_dialog = null
var _remove_string_confirmation_dialog = null
var _extractor_dialog = null
var _open_dialog = null
var _save_file_dialog = null
var _save_folder_dialog = null
# This is set when integrated as a Godot plugin
var _base_control = null
var _translation_edits = {}
var _dialogs_to_free_on_exit = []

var _data = {}
var _languages = []
var _current_path = null
var _current_format = FORMAT_CSV
var _modified_languages = {}


func _ready():
	# I don't want any of this to run in the edited scene (because `tool`)...
	if Engine.editor_hint and get_parent() is Viewport:
		return
	
	_file_menu.get_popup().add_item("Open...", MENU_FILE_OPEN)
	_file_menu.get_popup().add_item("Save", MENU_FILE_SAVE)
	_file_menu.get_popup().add_item("Save as CSV...", MENU_FILE_SAVE_AS_CSV)
	_file_menu.get_popup().add_item("Save as PO...", MENU_FILE_SAVE_AS_PO)
	_file_menu.get_popup().add_separator()
	_file_menu.get_popup().add_item("Add language...", MENU_FILE_ADD_LANGUAGE)
	_file_menu.get_popup().add_item("Remove language", MENU_FILE_REMOVE_LANGUAGE)
	_file_menu.get_popup().add_separator()
	_file_menu.get_popup().add_item("Extractor", MENU_FILE_EXTRACT)
	_file_menu.get_popup().set_item_disabled(_file_menu.get_popup().get_item_index(MENU_FILE_REMOVE_LANGUAGE), true)
	_file_menu.get_popup().connect("id_pressed", self, "_on_FileMenu_id_pressed")
	
	_edit_menu.get_popup().connect("id_pressed", self, "_on_EditMenu_id_pressed")
	
	# In the editor the parent is still busy setting up children...
	call_deferred("_setup_dialogs")
	
	_update_status_label()


func _setup_dialogs():
	# If this fails, something wrong is happening with parenting of the main view
	assert(_open_dialog == null)
	
	_open_dialog = FileDialog.new()
	_open_dialog.window_title = "Open translations"
	_open_dialog.add_filter("*.csv ; CSV files")
	_open_dialog.add_filter("*.po ; Gettext files")
	_open_dialog.mode = FileDialog.MODE_OPEN_FILE
	_open_dialog.connect("file_selected", self, "_on_OpenDialog_file_selected")
	_add_dialog(_open_dialog)

	_save_file_dialog = FileDialog.new()
	_save_file_dialog.window_title = "Save translations as CSV"
	_save_file_dialog.add_filter("*.csv ; CSV files")
	_save_file_dialog.mode = FileDialog.MODE_SAVE_FILE
	_save_file_dialog.connect("file_selected", self, "_on_SaveFileDialog_file_selected")
	_add_dialog(_save_file_dialog)

	_save_folder_dialog = FileDialog.new()
	_save_folder_dialog.window_title = "Save translations as gettext .po files"
	_save_folder_dialog.mode = FileDialog.MODE_OPEN_DIR
	_save_folder_dialog.connect("dir_selected", self, "_on_SaveFolderDialog_dir_selected")
	_add_dialog(_save_folder_dialog)
	
	_string_edit_dialog = StringEditionDialog.instance()
	_string_edit_dialog.set_validator(funcref(self, "_validate_new_string_id"))
	_string_edit_dialog.connect("submitted", self, "_on_StringEditionDialog_submitted")
	_add_dialog(_string_edit_dialog)
	
	_language_selection_dialog = LanguageSelectionDialog.instance()
	_language_selection_dialog.connect("language_selected", self, "_on_LanguageSelectionDialog_language_selected")
	_add_dialog(_language_selection_dialog)
	
	_remove_language_confirmation_dialog = ConfirmationDialog.new()
	_remove_language_confirmation_dialog.dialog_text = "Do you really want to remove this language? (There is no undo!)"
	_remove_language_confirmation_dialog.connect("confirmed", self, "_on_RemoveLanguageConfirmationDialog_confirmed")
	_add_dialog(_remove_language_confirmation_dialog)
	
	_extractor_dialog = ExtractorDialog.instance()
	_extractor_dialog.set_registered_string_filter(funcref(self, "_is_string_registered"))
	_extractor_dialog.connect("import_selected", self, "_on_ExtractorDialog_import_selected")
	_add_dialog(_extractor_dialog)
	
	_remove_string_confirmation_dialog = ConfirmationDialog.new()
	_remove_string_confirmation_dialog.dialog_text = \
		"Do you really want to remove this string and all its translations? (There is no undo)"
	_remove_string_confirmation_dialog.connect("confirmed", self, "_on_RemoveStringConfirmationDialog_confirmed")
	_add_dialog(_remove_string_confirmation_dialog)


func _add_dialog(dialog):
	if _base_control != null:
		_base_control.add_child(dialog)
		_dialogs_to_free_on_exit.append(dialog)
	else:
		add_child(dialog)


func _exit_tree():
	# Free dialogs because in the editor they might not be child of the main view...
	# Also this code runs in the edited scene view as a `tool` side-effect.
	for dialog in _dialogs_to_free_on_exit:
		dialog.queue_free()
	_dialogs_to_free_on_exit.clear()


func configure_for_godot_integration(base_control):
	# You have to call this before adding to the tree
	assert(not is_inside_tree())
	_base_control = base_control
	# Make underlying panel transparent because otherwise it looks bad in the editor
	# TODO Would be better to not draw the panel background conditionally
	self_modulate = Color(0, 0, 0, 0)


func _on_FileMenu_id_pressed(id):
	match id:
		MENU_FILE_OPEN:
			_open()
		
		MENU_FILE_SAVE:
			_save()
		
		MENU_FILE_SAVE_AS_CSV:
			_save_file_dialog.popup_centered_ratio()

		MENU_FILE_SAVE_AS_PO:
			_save_folder_dialog.popup_centered_ratio()
		
		MENU_FILE_ADD_LANGUAGE:
			_language_selection_dialog.configure(_languages)
			_language_selection_dialog.popup_centered_ratio()
			
		MENU_FILE_REMOVE_LANGUAGE:
			var language = get_current_language()
			_remove_language_confirmation_dialog.window_title = str("Remove language `", language, "`")
			_remove_language_confirmation_dialog.popup_centered_minsize()
		
		MENU_FILE_EXTRACT:
			_extractor_dialog.popup_centered_minsize()


func _on_EditMenu_id_pressed(id):
	pass


func _on_OpenDialog_file_selected(filepath):
	load_file(filepath)


func _on_SaveFileDialog_file_selected(filepath):
	save_file(filepath, FORMAT_CSV)


func _on_SaveFolderDialog_dir_selected(filepath):
	save_file(filepath, FORMAT_GETTEXT)


func _on_OpenButton_pressed():
	_open()


func _on_SaveButton_pressed():
	_save()


func _on_LanguageSelectionDialog_language_selected(language):
	_add_language(language)


func _open():
	_open_dialog.popup_centered_ratio()


func _save():
	if _current_path == null:
		# Have to default to CSV for now...
		_save_file_dialog.popup_centered_ratio()
	else:
		save_file(_current_path, _current_format)


func load_file(filepath):
	var ext = filepath.get_extension()
	
	if ext == "po":
		var valid_locales = Locales.get_all_locale_ids()
		_current_path = filepath.get_base_dir()
		_data = PoLoader.load_po_translation(_current_path, valid_locales)
		_current_format = FORMAT_GETTEXT
		
	elif ext == "csv":
		_data = CsvLoader.load_csv_translation(filepath)
		_current_path = filepath
		_current_format = FORMAT_CSV
		
	else:
		printerr("Unknown file format, cannot load ", filepath)
		return
	
	_languages.clear()
	for strid in _data:
		var s = _data[strid]
		for language in s.translations:
			if _languages.find(language) == -1:
				_languages.append(language)
	
	_translation_edits.clear()
	
	for i in _translation_tab_container.get_child_count():
		var child = _translation_tab_container.get_child(i)
		if child is TextEdit:
			child.queue_free()
	
	for language in _languages:
		_create_translation_edit(language)
	
	refresh_list()
	_modified_languages.clear()
	_update_status_label()


func _update_status_label():
	if _current_path == null:
		_status_label.text = "No file loaded"
	elif _current_format == FORMAT_CSV:
		_status_label.text = _current_path
	elif _current_format == FORMAT_GETTEXT:
		_status_label.text = str(_current_path, " (Gettext translations folder)")


func _create_translation_edit(language):
	assert(not _translation_edits.has(language)) # boom
	var edit = TextEdit.new()
	edit.hide()
	var tab_index = _translation_tab_container.get_tab_count()
	_translation_tab_container.add_child(edit)
	_translation_tab_container.set_tab_title(tab_index, language)
	_translation_edits[language] = edit
	edit.connect("text_changed", self, "_on_TranslationEdit_text_changed", [language])


func _on_TranslationEdit_text_changed(language):
	var edit = _translation_edits[language]
	var selected_strids = _string_list.get_selected_items()
	# TODO Don't show the editor if no strings are selected
	if len(selected_strids) != 1:
		return
	#assert(len(selected_strids) == 1)
	var strid = _string_list.get_item_text(selected_strids[0])
	var prev_text = null
	var s = _data[strid]
	if s.translations.has(language):
		prev_text = s.translations[language]
	if prev_text != edit.text:
		s.translations[language] = edit.text
		_set_language_modified(language)


func _on_NotesEdit_text_changed():
	var selected_strids = _string_list.get_selected_items()
	# TODO Don't show the editor if no strings are selected
	if len(selected_strids) != 1:
		return
	#assert(len(selected_strids) == 1)
	var strid = _string_list.get_item_text(selected_strids[0])
	var s = _data[strid]
	if s.comments != _notes_edit.text:
		s.comments = _notes_edit.text
		for language in _languages:
			_set_language_modified(language)


func _set_language_modified(language):
	if _modified_languages.has(language):
		return
	_modified_languages[language] = true
	_set_language_tab_title(language, str(language, "*"))


func _set_language_unmodified(language):
	if not _modified_languages.has(language):
		return
	_modified_languages.erase(language)
	_set_language_tab_title(language, language)


func _set_language_tab_title(language, title):
	var page = _translation_edits[language]
	for i in _translation_tab_container.get_child_count():
		if _translation_tab_container.get_child(i) == page:
			_translation_tab_container.set_tab_title(i, title)
			# TODO There seem to be a Godot bug, tab titles don't update unless you click on them Oo
			# See https://github.com/godotengine/godot/issues/23696
			_translation_tab_container.update()
			return
	# Something bad happened
	assert(false)


func get_current_language():
	var page = _translation_tab_container.get_current_tab_control()
	for language in _translation_edits:
		if _translation_edits[language] == page:
			return language
	# Something bad happened
	assert(false)
	return null


func save_file(path, format):
	var saved_languages = []
	
	if format == FORMAT_GETTEXT:
		var languages_to_save
		if _current_format != FORMAT_GETTEXT:
			languages_to_save = _languages
		else:
			languages_to_save = _modified_languages.keys()
		saved_languages = PoLoader.save_po_translations(path, _data, languages_to_save)
		
	elif format == FORMAT_CSV:
		saved_languages = CsvLoader.save_csv_translation(path, _data)
		
	else:
		printerr("Unknown file format, cannot save ", path)

	for language in saved_languages:
		_set_language_unmodified(language)
	
	_current_format = format
	_current_path = path
	_update_status_label()


func refresh_list():
	var search_text = _search_edit.text.strip_edges()
	
	var sorted_strids = []
	if search_text == "":
		sorted_strids = _data.keys()
	else:
		for strid in _data.keys():
			if strid.find(search_text) != -1:
				sorted_strids.append(strid)
	
	sorted_strids.sort()
	
	_string_list.clear()
	for strid in sorted_strids:
		_string_list.add_item(strid)


func _on_StringList_item_selected(index):
	var str_id = _string_list.get_item_text(index)
	var s = _data[str_id]
	for language in _languages:
		var e = _translation_edits[language]
		#e.show()
		if s.translations.has(language):
			e.text = s.translations[language]
		else:
			e.text = ""
	_notes_edit.text = s.comments


func _on_AddButton_pressed():
	_string_edit_dialog.set_replaced_str_id(null)
	_string_edit_dialog.popup_centered()


func _on_RemoveButton_pressed():
	var selected_items = _string_list.get_selected_items()
	if len(selected_items) == 0:
		return
	var str_id = _string_list.get_item_text(selected_items[0])
	_remove_string_confirmation_dialog.window_title = str("Remove `", str_id, "`")
	_remove_string_confirmation_dialog.popup_centered_minsize()


func _on_RemoveStringConfirmationDialog_confirmed():
	var selected_items = _string_list.get_selected_items()
	if len(selected_items) == 0:
		printerr("No selected string??")
		return
	var strid = _string_list.get_item_text(selected_items[0])
	_string_list.remove_item(selected_items[0])
	_data.erase(strid)
	for language in _languages:
		_set_language_modified(language)


func _on_RenameButton_pressed():
	var selected_items = _string_list.get_selected_items()
	if len(selected_items) == 0:
		return
	var str_id = _string_list.get_item_text(selected_items[0])
	_string_edit_dialog.set_replaced_str_id(str_id)
	_string_edit_dialog.popup_centered()


func _on_StringEditionDialog_submitted(str_id, prev_str_id):
	if prev_str_id == null:
		add_new_string(str_id)
	else:
		rename_string(prev_str_id, str_id)


func _validate_new_string_id(str_id):
	if _data.has(str_id):
		return "Already existing"
	if str_id.strip_edges() != str_id:
		return "Must not start or end with spaces"
	for k in _data:
		if k.nocasecmp_to(str_id) == 0:
			return "Already existing with different case"
	return true


func add_new_string(strid):
	print("Adding new string ", strid)
	assert(not _data.has(strid))
	var s = {
		"translations": {},
		"comments": ""
	}
	_data[strid] = s
	_string_list.add_item(strid)
	for language in _languages:
		_set_language_modified(language)


func rename_string(old_strid, new_strid):
	assert(_data.has(old_strid))
	var s = _data[old_strid]
	_data.erase(old_strid)
	_data[new_strid] = s
	for i in _string_list.get_item_count():
		if _string_list.get_item_text(i) == old_strid:
			_string_list.set_item_text(i, new_strid)
			break


func _add_language(language):
	assert(_languages.find(language) == -1)
	
	_create_translation_edit(language)
	_languages.append(language)
	_set_language_modified(language)
	
	var menu_index = _file_menu.get_popup().get_item_index(MENU_FILE_REMOVE_LANGUAGE)
	_file_menu.get_popup().set_item_disabled(menu_index, false)
	
	print("Added language ", language)


func _remove_language(language):
	assert(_languages.find(language) != -1)
	
	_set_language_unmodified(language)
	var edit = _translation_edits[language]
	edit.queue_free()
	_translation_edits.erase(language)
	_languages.erase(language)

	if len(_languages) == 0:
		var menu_index = _file_menu.get_popup().get_item_index(MENU_FILE_REMOVE_LANGUAGE)
		_file_menu.get_popup().set_item_disabled(menu_index, true)

	print("Removed language ", language)


func _on_RemoveLanguageConfirmationDialog_confirmed():
	var language = get_current_language()
	_remove_language(language)


# Used as callback for filtering
func _is_string_registered(text):
	if _data == null:
		print("No data")
		return false
	return _data.has(text)


func _on_ExtractorDialog_import_selected(results):
	for text in results:
		if not _is_string_registered(text):
			add_new_string(text)


func _on_Search_text_changed(search_text):
	_clear_search_button.visible = (search_text != "")
	refresh_list()


func _on_ClearSearch_pressed():
	_search_edit.text = ""
