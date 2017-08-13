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
/*
	The following code was derived from sec-xbrl python code available on github at
	https://github.com/altova/sec-xbrl which was released under the apache 2,.0 license.
	the apache 2.0 license is compatible with GPL 3.
*/

#include <string>
#include <vector>
#include "config.h"
#include "xml/xml_report.hpp"


namespace sec{

std::string GenerateSECUrl(std::string stock_symbol);
std::string GenerateArchiveUrl(int a_year, int a_month);

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
	std::string symbol;
	std::string CIK;
	std::string SIC;
	std::string SIC_desc;
	std::string company_name;
public:
	info(std::string stock_symbol):xml_report(GenerateSECUrl(stock_symbol)); 	// Constructor
	std::string getCIK(){return CIK;};
	std::string getSIC(){return SIC;};
	std::string getSIC_desc(){return SIC_desc;};
	std::string getName(){return company_name;};
	void fillFacts();
}; // class sec

class report_item_t {
	public:
		std::string CIK_;
		std::string form_;
		std::string accession_;
		std::string date_;
		std::string zip_reference;
	};
	
// a single monthly archive report
class archive: public xml_report{
public:
	std::vector<report_item_t> items_;
	std::string year_;
	std::string month_;
	std::string form_;
	std::string CIK_;
	archive(std::string a_CIK, std::string a_form, int a_year, int a_month):CIK_(a_CIK),form_(a_form),xml_report(sec::GenerateArchiveUrl(a_year,a_month)); // 1= january 12=december
	void fillFacts();
};//class archive
} // namespace sec
#endif //!_REPORT_H

