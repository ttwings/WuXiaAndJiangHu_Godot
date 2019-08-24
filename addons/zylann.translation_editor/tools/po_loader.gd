tool

const STATE_NONE = 0
const STATE_MSGID = 1
const STATE_MSGSTR = 2

static func load_po_translation(folder_path, valid_locales):
	var all_strings = {}
	var config = {}
	
	# TODO Get languages from configs, not from filenames
	var languages = get_languages_in_folder(folder_path, valid_locales)
	
	if len(languages) == 0:
		printerr("No .po languages were found in ", folder_path)
		return all_strings
	
	for language in languages:
		var filepath = folder_path.plus_file(str(language, ".po"))
		
		var f = File.new()
		var err = f.open(filepath, File.READ)
		if err != OK:
			printerr("Could not open file ", filepath, " for read, error ", err)
			return null
		
		f.store_line("")
		
		var state = STATE_NONE
		var comment = ""
		var msgid = ""
		var msgstr = ""
		var ids = []
		var translations = []
		var comments = []
		# For debugging
		var line_number = -1
		
		while not f.eof_reached():
			var line = f.get_line().strip_edges()
			line_number += 1
			
			if line != "" and line[0] == "#":
				var comment_line = line.right(1).strip_edges()
				if comment == "":
					comment = str(comment, comment_line)
				else:
					comment = str(comment, "\n", comment_line)
				continue
			
			var space_index = line.find(" ")
			
			if line.begins_with("msgid"):
				msgid = _parse_msg(line.right(space_index))
				state = STATE_MSGID
				
			elif line.begins_with("msgstr"):
				msgstr = _parse_msg(line.right(space_index))
				state = STATE_MSGSTR
				
			elif line.begins_with('"'):
				match state:
					STATE_MSGID:
						msgid = str(msgid, _parse_msg(line))
					STATE_MSGSTR:
						msgstr = str(msgstr, _parse_msg(line))
				
			elif line == "" and state == STATE_MSGSTR:
				var s = null
				if msgid == "":
					assert(len(msgstr) != 0)
					config = _parse_config(msgstr)
				else:
					if not all_strings.has(msgid):
						s = {
							"translations": {},
							"comments": ""
						}
						all_strings[msgid] = s
					else:
						s = all_strings[msgid]
					s.translations[language] = msgstr
					if s.comments == "":
						s.comments = comment
				
				comment = ""
				msgid = ""
				msgstr = ""
				state = STATE_NONE
				
			else:
				print("Unhandled .po line: ", line)
				continue
	
	# TODO Return configs?
	return all_strings


static func _parse_msg(s):
	s = s.strip_edges()
	assert(s[0] == '"')
	var end = s.rfind('"')
	var msg = s.substr(1, end - 1)
	return msg.c_unescape().replace('\\"', '"')


static func _parse_config(text):
	var config = {}
	var lines = text.split("\n", false)
	print("Config lines: ", lines)
	for line in lines:
		var splits = line.split(":")
		print("Splits: ", splits)
		config[splits[0]] = splits[1].strip_edges()
	return config


class _Sorter:
	func sort(a, b):
		return a[0] < b[0]


static func save_po_translations(folder_path, translations, languages_to_save):
	var sorter = _Sorter.new()
	var saved_languages = []
	
	for language in languages_to_save:
		
		var f = File.new()
		var filepath = folder_path.plus_file(str(language, ".po"))
		var err = f.open(filepath, File.WRITE)
		if err != OK:
			printerr("Could not open file ", filepath, " for write, error ", err)
			continue
		
		# TODO Take as argument
		var config = {
			"Project-Id-Version": ProjectSettings.get_setting("application/config/name"),
			"MIME-Version": "1.0",
			"Content-Type": "text/plain; charset=UTF-8",
			"Content-Transfer-Encoding": "8bit",
			"Language": language
		}
		
		# Write config
		var config_msg = ""
		for k in config:
			config_msg = str(config_msg, k, ": ", config[k], "\n")
		_write_msg(f, "msgid", "")
		_write_msg(f, "msgstr", config_msg)
		f.store_line("")
		
		var items = []
		
		for id in translations:
			var s = translations[id]
			if not s.translations.has(language):
				continue
			items.append([id, s.translations[language], s.comments])
		
		items.sort_custom(sorter, "sort")
				
		for item in items:
			
			var comment = item[2]
			if comment != "":
				var comment_lines = comment.split("\n")
				for line in comment_lines:
					f.store_line(str("# ", line))
			
			_write_msg(f, "msgid", item[0])
			_write_msg(f, "msgstr", item[1])
			
			f.store_line("")
		
		f.close()
		saved_languages.append(language)
	
	return saved_languages


static func _write_msg(f, msgtype, msg):
	var lines = msg.split("\n")
	# `split` removes the newlines, so we'll add them back.
	# Empty lines may happen if the original text has multiple successsive line breaks.
	# However, if the text ends with a newline, it will produce an empty string at the end,
	# which we don't want. Repro: "\n".split("\n") produces ["", ""].
	if len(lines) > 0 and lines[-1] == "":
		lines.remove(len(lines) - 1)
	
	if len(lines) > 1:
		for i in range(0, len(lines) - 1):
			lines[i] = str(lines[i], "\n")
	else:
		lines = [msg]
	
	# This is just to avoid too long lines
#	if len(lines) > 1:
#		var rlines = []
#		for i in len(rlines):
#			var line = rlines[i]
#			var maxlen = 78
#			if i == 0:
#				maxlen -= len(msgtype) + 1
#			while len(line) > maxlen:
#				line = line.substr(0, maxlen)
#				rlines.append(line)
#			rlines.append(line)
#		lines = rlines

	for i in len(lines):
		lines[i] = lines[i].c_escape().replace('"', '\\"')
	
	f.store_line(str(msgtype, " \"", lines[0], "\""))
	for i in range(1, len(lines)):
		f.store_line(str(" \"", lines[i], "\""))


static func get_languages_in_folder(folder_path, valid_locales):
	var result = []
	var d = Directory.new()
	var err = d.open(folder_path)
	if err != OK:
		printerr("Could not open directory ", folder_path, ", error ", err)
		return result
	d.list_dir_begin()
	var fname = d.get_next()
	while fname != "":
		if not d.current_is_dir():
			var ext = fname.get_extension()
			if ext == "po":
				var language = fname.get_basename().get_file()
				if valid_locales.find(language) != -1:
					result.append(language)
		fname = d.get_next()
	return result
