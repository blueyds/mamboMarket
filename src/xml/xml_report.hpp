#ifndef XML_REPORT_H
#define XML_REPORT_H
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
/*
	The following code was derived from sec-xbrl python code available on github at
	https://github.com/altova/sec-xbrl which was released under the apache 2,.0 license.
	the apache 2.0 license is compatible with GPL 3.
*/

#include <string>
#include <iterator>
#include <vector>
//#include "config.h"
#include "report.hpp"
#include "xml/rapidxml_ns.hpp"


namespace sec{

class xml_report : public report
{
private:
	rapidxml_ns::xml_document<char> doc_;
	std::vector<char> xml_;
	bool parsed_;
public:
/* inherited from report
	string getUrl()
	void connect(file_name);
	void disconnect();
*/
	void fillFacts(){;};
	xml_report():parsed_(false){;};
	xml_report(std::string url):report(url),parsed_(false){;};
	~xml_report(){;};
	
	bool isParsed(){return parsed_;};
	
	void load_xmlfile();
	//this will connect to the url and load file into ss_ then uses rapidxml to parse in doc_. all derived classes should call this in constructor.
	
	/* numbers will be used to find index of corresponding tag
	tags are strings or char*.
	first number will be used for first tag.
	Tags should be in order parent first then child then child.
	*/
	/*int getChildCount(std::initializer_list<int> indices, std::initializer_list<std::string> tags);
		
	std::string getChildValue(std::initializer_list<int> indices, std::initializer_list<std::string> tags);
	
	std::string getAttribute(std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::string attribute);
	*/
	int getChildCount(std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::initializer_list<std::string> ns={"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""});
		
	std::string getChildValue(std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::initializer_list<std::string> ns={"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""});
	//ns list should also include the attribute namespace oro ""
	std::string getAttribute( std::string attribute,std::initializer_list<int> indices, std::initializer_list<std::string> tags, std::initializer_list<std::string> ns={"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""});
};
} // namespace sec
#endif //!_REPORT_H

