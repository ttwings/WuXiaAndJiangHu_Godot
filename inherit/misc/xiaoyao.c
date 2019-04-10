// xiaoyao.c

int lingjiu_master(object ob);
int xiaoyao_master(object ob);
string fam_type(object ob)
{
	object weapon;
	if (!userp(ob))
	{
		if (ob->query_skill_mapped("force")=="beiming-shengong")
		return "xiaoyao";
		if (ob->query_skill_mapped("force")=="bahuang-gong")
		return "lingjiu";
	}
	if (!ob->query("family") || 
	ob->query("family/family_name")!="åÐÒ£ÅÉ")	return 0;
	if (!objectp(weapon= ob->query_temp("weapon")))
	{
		if (ob->query_skill_mapped("hand")=="zhemei-shou"
		&&  ob->query_skill_mapped("force")=="beiming-shengong"
		&&  ob->query_skill_mapped("dodge")=="lingboweibu"
		&&  ob->query_skill_prepared("hand")=="zhemei-shou"
		&& xiaoyao_master(ob) )
		return "xiaoyao";
		if (ob->query_skill_mapped("hand")=="liuyang-zhang"
		&&  ob->query_skill_mapped("force")=="bahuang-gong"
		&&  ob->query_skill_mapped("dodge")=="yueying-wubu"
		&&  ob->query_skill_prepared("hand")=="liuyang-zhang"
		&& lingjiu_master(ob) )
		return "lingjiu";
		return 0;
	}
	if (weapon->query("skill_type")=="blade" 
	&&  ob->query_skill_mapped("blade")=="ruyi-dao"
	&&  ob->query_skill_mapped("hand")=="zhemei-shou"
	&&  ob->query_skill_mapped("force")=="beiming-shengong"
	&&  ob->query_skill_mapped("dodge")=="lingboweibu"
	&&  ob->query_skill_prepared("hand")=="zhemei-shou"
	&& xiaoyao_master(ob) )
		return "xiaoyao";
	if (weapon->query("skill_type")=="sword" 
	&& ob->query_skill_mapped("sword")=="tianyu-qijian"
	&& ob->query_skill_mapped("hand")=="liuyang-zhang"
	&&  ob->query_skill_mapped("force")=="bahuang-gong"
	&&  ob->query_skill_mapped("dodge")=="yueying-wubu"
	&&  ob->query_skill_prepared("hand")=="liuyang-zhang"
	&& xiaoyao_master(ob) )
		return "lingjiu";
	return 0;	
}
int xiaoyao_master(object ob)
{
	string fid;
	
	fid = ob->query("family/master_id");
	if (!stringp(fid)) return 0;
	if (fid == "fan bailing" ||
	    fid == "feng asan" ||
	    fid == "gou du" ||
	    fid == "kang guangling" ||
	    fid == "li kuilei" ||
	    fid == "shi qinglu" ||
	    fid == "su xinghe" ||
	    fid == "wu lingjun" ||
	    fid == "xiaoyao zi" ||
	    fid == "xue muhua")
    	    return 1;
         return 0;
}
int lingjiu_master(object ob)
{
	string fid;
	
	fid = ob->query("family/master_id");
	if (!stringp(fid)) return 0;
	if (fid == "ju jian" ||
	fid == "mei jian" ||
	fid == "tong lao" ||
	fid == "xu zhu" )
	return 1;
	return 0;
}