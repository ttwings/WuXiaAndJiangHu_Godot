tool
extends WindowDialog

const Extractor = preload("extractor.gd")

signal import_selected(strings)

onready var _root_path_edit = get_node("VBoxContainer/HBoxContainer/RootPathEdit")
onready var _excluded_dirs_edit = get_node("VBoxContainer/Options/ExcludedDirsEdit")
onready var _summary_label = get_node("VBoxContainer/StatusBar/SummaryLabel")
onready var _results_list = get_node("VBoxContainer/Results")
onready var _progress_bar = get_node("VBoxContainer/StatusBar/ProgressBar")
onready var _extract_button = get_node("VBoxContainer/Buttons/ExtractButton")
onready var _import_button = get_node("VBoxContainer/Buttons/ImportButton")

var _extractor = null
# { string => { fpath => line number } }
var _results = {}
var _registered_string_filter = null


func _ready():
	_import_button.disabled = true


func set_registered_string_filter(registered_string_filter):
	assert(registered_string_filter is FuncRef)
	_registered_string_filter = registered_string_filter


func _notification(what):
	if what == NOTIFICATION_VISIBILITY_CHANGED:
		if visible:
			_summary_label.text = ""
			_results.clear()
			_update_import_button()


func _update_import_button():
	_import_button.disabled = (_results == null or len(_results) == 0)


func _on_ExtractButton_pressed():
	if _extractor != null:
		return
	
	var root = _root_path_edit.text.strip_edges()
	var d = Directory.new()
	if not d.dir_exists(root):
		printerr("Directory `", root, "` does not exist")
		return
	
	var excluded_dirs = _excluded_dirs_edit.text.split(";", false)
	for i in len(excluded_dirs):
		excluded_dirs[i] = excluded_dirs[i].strip_edges()
	
	_extractor = Extractor.new()
	_extractor.connect("progress_reported", self, "_on_Extractor_progress_reported")
	_extractor.connect("finished", self, "_on_Extractor_finished")
	_extractor.extract(root, excluded_dirs)
	
	_progress_bar.value = 0
	_progress_bar.show()
	_summary_label.text = ""
	
	_extract_button.disabled = true
	_import_button.disabled = true


func _on_ImportButton_pressed():
	emit_signal("import_selected", _results)
	_results.clear()
	hide()


func _on_CancelButton_pressed():
	# TODO Cancel extraction?
	hide()


func _on_Extractor_progress_reported(ratio):
	_progress_bar.value = 100.0 * ratio


func _on_Extractor_finished(results):
	print("Extractor finished")
	_progress_bar.value = 100
	_progress_bar.hide()
	
	_results_list.clear()
	
	var registered_set = {}
	var new_set = {}
	
	# TODO We might actually want to not filter, in order to update location comments
	# Filter results
	if _registered_string_filter != null:
		var texts = results.keys()
		for text in texts:
			if _registered_string_filter.call_func(text):
				results.erase(text)
				registered_set[text] = true
	
	# Root
	_results_list.create_item()
	
	for text in results:
		var item = _results_list.create_item()
		item.set_text(0, text)
		item.collapsed = true
		new_set[text] = true
		
		var files = results[text]
		for file in files:
			var line_number = files[file]
			
			var file_item = _results_list.create_item(item)
			file_item.set_text(0, str(file, ": ", line_number))
	
	_results = results
	_extractor = null

	_update_import_button()
	_extract_button.disabled = false
	
	_summary_label.text = "{0} new, {1} registered".format([len(new_set), len(registered_set)])
