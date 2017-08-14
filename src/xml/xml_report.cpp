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
#include <iostream>
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

int sec::xml_report::getChildCount(std::initializer_list<int> indices, std::initializer_list<std::string> tags)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count=0;
	parent_node=&doc_;
	for (int i : indices)
	{
		child_node=parent_node->first_node((*tagIt).c_str());
		if (i>0)
		{	for(count=1;count<=i;i++)
			{child_node=parent_node->next_sibling((*tagIt).c_str());}
		}
		tagIt++;
		parent_node=child_node; //for next iteration
	}
	//logic there should be one less index than tags. otherwise you would not be asking for a count
	child_node=parent_node->first_node((*tagIt).c_str());
	if(!child_node){count=0;}
	else
	{
		count=0;
		while (parent_node->next_sibling((*tagIt).c_str()))
		{count++;};
	}
	
	return count;
}

std::string sec::xml_report::getChildValue(std::initializer_list<int> indices, std::initializer_list<std::string> tags)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count=0;
	parent_node=&doc_;
	for (int i : indices)
	{
		child_node=parent_node->first_node((*tagIt).c_str());
		if (i>0)
		{	for(count=1;count<=i;i++)
			{child_node=parent_node->next_sibling((*tagIt).c_str());}
		}
		std::cout << (*tagIt)<<"/t"<<child_node->value()<<"/n":
		tagIt++;
		parent_node=child_node; //for next iteration
	}
	
	return child_node->value();
}

