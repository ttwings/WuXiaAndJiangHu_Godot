# WuXiaAndJiangHu_Godot 武侠和江湖  godot开发笔记

## 抱歉，天天换开发工具。
*  在用love2d框架开发中，发现点问题。如发布和添加广告，第三方SDK支持等。
* 而且因为love2d的用户群体过少，自己编程水平很一般，遇到的问题难以解决，比如想加个广告。。
* 考虑到游戏最终发布，忍痛换工具，近期在学习godot游戏引擎。
* love2d还是很好用的，很适合学习，做工具，还会继续密切关注。


## 已经基本掌握godot引擎
* 通过学习官网教程，和网上一些教程。目前已经基本掌握godot。
* 游戏的整体框架思路，已经逐渐定型，素材收集也差不多。换引擎不会影响太多。
* godot引擎，目前用起来，感觉不错。很顺手。

## 开发随笔
1. 基本保存
```JavaScript
func save(content):
    var file = File.new()
    file.open("user://save_game.dat", file.WRITE)
    file.store_string(content)
    file.close()

func load():
    var file = File.new()
    file.open("user://save_game.dat", file.READ)
    var content = file.get_as_text()
    file.close()
    return content
```
2. json的基本使用
```JavaScript
var p = JSON.parse('["hello", "world", "!"]')
if typeof(p.result) == TYPE_ARRAY:
    print(p.result[0]) # prints 'hello'
else:
    print("unexpected results")
```
3. 读取json数据
```JavaScript
func load_data(path:String):
	var load_data = File.new()
	if not load_data.file_exists(path):
		print_debug("not exists file")
		return
	
	load_data.open(path,File.READ)

	var data_str = load_data.get_as_text()
	var p = JSON.parse(data_str)
	return p.result
```
4. 获取目录下特定后缀文件
```JavaScript
func dir_files(path,suffix):
	var dir = Directory.new()
	var files = []
	if dir.open(path) == OK:
		dir.list_dir_begin()
		var file_name = dir.get_next()
		while (file_name!= ""):
			if dir.current_is_dir():
				print("Found directory" + file_name)
			elif file_name.split(".")[-1] == suffix:
				files.append(file_name)
				print("Found file: " + file_name)
			else:
				pass
				#print("Found file: " + file_name)
			file_name = dir.get_next()
	else:
		print("An error ccurred when trying to access the path.")
	return files	
```

5. 读取文件夹下图片素材生成动画

```JavaScript
extends Node2D
# 选择目录下的png
export(String,DIR) var path
export(String) var anim

func _ready():
    $AnimatedSprite.frames = creatAnimation(path)
    $AnimatedSprite.speed_scale = 4
    $AnimatedSprite.play("default")
    pass # Replace with function body.

func dir_contents(path):
    var dir = Directory.new()
    var file_list = []
    if dir.open(path) == OK:
        dir.list_dir_begin()
        var file_name = dir.get_next()
        while(file_name != ""):
            if dir.current_is_dir():
                print("Found directory: " + file_name)
            else:
                if file_name.split(".")[-1] == "png":
                    file_list.append(file_name)
#                    print("Found file: " + file_name)
            file_name = dir.get_next()
    else:
        print("An Error occurred when trying to access the path.")
    return file_list

func creatAnimation(path:String):
    var sprite_sheet = dir_contents(path)
    var sprite_frames = SpriteFrames.new()
    for i in sprite_sheet.size() :
        var frame = load(path + "/" + sprite_sheet[i])
        sprite_frames.add_frame("default",frame)
    return sprite_frames
```