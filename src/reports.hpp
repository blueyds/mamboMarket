#ifndef _REPORT_H
#define _REPORT_H
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
#include <sstream>
#include "url.hpp"

namespace sec{

std::string GenerateSECUrl(std::string stock_symbol);
std::string GenerateArchiveUrl(int a_year, int a_month);
class report
{
private:
	std::string fname_;
	bool open;
	std::string url_;
public:
	report():open(false);{};
	report(std::string url):url_(u),open(false);{};
	~report();
	std::string getUrl(){return url_;};
	std::string setUrl(std::string url);
	std::string getFileName(){return fname_;};
	bool isOpen(){return open;};
	void connect();
	void connect(std::string file_name);
	void disconnect();
	void virtual fillFacts()=0;
	// derivatives of report will be responsible for connecting and disconnecting with fillFacts. Also, the derivatives must ensure that url is properly defined before calling connect. This cannot be assumed with normal construction inheritance because the base constructor is called first. And there is no reason to leave the temp file laying around outside of fillFacts.
	//ifi the  derived class specifies the url for report by using report(url) in the member initializer list then the base will be defined with proper Urls and will allow the derived class to call connect , fillFacts , disconnect within the derived constructor
};

class xml_report : public report
{
private:
	rapidxml_ns::xml_document<> doc_;
	std::sstream ss_;
public:
/* inherited from report
	string getUrl()
	void connect(file_name);
	void disconnect();
*/
	xml_report();
	
	void load_xmlfile();//this will connect to the url and load file into ss_ then uses rapidxml to parse in doc_. all derived classes should call this in constructor.
	int getChildCount(std::string parentTag, int parentIndex, std::string childTag);
	std::string getChildValue(std::string parentTag, int parentIndex, std::string childTag, int childIndex);
	void fillFacts(){;};
	
}

class csv_report : public report
{
private:
	
public:
/* inherited from report
	Url getUrl();
	void connect(file_name);
	void disconnect();
*/
	csv_report();
}

class sec : public xml_report {
private:
	
public:
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
	sec(std::string stock_symbol):report(SEC::GenerateSECUrl(stock_symbol)); 	// Constructor
	void fillFacts();
}; // class sec

class report_item_t {
	public:
		std::string CIK_;
		std::string form_;
		std::string accession_;
		std::string date_;
		Url zip_reference;
	};
	
// a single monthly archive report
class archive: public xml_report{
public:
	std::vector<report_item_t> items_;
	std::string year_;
	std::string month_;
	std::string form_;
	std::string CIK_;
	archive(std::string a_CIK, std::string a_form, int a_year, int a_month):report(sec::GenerateArchiveUrl(a_year,a_month)); // 1= january 12=december
	void fillFacts();
};//class archive
} // namespace sec
#endif //!_REPORT_H

