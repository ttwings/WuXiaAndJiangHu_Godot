
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
// ban.c
// Modified by Constant Apr.7.2000

#include <ansi.h>

#define BANNED_SITES "/adm/etc/banned_sites"
#define ALLOWED_SITES "/adm/etc/allowed_sites"
void load_sites();
int is_banned(string site);
int is_multi(string site, int num);
void print();
void add(string site, mixed num);
void delete(string site, mixed num);
int match_sites(mapping sites, string site);
void record_list(mapping sites, string file);

mapping Sites;
mapping OKSites;

void create()
{
	seteuid(getuid());
	load_sites();
}

void load_sites()
{
	string *tmp, *line, file;
	int loop;

	Sites = ([]);
	OKSites = ([]);	

	// reads in the list of the banned sites
	file = read_file(BANNED_SITES);
	if (!file) return;
	
	tmp = explode(file, "\n");
   	for(loop=0; loop<sizeof(tmp); loop++) {
		line = explode(tmp[loop], " ");
        	if(line[0][0] == '#' || line[0][0] == '\n' || line[0] == "")
           		continue;
        	else Sites += ([ line[0] : atoi(line[1]) ]);
	}
        // reads in the list of the allowed sites
        file = read_file(ALLOWED_SITES);
        if (!file) return;

        tmp = explode(file, "\n");
        for(loop=0; loop<sizeof(tmp); loop++) {
		line = explode(tmp[loop], " ");
                if(line[0][0] == '#' || line[0][0] == '\n' || line[0] == "")
                        continue;
                else OKSites += ([ line[0] : atoi(line[1]) ]);
	}
	return;
}

// 先匹配解禁列表，后匹配封禁列表，以允许正则表达式的过滤
// 例如：ban 210.34.4	allow 210.34.4.168
int is_banned(string site)
{
	int i;
	
	// 先判断是否在解禁列表中
        for (i = 0; i < sizeof(keys(OKSites)); i++)	
                if (site == keys(OKSites)[i] && values(OKSites)[i] != -1
		    || strsrch(site, keys(OKSites)[i]) != -1 && values(OKSites)[i] == -1)
                        return 0;
	
	// 再判断是否在封禁列表中
	for (i = 0; i < sizeof(keys(Sites)); i++) {
		if (site == keys(Sites)[i] && values(Sites)[i] == 0
		    || strsrch(site, keys(Sites)[i]) != -1 && values(Sites)[i] == -1 )
		{
			log_file("ATTEMPT_LOGIN",sprintf("SOMEONE  tried to login from banned site: %s\n",site));
			return 1;
		}}
	return 0;
}	

int is_multi(string site, int num)
{
	int i;
	
	for (i = 0; i < sizeof(keys(OKSites)); i++)
		if (values(OKSites)[i] && values(OKSites)[i] != -1
		    && site == keys(OKSites)[i] && num >= values(OKSites)[i])
			return 1;

	for (i = 0; i < sizeof(keys(Sites)); i++) {
		if (values(Sites)[i] != 0  && values(Sites)[i] != -1
		    && site == keys(Sites)[i] && num >= values(Sites)[i])
			return 1;
	}
	return 0;
}	

void print()
{
	int i;
	write("BANNED:\n");
	if (mapp(Sites))
		for (i = 0; i < sizeof(keys(Sites)); i++)
			write(keys(Sites)[i] + " " + values(Sites)[i] + "\n");
	write("ALLOWED:\n");
	if (mapp(OKSites))
	        for (i = 0; i < sizeof(keys(OKSites)); i++)
		        write(keys(OKSites)[i] + " " + values(OKSites)[i] + "\n");
}

void add(string site, mixed num)
{
	int i, check = 0;
	string *k_site;

	if (site == "clear") {
		Sites = ([]);
		write_file(BANNED_SITES, "", 1);
		write("清除封禁列表......完成！\n");
		return;
	}

	if ((i = member_array(site, keys(Sites))) != -1)
		if (values(Sites)[i] == num) {
			tell_object(this_player(), "这个地址已经被封禁了。\n");
			return;
		} else if (values(Sites)[i] != -1) {
			Sites[keys(Sites)[i]] = num;
			check =1;
		}

	if (match_sites(Sites, site) && !check)
		if (i = member_array(site, keys(OKSites)) == -1) {
			tell_object(this_player(), "这个地址已经被封禁了。\n");
			return;
		} else if (!num) {
			map_delete(OKSites, site);
			write(HIW"封禁 "HIR + site + HIW" Ｏ．Ｋ．\n"NOR);
			write_file(ALLOWED_SITES, "", 1);
			record_list(OKSites, ALLOWED_SITES);
			return;
		} else {
			tell_object(this_player(), "这个地址已经被封禁了。\n");
			return;
		}

	// 整理封禁列表。
	write_file(BANNED_SITES, "", 1);

	k_site = keys(Sites);
	if (num == -1)
		for (i=0; i<sizeof(k_site); i++)
			if (strsrch(k_site[i], site) != -1)
				map_delete(Sites, k_site[i]);

	Sites += ([site : num]);
	record_list(Sites, BANNED_SITES);

	// 整理解禁列表。
	write_file(ALLOWED_SITES, "", 1);
	if ((i = member_array(site, keys(OKSites))) != -1)
		if (values(OKSites)[i] == num)
			map_delete(OKSites, site);
		else	OKSites[site] = num;

	k_site = keys(OKSites);
	if (num == -1)
		for (i=0; i<sizeof(k_site); i++)
			if (strsrch(k_site[i], site) != -1)
				map_delete(OKSites, k_site[i]);

	record_list(OKSites, ALLOWED_SITES);

	write(HIW"封禁 "HIR + site + HIW" Ｏ．Ｋ．\n"NOR);
}

void delete(string site, mixed num)
{
        int i, add_flag = 0;
	string *k_site;

	if (site == "clear") {
		OKSites = ([]);
		write_file(ALLOWED_SITES, "", 1);
		write("清除解禁列表......完成！\n");
		return;
	}

	if (member_array(site, keys(OKSites)) != -1) {
		if (values(OKSites)[i] == num) {
			tell_object(this_player(), "该地址已在解禁之列。\n");
			return;
		} else  OKSites[keys(OKSites)[i]] = num;
	}
	
	if (match_sites(OKSites, site)) {
			tell_object(this_player(), "该地址已在解禁之列。\n");
			return;
	}

	// 整理封禁列表。
	write_file(BANNED_SITES, "", 1);
	if ((i = member_array(site, keys(Sites))) != -1)
		if (values(Sites)[i] >= num && num <= 0) 
			map_delete(Sites, site);
		else if (values(Sites)[i] != -1)
			Sites[site] = num;

	k_site = keys(Sites);
	if (num == -1)
		for (i=0; i<sizeof(k_site); i++)
			if (strsrch(k_site[i], site) != -1)
				map_delete(Sites, k_site[i]);

	record_list(Sites, BANNED_SITES);

	// 整理解禁列表。
	write_file(ALLOWED_SITES, "", 1);

	k_site = keys(OKSites);
	if (num == -1)
		for (i=0; i<sizeof(k_site); i++)
			if (strsrch(k_site[i], site) != -1)
				map_delete(OKSites, k_site[i]);

	if (match_sites(Sites, site)) {
		OKSites += ([ site : num ]);
	}

	record_list(OKSites, ALLOWED_SITES);

	write(HIW"解禁 "HIR + site + HIW" Ｏ．Ｋ．\n"NOR);
}

int match_sites(mapping sites, string site)
{
	int i;

	for (i=0; i<sizeof(keys(sites)); i++)
		if (strsrch(site, keys(sites)[i]) != -1 && values(sites)[i] == -1)
			return 1;
	return 0;
}

void record_list(mapping sites, string file)
{
	int i;

	if (sites)
		for (i=0; i<sizeof(keys(sites)); i++)
			write_file(file, keys(sites)[i] + " " + values(sites)[i] + "\n", 0);
}
