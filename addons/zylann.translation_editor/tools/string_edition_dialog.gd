tool
extends WindowDialog

signal submitted(str_id, prev_str_id)

onready var _line_edit = get_node("VBoxContainer/LineEdit")
onready var _ok_button = get_node("VBoxContainer/Buttons/OkButton")
onready var _hint_label = get_node("VBoxContainer/HintLabel")

var _validator_func = null
var _prev_str_id = null


func set_replaced_str_id(str_id):
	assert(typeof(str_id) == TYPE_STRING or str_id == null)
	_prev_str_id = str_id
	if typeof(str_id) == TYPE_STRING:
		_line_edit.text = str_id


func set_validator(f):
	_validator_func = f


func _notification(what):
	if what == NOTIFICATION_VISIBILITY_CHANGED:
		if visible:
			if _prev_str_id == null:
				window_title = "New string ID"
			else:
				window_title = str("Replace `", _prev_str_id, "`")
			_line_edit.grab_focus()
			_validate()


func _on_LineEdit_text_changed(new_text):
	_validate()


func _validate():
	var new_text = _line_edit.text.strip_edges()
	var valid = not new_text.empty()
	var hint_message = ""

	if _validator_func != null:
		var res = _validator_func.call_func(new_text)
		assert(typeof(res) == TYPE_BOOL or typeof(res) == TYPE_STRING)
		if typeof(res) != TYPE_BOOL or res == false:
			hint_message = res
			valid = false

	_ok_button.disabled = not valid
	_hint_label.text = hint_message
	# Note: hiding the label would shift up other controls in the container


func _on_LineEdit_text_entered(new_text):
	submit()


func _on_OkButton_pressed():
	submit()


func _on_CancelButton_pressed():
	hide()


func submit():
	var s = _line_edit.text.strip_edges()
	emit_signal("submitted", s, _prev_str_id)
	hide()

