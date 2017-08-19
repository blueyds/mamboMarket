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

#include "config.h"
#include "sec/sec_report.hpp"

std::string sec::GenerateSECUrl(std::string stock_symbol)
{
	std::string s="https://www.sec.gov/cgi-bin/browse-edgar?action=getcompany&CIK="+stock_symbol+"&output=xml";
	return s;
}


void sec::info::fillFacts()
{ 

	CIK_= getChildValue({0,0,0},{"companyFilings","companyInfo","CIK"});
	SIC_ = getChildValue({0,0,0},{"companyFilings","companyInfo","SIC"});
	company_name_ = getChildValue({0,0,0},{"companyFilings","companyInfo","name"});
	SIC_desc_ = getChildValue({0,0,0},{"companyFilings","companyInfo","SICDescription"});
	year_end_ = getChildValue({0,0,0},{"companyFilings","companyInfo","fiscalYearEnd"});
	state_ = getChildValue({0,0,0},{"companyFilings","companyInfo","stateOfIncorporation"});
}
