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
#include <cstring>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "error.hpp"
#include "config.h"
#include "xml/xml_report.hpp"
#include "xml/rapidxml_ns.hpp"



void sec::xml_report::load_xmlfile()
{ //may need to run an error check in case url is not defined
	if(!isOpen()){connect();};
	if(!isParsed())
	{
	
		std::ifstream file(getFileName());
		if (!file.eof() && !file.fail()){
			file.seekg(0, std::ios_base::end);
			std::streampos fileSize = file.tellg();
			xml_.resize(fileSize);
			file.seekg(0, std::ios_base::beg);
			file.read(&xml_[0], fileSize);
		}
		xml_.push_back('\0');
		disconnect();
		doc_.parse<0>(&xml_[0]);
		parsed_=true;
	}
}
/*
int sec::xml_report::getChildCount(std::initializer_list<int> indices, std::initializer_list<std::string> tags)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count;
	parent_node=&doc_;
	for (int i : indices)
	{
		count=0;
		for (child_node= parent_node->first_node(tagIt->c_str()); child_node; child_node = child_node->next_sibling(tagIt->c_str())){
    		if (count==i) {break;}
    		else {count++;};
		}
		tagIt++;
		parent_node=child_node; //for next iteration
	}
	//logic there should be one less index than tags. otherwise you would not be asking for a count
	count=0;
	for (child_node= parent_node->first_node(tagIt->c_str()); child_node; child_node = child_node->next_sibling(tagIt->c_str())){
    	count++;
	}
	return count;
}*/
int sec::xml_report::getChildCount(std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::initializer_list<std::string> ns)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	std::initializer_list<std::string>::iterator nsIt;
	nsIt=ns.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count;
	parent_node=&doc_;
	for (int i : indices)
	{
		count=0;
		for (child_node=parent_node->first_node_ns(nsIt->c_str(),tagIt->c_str()); child_node; child_node = child_node->next_sibling_ns(nsIt->c_str(),tagIt->c_str())){
    		if (count==i) {break;}
    		else {count++;};
		}
		tagIt++;
		nsIt++;
		parent_node=child_node; //for next iteration
	}
	//logic there should be one less index than tags. otherwise you would not be asking for a count
	count=0;
	for (child_node= parent_node->first_node_ns(nsIt->c_str(),tagIt->c_str()); child_node; child_node = child_node->next_sibling_ns(nsIt->c_str(),tagIt->c_str())){
    	count++;
	}
	return count;
}
/*
std::string sec::xml_report::getChildValue(std::initializer_list<int> indices, std::initializer_list<std::string> tags)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count;
	parent_node=&doc_;
	for (int i : indices){
		count=0;
		for (child_node= parent_node->first_node(tagIt->c_str()); child_node; child_node = child_node->next_sibling(tagIt->c_str())){
    		if (count==i) {break;}
    		else {count++;};
		}
		tagIt++;
		parent_node=child_node; //for next iteration
	}
	return child_node->value();
}
*/
std::string sec::xml_report::getChildValue(std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::initializer_list<std::string> ns)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	std::initializer_list<std::string>::iterator nsIt;
	nsIt=ns.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count;
	parent_node=&doc_;
	for (int i : indices){
		count=0;
		for (child_node= parent_node->first_node_ns(nsIt->c_str(),tagIt->c_str()); child_node; child_node = child_node->next_sibling_ns(nsIt->c_str(),tagIt->c_str())){
    		if (count==i) {break;}
    		else {count++;};
		}
		tagIt++;
		nsIt++;
		parent_node=child_node; //for next iteration
	}
	if (child_node)
	{return child_node->value();}
	else return "";
}

/*
//return empty string if find nothing
std::string sec::xml_report::getAttribute(std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::string attribute)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count=0;
	parent_node=&doc_;
	for (int i : indices)
	{
		child_node=parent_node->first_node(tagIt->c_str());
		for(count=1;count<=i;count++)
			{child_node=parent_node->next_sibling(tagIt->c_str());}
		tagIt++;
		parent_node=child_node; //for next iteration
	}
	//now access rapidxml attribute on the child_node
	rapidxml_ns::xml_attribute<char> *child_attr;
	child_attr=child_node->first_attribute(attribute.c_str());
	if(child_attr){return child_attr->value();}
	else return "";
}
*/
std::string sec::xml_report::getAttribute(std::string attribute, std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::initializer_list<std::string> ns)
{
	std::initializer_list<std::string>::iterator tagIt;
	tagIt=tags.begin();
	std::initializer_list<std::string>::iterator nsIt;
	nsIt=ns.begin();
	rapidxml_ns::xml_node<char> *parent_node;
	rapidxml_ns::xml_node<char> *child_node;
	int count;
	parent_node=&doc_;
	for (int i : indices){
		count=0;
		for (child_node= parent_node->first_node_ns(nsIt->c_str(),tagIt->c_str()); child_node; child_node = child_node->next_sibling_ns(nsIt->c_str(),tagIt->c_str())){
    		if (count==i) {break;}
    		else {count++;};
		}
		tagIt++;
		nsIt++;
		parent_node=child_node; //for next iteration
	}
	if (!child_node)return "";
	//now access rapidxml attribute on the child_node
	rapidxml_ns::xml_attribute<char> *child_attr;
	child_attr=child_node->first_attribute_ns(nsIt->c_str(),attribute.c_str());
	if(child_attr){return child_attr->value();}
	else return "";
}