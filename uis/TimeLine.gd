extends Node2D

var Date = {year=0,month=0,week=0,day=0,hour=0,minute=0,second=0,turn=0}
var animals = ["鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"]
var weeks 	= ["上旬","中旬","下旬"]
var days 	= ["月曜日","火曜日","水曜日","木曜日","金曜日","土曜日","日曜日"]
var hours 	= ["子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"]
var minutes = ["一刻","二刻","三刻","四刻","五刻","六刻","七刻","八刻","九刻"]
var months  = ["正","二","三","四","五","六","七","八","九","十","冬","腊"]
var numbers = ["〇","一","二","三","四","五","六","七","八","九"]
var season	= ["春","夏","秋","冬"]
var monthMsgOut = [	"春天悄悄地走来了，","春风轻轻地拂过你的脸庞，","天气逐渐变暖了，",
				"已经是初夏时节了，","知了的叫声让你感觉到了盛夏的气息，","天气变得非常闷热，",
				"虽然是秋天了，天气还是有些热，","中秋佳节快到了，","一阵秋风吹来，卷起了地上的落叶，",
				"秋去冬来，","寒风凛冽，","快到年关了，"]
func _ready():
#	$Label.text = "戊戌年九月二十三日 子时一刻"
	$Label.text = print_date()
	
func date_change():
	Date.second	= Date.second + 6
	Date.minute = Date.second/60
	Date.hour 	= Date.minute/120
	Date.day 	= Date.hour/12
	Date.week 	= Date.day/7
	Date.month 	= Date.week/3
	Date.year 	= Date.month/12

	Date.minute = Date.minute%120
	Date.hour 	= Date.hour%12
	Date.day 	= Date.day%7
	Date.week 	= Date.week%3
	Date.month 	= Date.month%12
	Date.year 	= Date.year%12
	return Date

func _process(delta):
	# -- 1年 = 12 月 * 3 旬 * 7 天 * 12 时辰 * 120 分 * 60 秒 * 60 帧 = 15552000
	# -- 计算年月日
	# -- 6 秒一回合
	date_change()
	$Label.text = print_date()
	pass
	
func print_date():
	var yearStr = hours[Date.year] + animals[Date.year]
	var monthStr = months[Date.month]
	var weekStr = weeks[Date.week]
	var dayStr = days[Date.day]
	var hourStr = hours[Date.hour]
	var minuteStr = minutes[Date.minute/15%8]
	var dateStr = ""
	var dateStr1 = ""
	dateStr = "{0}年{1}月{2}{3}{4}时{5}".format([yearStr,monthStr,weekStr,dayStr,hourStr,minuteStr])
	dateStr1 = "{0}年{1}月{2}日 {3}：{4}".format([str(Date.year),str(Date.month),str(Date.day),str(Date.hour),str(Date.minute)])
	return dateStr