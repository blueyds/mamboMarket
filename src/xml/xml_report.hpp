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
#include <sstream>
#include "../config.h"
#include ABSOLUTE_SRC_REPORT_HPP
#include ABSOLUTE_SRC_XML_RAPIDXML_NS_HPP


namespace sec{

class xml_report : public report
{
private:
	rapidxml_ns::xml_document<> doc_;
	std::sstream ss_;
	bool parsed_;
public:
/* inherited from report
	string getUrl()
	void connect(file_name);
	void disconnect();
*/
	xml_report():parsed_(false){;};
	xml_report(std::string url):report(url);
	
	isParsed();{return parsed_;};
	void load_xmlfile();
	//this will connect to the url and load file into ss_ then uses rapidxml to parse in doc_. all derived classes should call this in constructor.
	
	int getChildCount(std::string parentTag, int parentIndex, std::string childTag);
	
	std::string getChildValue(std::string parentTag, int parentIndex, std::string childTag, int childIndex);
	
	void fillFacts(){;};
	
}
} // namespace sec
#endif //!_REPORT_H

