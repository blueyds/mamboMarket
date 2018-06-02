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

//#include "config.h"
#include <time.h>
#include "sec/sec_report.hpp"
#include "error.hpp"

std::string sec::GenerateSECUrl(std::string stock_symbol)
{
	std::string s="https://www.sec.gov/cgi-bin/browse-edgar?action=getcompany&CIK="+stock_symbol+"&output=xml";
	return s;
}
std::string sec::info::getData(std::string name)
{
	findXpath("//"+name);
	return getNodeStr(0);
}

void sec::info::fillFacts()
{ 
	CIK_= getData("CIK");
	SIC_ = getData("SIC");
	company_name_ = getData("name");
	SIC_desc_ = getData("SICDescription");
	year_end_ = getData("fiscalYearEnd");
	state_ = getData("stateOfIncorporation");
	int cur_year;
	int cur_month;
	{
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		cur_year = timeinfo->tm_year + 1900;
		cur_month = timeinfo->tm_mon+1;
	}
	for (int y = cur_year; y <= cur_year; ++y)
	{
		for (int m = 1; m <6; ++m)
		{
			//MSG("YYYYMM", y * 100 + m);
			if ((y >= cur_year)&&(m > cur_month)) { continue; };//we don't want to go past current month
			sec::archive a(getCIK(), "10-Q", y, m);
			for (auto item : a.items_) { reports_.push_back(item); };
			a.changeForm("10-K");
			for (auto item : a.items_) { reports_.push_back(item); };
		}
	}
}

void sec::info::printUrls()
{
	for (report_item_t item : reports_)
	{
		MSG("Url", item.url_);
	}
}