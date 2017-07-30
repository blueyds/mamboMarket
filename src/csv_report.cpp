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

int sec::xml_report::getChildCount(std::string parentTag, int parentIndex, std::string childTag)
{
	using namespace rapidxml_ns;
	xml_document<> doc;
	doc.parse<0>(ss_.cstr());
	return 0;
}

std::string sec::xml_report::getChildValue(std::string parentTag, int parentIndex, std::string childTag, int childIndex)
{
	
	return "";
}



void sec::sec::fillFacts(std::string f_name)
{ 
	using namespace rapidxml_ns;
	xml_document<> doc;
	doc.parse<0>(text.c_str());
	
	
        for (int i = 0; i < doc->getChildCount("companyFilings", 0, "companyInfo"); i++) {
            CIK= doc->getChildValue("companyInfo", i, "CIK", 0);
            SIC = doc->getChildValue("companyInfo", i, "SIC", 0);}
    	for (int i=0;i<doc->getChildCount("results",0,"filing");i++){
    		std::string type=doc->getChildValue("filing",i,"type",0);
    		if (type=="10-K"){;}	}  
        delete doc;
    }
}
