extends Node

func createHeal(from,to,heal):
	var healObj = HealObj.new({
		"from":from,
		"to":to,
		"heal":heal
	})
	return healObj