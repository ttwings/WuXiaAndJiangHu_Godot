
const STATE_SEARCHING = 0
const STATE_READING_TEXT = 1

# results: { string => { fpath => line number } }
signal finished(results)
signal progress_reported(ratio)

var _strings = {}
var _thread = null
var _time_before = 0.0
var _ignored_paths = {}
var _paths = []


func extract(root, ignored_paths=[]):
	_time_before = OS.get_ticks_msec()
	assert(_thread == null)
	
	_ignored_paths.clear()
	for p in ignored_paths:
		_ignored_paths[root.plus_file(p)] = true
	
	_thread = Thread.new()
	_thread.start(self, "_extract", root)


func _extract(root):
	_walk(root, funcref(self, "_index_file"), funcref(self, "_filter"))
	
	for i in len(_paths):
		var fpath = _paths[i]
		var f = File.new()
		var err = f.open(fpath, File.READ)
		if err != OK:
			printerr("Could not open '", fpath, "', for read, error ", err)
			continue
		var ext = fpath.get_extension()
		match ext:
			"tscn":
				_process_tscn(f, fpath)
			"gd":
				_process_gd(f, fpath)
		f.close()
		call_deferred("_report_progress", float(i) / float(len(_paths)))
	
	call_deferred("_finished")


func _report_progress(ratio):
	emit_signal("progress_reported", ratio)


func _finished():
	_thread.wait_to_finish()
	_thread = null
	var elapsed = float(OS.get_ticks_msec() - _time_before) / 1000.0
	print("Extraction took ", elapsed, " seconds")
	emit_signal("finished", _strings)


func _filter(path):
	if path in _ignored_paths:
		return false
	if path[0] == ".":
		return false
	return true


func _index_file(fpath):
	var ext = fpath.get_extension()
	#print("File ", fpath)
	if ext != "tscn" and ext != "gd":
		return
	_paths.append(fpath)


func _process_tscn(f, fpath):
	# TOOD Also search for "window_title" and "dialog_text"
	var pattern = "text ="
	var text = ""
	var state = STATE_SEARCHING
	var line_number = 0
	
	while not f.eof_reached():
		var line = f.get_line()
		line_number += 1
		
		if line == "":
			continue
		
		match state:
			
			STATE_SEARCHING:
				var i = line.find(pattern)
				if i != -1:
					var begin_quote_index = line.find('"', i + len(pattern))
					if begin_quote_index == -1:
						printerr("Could not find begin quote after text property, in ", fpath, " line ", line_number)
						continue
					var end_quote_index = line.rfind('"')
					if end_quote_index != -1 and end_quote_index > begin_quote_index and line[end_quote_index - 1] != '\\':
						text = line.substr(begin_quote_index + 1, end_quote_index - begin_quote_index - 1)
						if text != "":
							_add_string(fpath, line_number, text)
						text = ""
					else:
						# The text may be multiline
						text = str(line.right(begin_quote_index + 1), "\n")
						state = STATE_READING_TEXT
			
			STATE_READING_TEXT:
				var end_quote_index = line.rfind('"')
				if end_quote_index != -1 and line[end_quote_index - 1] != '\\':
					text = str(text, line.left(end_quote_index))
					_add_string(fpath, line_number, text)
					text = ""
					state = STATE_SEARCHING
				else:
					text = str(text, line, "\n")


func _process_gd(f, fpath):
	var pattern = "tr("
	var text = ""
	var line_number = 0
	
	while not f.eof_reached():
		var line = f.get_line().strip_edges()
		line_number += 1

		if line == "" or line[0] == "#":
			continue
		
		# Search for one or multiple tr("...") in the same line
		var search_index = 0
		var counter = 0
		while true:
			var call_index = line.find(pattern, search_index)
			if call_index == -1:
				break
			if call_index != 0:
				if line.substr(call_index - 1, 3).is_valid_identifier():
					# not a tr( call
					break
				if line[call_index - 1] == '"':
					break
				# TODO There may be more cases to handle
				# They may need regexes or a simplified GDScript parser to extract properly
			
			var begin_quote_index = line.find('"', call_index)
			if begin_quote_index == -1:
				# Multiline or procedural strings not supported
				printerr("Begin quote not found in ", fpath, " line ", line_number)
				break
			var end_quote_index = find_unescaped_quote(line, begin_quote_index + 1)
			if end_quote_index == -1:
				# Multiline or procedural strings not supported
				printerr("End quote not found in ", fpath, " line ", line_number)
				break
			text = line.substr(begin_quote_index + 1, end_quote_index - begin_quote_index - 1)
			var end_bracket_index = line.find(')', end_quote_index)
			if end_bracket_index == -1:
				# Multiline or procedural strings not supported
				printerr("End bracket not found in ", fpath, " line ", line_number)
				break
			_add_string(fpath, line_number, text)
			search_index = end_bracket_index
			
			counter += 1
			assert(counter < 100)


static func find_unescaped_quote(s, from):
	while true:
		var i = s.find('"', from)
		if i <= 0:
			return i
		if s[i - 1] != '\\':
			return i
		from = i + 1


func _add_string(file, line_number, text):
	if not _strings.has(text):
		_strings[text] = {}
	_strings[text][file] = line_number


static func _walk(folder_path, file_action, filter):
	#print("Walking dir ", folder_path)
	var d = Directory.new()
	var err = d.open(folder_path)
	if err != OK:
		printerr("Could not open directory '", folder_path, "', error ", err)
		return
	d.list_dir_begin(true, true)
	var fname = d.get_next()
	while fname != "":
		var fullpath = folder_path.plus_file(fname)
		if filter == null or filter.call_func(fullpath) == true:
			if d.current_is_dir():
				_walk(fullpath, file_action, filter)
			else:
				file_action.call_func(fullpath)
		fname = d.get_next()
	return

