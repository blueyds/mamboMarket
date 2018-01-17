#ifndef SEC_REPORT_H
#define SEC_REPORT_H
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
#include <vector>
//#include "config.h"
#include "xml/xml_report.hpp"


namespace sec{

std::string GenerateSECUrl(std::string stock_symbol);
std::string GenerateArchiveUrl(int a_year, int a_month);

class report_item_t {
public:
	std::string CIK_;
	std::string form_;
	std::string date_;
	std::string url_;
	report_item_t(std::string CIK,std::string form,std::string date, std::string url):CIK_(CIK),form_(form),date_(date),url_(url){;};
};

class info : public xml_report {
private:
/* inherited from xml_report
	void load_xmlfile();
	int getChildCount(parentTag, parentInces, childTag);
	string getChildValue(parentTag, parentIndex, childTag, childIndex);
*/
/* inherited from report
	Url getUrl();
	void connect(file_name);
	void disconnect();
*/
	std::string symbol_;
	std::string CIK_;
	std::string SIC_;
	std::string SIC_desc_;
	std::string company_name_;
	std::string year_end_;
	std::string state_;
	std::vector<report_item_t> reports_;
public:
	info(std::string stock_symbol): 
		xml_report(GenerateSECUrl(stock_symbol)), 
		symbol_(stock_symbol)
			{
				load_xmlfile();
				fillFacts();
			};	// Constructor
	std::string getCIK(){return CIK_;};
	std::string getSIC(){return SIC_;};
	std::string getSIC_desc(){return SIC_desc_;};
	std::string getName(){return company_name_;};
	std::string getYearEnd(){return year_end_;};
	std::string getState(){return state_;};
	std::string getSymbol(){return symbol_;};
	void fillFacts();
}; // class sec

// a single monthly archive report
class archive: public xml_report{
private:
	std::string form_;
	std::string CIK_;
	std::string month_;
	std::string year;
	std::string edgarns_;
public:
	std::vector<report_item_t> items_;
	std::string lang_;
	archive(std::string a_CIK, 
		std::string a_form, 
		int a_year, int a_month):
		CIK_(a_CIK),
		form_(a_form),
		edgarns_("http://www.sec.gov/Archives/edgar"),
		xml_report(sec::GenerateArchiveUrl(a_year,a_month))
			{
				load_xmlfile();
				fillFacts();
			}; // 1= january 12=december
	std::string getForm(){return form_;};
	std::string getCIK(){return CIK_;};
	void fillFacts();
};//class archive
} // namespace sec
#endif //!_REPORT_H

