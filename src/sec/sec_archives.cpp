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
#include "pugixml/pugixml.hpp"
#include "error.hpp"
#include "sec/sec_report.hpp"

sec::info::info(std::string stock_symbol) :
	xml_report(GenerateSECUrl(stock_symbol)),
	symbol_(stock_symbol)
{
	load_xmlfile();
	fillFacts();
	unload_xmlfile();
};	// Constructor

std::string sec::GenerateArchiveUrl(int a_year, int a_month)
{
	std::string year_s;
	year_s = std::to_string(a_year);
	std::string month_s;
	month_s = std::to_string(a_month);
	if (month_s.length() == 1)
	{
		month_s = "0" + month_s;
	}
	if (year_s.length() == 2) { year_s = "20" + year_s; }
	std::string s = "https://www.sec.gov/Archives/edgar/monthly/xbrlrss-" + year_s + "-" + month_s + ".xml";
	return s;
}

std::string sec::archive::getData(std::string name)
{
	findXpath("//" + name);
	return getNodeStr(0);
}


void sec::archive::fillFacts()
{
	lang_ = getData("language");
	findXpath("//edgar:xbrlFiling");
	pugi::xpath_node_set::const_iterator it=xml_begin();

	for (it; it != xml_end(); ++it)
	{
		pugi::xpath_node node = *it;
		std::string type;
		std::string d1;
		std::string cik = node.node().child("edgar:cikNumber").text().as_string();
		if (cik != getCIK()) { continue; };
		type = node.node().child("edgar:formType").text().as_string();
		d1 = node.node().child("edgar:filingDate").text().as_string();
		pugi::xml_node files = node.node().child("edgar:xbrlFiles");
		pugi::xml_node file;
		file = files.find_child_by_attribute("edgar:xbrlFile", "edgar:description", "XBRL INSTANCE DOCUMENT");
		std::string attr;
		attr = file.attribute("edgar:description").value();
		std::string t1;
		t1 = file.attribute("edgar:type").value();
		if ((attr == "XBRL INSTANCE DOCUMENT") || (t1 == "EX-101.INS"))
			{
				// we found the node we are looking for.
				//createt a report item and add to vector
				std::string url;
				url = file.attribute("edgar:url").as_string();
				report_item_t item(getCIK(), getForm(), d1, url);
				items_.push_back(item);
				break;
			}
	}
}

void sec::archive::changeForm(std::string form)
{
	items_.clear();
	form_ = form;
	fillFacts();
}
