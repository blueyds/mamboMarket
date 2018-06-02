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
#include "pugixml/pugixml.hpp"
#include "error.hpp"
//#include "config.h"
#include "xml/xml_report.hpp"




void sec::xml_report::load_xmlfile()
{ //may need to run an error check in case url is not defined
	if(!isOpen()){connect();};
	if(!isParsed())
	{
		pugi::xml_parse_result result = doc_.load_file(getFileName().c_str());

		if (doc_ == NULL) {
			MSG("Document not parsed successfully.");
			return;
		}
	}
	parsed_ = true;
}

void sec::xml_report::unload_xmlfile()
{
	doc_.reset();
	disconnect();
}


/*
Selecting Nodes
XPath uses path expressions to select nodes in an XML document. The node is selected by following a path or steps. The most useful path expressions are listed below:

Expression	Description
nodename	Selects all nodes with the name "nodename"
/	Selects from the root node
//	Selects nodes in the document from the current node that match the selection no matter where they are
.	Selects the current node
..	Selects the parent of the current node
@	Selects attributes

Selecting Unknown Nodes
XPath wildcards can be used to select unknown XML nodes.

Wildcard	Description
*	Matches any element node
@*	Matches any attribute node
node()	Matches any node of any kind
*/

void sec::xml_report::findXpath(std::string xpath) 
{
	if (xpath != xpath_cur_)
	{
		nodes_ = doc_.select_nodes(xpath.c_str());
		xpath_cur_ = xpath;
	}
}


std::string sec::xml_report::getNodeStr(int index)
{
	std::string data;
	data = nodes_[index].node().text().as_string();
	return data;
}

double sec::xml_report::getNodeDbl(int index)
{
	
	double data;
	data = nodes_[index].node().text().as_double();
	return data;
}

const pugi::xml_node sec::xml_report::getNode(int index)
{
	return nodes_[index].node();
}

int sec::xml_report::getNodeCount()
{
	return nodes_.size();
}