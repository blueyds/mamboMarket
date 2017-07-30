/*
    Copyright (C) {2016}  {Craig Nunemaker}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "rapidxml_ns.hpp"
#include "sec.hpp"

void sec::xml_report::xml_report()
{
	
	std::ifstream fin("temp342");
	copy(istreambuf_iterator<char>(fin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(ss_));
}

void sec::xml_report::load_xmlfile()
{ //may need to run an error check in case url is not defined
	connect;
	std::ifstream fin(getFileName());
	copy(istreambuf_iterator<char>(fin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(ss_));
	disconnect();
	doc_.parse<0>(ss_.cstr());
}

int sec::xml_report::getChildCount(std::string parentTag, int parentIndex, std::string childTag)
{//add logic in case parent is not inside the first level
	rapidxml_ns::xml_node<rapidxml::Ch> *parent_node;
	rapidxml_ns::xml_node<rapidxml::Ch> *child_node;
	bool working=true;
	int count=0;
	parent_node=doc.first_node(parentTag.cstr());
	if !(parent_node){return 0;};
	child_node=parent_node->first_node(childTag.cstr());
	if !(child_node){return 0;};
	do {
		child_node=parent_node->next_sibling(childTag.cstr());
		if (child_node){count++;}
		else {working=false;};
	} while (working);
	return count;
}

std::string sec::xml_report::getChildValue(std::string parentTag, int parentIndex, std::string childTag, int childIndex)
{
	rapidxml_ns::xml_node<rapidxml::Ch> *parent_node;
	rapidxml_ns::xml_node<rapidxml::Ch> *child_node;
	bool working=true;
	int count=0;
	parent_node=doc.first_node(parentTag.cstr());
	if (parentIndex
	if !(parent_node){return 0;};
	child_node=parent_node->first_node(childTag.cstr());
	if !(child_node){return 0;};
	do {
		child_node=parent_node->next_sibling(childTag.cstr());
		if (child_node){count++;}
		else {working=false;};
	} while (working);
	return count;
	return "";
}



void sec::sec::fillFacts(std::string f_name="")
{ 
	for (int i = 0; i < doc->getChildCount("companyFilings", 0, "companyInfo"); i++) 
	{
		CIK= doc->getChildValue("companyInfo", i, "CIK", 0);
		SIC = doc->getChildValue("companyInfo", i, "SIC", 0);
	}
	for (int i=0;i<doc->getChildCount("results",0,"filing");i++)
	{
		std::string type=doc->getChildValue("filing",i,"type",0);
		if (type=="10-K"){;}
	}
}
