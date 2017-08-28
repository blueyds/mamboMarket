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
#include "error.hpp"
#include "sec/sec_report.hpp"

std::string sec::GenerateArchiveUrl(int a_year, int a_month)
{
	std::string year_s;
	year_s=std::to_string(a_year);
	std::string month_s;
	month_s=std::to_string(a_month);
	if (month_s.length()==1)
		{month_s="0"+month_s;}
	if (year_s.length()==2) {year_s="20"+year_s;}
	std::string s="https://www.sec.gov/Archives/edgar/monthly/xbrlrss-"+year_s+"-"+month_s+".xml";
	return s;
}



void sec::archive::fillFacts()
{
	lang_=getChildValue({0,0,0},{"rss","channel","language"});
	int item_count;
	item_count=getChildCount({0,0},{"rss","channel","item"});
	for (int x=0;x<item_count;x++)
	{
		std::string type;
		std::string cik;
		cik=getChildValue({0,0,x,0},{"rss","channel","item","cikNumber"},{"","","","edgar"});
		if(cik!=getCIK()) continue;
		type=getChildValue({0,0,x,0},{"rss","channel","item","formType"},{"","","","edgar"});
		if(type!=getForm()) continue;
		cik=getChildValue({0,0,x,0},{"rss","channel","item","cikNumber"},{"","","","edgar"});
		if(cik!=getCIK()) continue;
		int files_count;
		files_count=getChildCount({0,0,x,0},{"rss","channel","item","xbrlFiles","xbrlFile"}, {"","","","edgar","edgar"});
		for (int y=0;y<files_count;y++){
			std::string attr;
			attr=getAttribute("description",{0, 0,  x, 0, y},{"rss", "channel", "item", "xbrlFiles", "xbrlFile"},{"","","","edgar","edgar","edgar"});
			if(attr!="XBRL INSTANCE DOCUMENT") continue;
			// we found the node we are looking for.
			//createt a report item and add to vector
			std::string d;
			d=getChildValue({0,0,x,0},{"rss","channel","item","filingDate"},{"","","","edgar"});
			std::string url;
			url=getAttribute("url",{0, 0,  x, 0, y},{"rss", "channel", "item", "xbrlFiles", "xbrlFile"},{"","","","edgar","edgar","edgar"});
			report_item_t it(getCIK(),getForm(),d,url);
			items_.push_back(it);
			break;
		}
	}
}
