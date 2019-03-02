extends Node

class_name Char

var temps = {}
var skills = {}

	


func query_skill(skill:String):
	if skills[skill] :
		return skills[skill]
	else:
		return false
		
func query_temp(temp:String):
	if temps[temp] :
		return temps[temp]
	else:
		return false		
		
func query(p:String):
	if self.p :
		return self.p
	else:
		return false		