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
sec::archive::archive(std::string a_CIK, std::string a_form, int a_year, int a_month)
{
	load_xmlfile();
	fillFacts();
}


void sec::archive::fillFacts(std::string f_name)
{
	for (int i = 0; i < getChildCount("channel",0,"item"); i++) {
			if ((getChildValue( "item", i, "edgar::formType", 0) == form_) && (getChildValue( "item",  i, "edgar::cikNumber", 0) == CIK_)){
				report_item_t t;
				t.CIK_= getChildValue( "item" , i, "edgar::cikNumber", 0);
				t.form_= getChildValue( "item" , i, "edgar::formType", 0);
				t.accession_ = getChildValue( "item" , i, "edgar::accessionNumber", 0);
				t.date_ = getChildValue( "item" , i, "edgar::filingDate", 0);
				items_.push_back(t);
			}
		}
}



sec::archive::archive(std::string a_CIK, std::string a_form, std::string a_year, std::string a_month)
{
	year_=a_year;
	month_=a_month;
	std::string s = "https://www.sec.gov/Archives/edgar/monthly/xbrlrss-" + year_ + "-" + month_ + ".xml";
	setUrl(s);
	form_=a_form;
	CIK_=a_CIK;
	load_xmlfile();
}

