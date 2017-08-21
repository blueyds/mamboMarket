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
	MY_TEST_MESSAGE("just entered arcchive fillfacts");
	lang_=getChildValue({0,0,0},{"rss","channel","language"});
}
