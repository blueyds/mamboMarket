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
#include <sstream>
#include <cstring>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "config.h"
#include "xml/xml_report.hpp"
#include "xml/rapidxml_ns.hpp"

sec::xml_report::~xml_report()
{
	delete xml_;
}

void sec::xml_report::load_xmlfile()
{ //may need to run an error check in case url is not defined
	if(!isOpen()){connect();};
	if(!isParsed())
	{
		std::stringstream ss;
		std::ifstream fin(getFileName().c_str());
		std::copy(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(ss));
		disconnect();
		xml_ = new char[ss.str().length()+1];
		std::strcpy(xml_,ss.str().c_str());
		doc_.parse<0>(xml_);
		parsed_=true;
	}
}

int sec::xml_report::getChildCount(std::string parentTag, int parentIndex, std::string childTag)
{//add logic in case parent is not inside the first level
	load_xmlfile();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	bool working=true;
	int count=0;
	parent_node=doc_.first_node(parentTag.c_str());
	if (!parent_node){return 0;};
	child_node=parent_node->first_node(childTag.c_str());
	if (!child_node){return 0;};
	do {
		child_node=parent_node->next_sibling(childTag.c_str());
		if (child_node){count++;}
		else {working=false;};
	} while (working);
	return count;
}

std::string sec::xml_report::getChildValue(std::string parentTag, int parentIndex, std::string childTag, int childIndex)
{
	load_xmlfile();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	bool working=true;
	int count=0;
	parent_node=doc_.first_node(parentTag.c_str());
	for(int i=0; i !=parentIndex;i++)
		{parent_node=doc_.next_sibling(parentTag.c_str());};
	child_node=parent_node->first_node(childTag.c_str());
	for(int i=0;i != childIndex;i++)
		{child_node=parent_node->next_sibling(childTag.c_str());};
	std::string value(child_node->value());
	return value;
}

