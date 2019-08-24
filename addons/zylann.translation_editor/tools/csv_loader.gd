tool

static func load_csv_translation(filepath):
	var f = File.new()
	var err = f.open(filepath, File.READ)
	if err != OK:
		printerr("Could not open ", filepath, " for read, code ", err)
		return null
	
	var first_row = f.get_csv_line()
	if first_row[0] != "id":
		printerr("Translation file is missing the `id` column")
		return null
	
	var languages = PoolStringArray()
	for i in range(1, len(first_row)):
		languages.append(first_row[i])
	
	var ids = []
	var rows = []
	while not f.eof_reached():
		var row = f.get_csv_line()
		if len(row) < 1 or row[0].strip_edges() == "":
			printerr("Found an empty row")
			continue
		if len(row) < len(first_row):
			print("Found row smaller than header, resizing")
			row.resize(len(first_row))
		ids.append(row[0])
		var trans = PoolStringArray()
		for i in range(1, len(row)):
			trans.append(row[i])
		rows.append(trans)
	f.close()
	
	var translations = {}
	for i in len(ids):
		var t = {}
		for language_index in len(rows[i]):
			t[languages[language_index]] = rows[i][language_index]
		translations[ids[i]] = { "translations": t, "comments": "" }
	
	return translations


class _Sorter:
	func sort(a, b):
		return a[0] < b[0]


static func save_csv_translation(filepath, data):
	print("Saving: ", data)
	var languages = {}
	for id in data:
		var s = data[id]
		for language in s.translations:
			languages[language] = true
	
	if len(languages) == 0:
		printerr("No language found, nothing to save")
		return []
	
	languages = languages.keys()
	languages.sort()
	
	var first_row = ["id"]
	first_row.resize(len(languages) + 1)
	for i in len(languages):
		first_row[i + 1] = languages[i]
	
	var rows = []
	rows.resize(len(data))
	
	var row_index = 0
	for id in data:
		var s = data[id]
		var row = []
		row.resize(len(languages) + 1)
		row[0] = id
		for i in len(languages):
			var text = ""
			if s.translations.has(languages[i]):
				text = s.translations[languages[i]]
			row[i + 1] = text
		rows[row_index] = row
		row_index += 1
	print(rows)
	var sorter = _Sorter.new()
	rows.sort_custom(sorter, "sort")

	var delim = ","

	var f = File.new()
	var err = f.open(filepath, File.WRITE)
	if err != OK:
		printerr("Could not open ", filepath, " for write, code ", err)
		return []

	store_csv_line(f, first_row)
	for row in rows:
		store_csv_line(f, row)
	
	f.close()
	print("Saved ", filepath)
	var saved_languages = languages
	return saved_languages


static func store_csv_line(f, a, delim = ","):
	for i in len(a):
		if i > 0:
			f.store_string(",")
		var text = str(a[i])
		# Behavior taken from LibreOffice
		if text.find(delim) != -1 or text.find('"') != -1 or text.find("\n") != -1:
			text = str('"', text.replace('"', '""'), '"')
		f.store_string(text)
	f.store_string("\n")

