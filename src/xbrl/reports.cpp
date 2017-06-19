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
#include <fstream>
#include <iterator>
#include <algorithm>
#include "XmlDomDocument.h"
#include "sec.hpp"
#include "client_https.hpp"


  

sec::report::report(std::string stock_symbol)
{
	std::string s="https://www.sec.gov/cgi-bin/browse-edgar?action=getcompany&CIK="+stock_symbol+"&count=100&output=xml";
	url_ = s;
}

void sec::sec::fillFacts(std::string f_name)
{
	
	XmlDomDocument* doc = new XmlDomDocument(f_name.c_str());
    if (doc) {
        for (int i = 0; i < doc->getChildCount("companyFilings", 0, "companyInfo"); i++) {
            CIK= doc->getChildValue("companyInfo", i, "CIK", 0);
            SIC = doc->getChildValue("companyInfo", i, "SIC", 0);}
    	for (int i=0;i<doc->getChildCount("results",0,"filing");i++){
    		std::string type=doc->getChildValue("filing",i,"type",0);
    		if (type=="10-K"){;}	}  
        delete doc;
    }
}

sec::archive::archive(std::string a_CIK, std::string a_form, int a_year, int a_month)
{
	year_=std::to_string(a_year);
	std::string temp_month;
	temp_month=std::to_string(a_month);
	if (temp_month.length()==1)
		{month_="0"+temp_month;}
		else {month_=temp_month;}
	if (year_.length()==2) {year_="20"+year_;}
	std::string s="https://www.sec.gov/Archives/edgar/monthly/xbrlrss-"+year_+"-"+month_+".xml";
	url_=s;
	form_=a_form;
	CIK_=a_CIK;
}

sec::archive::archive(std::string a_CIK, std::string a_form, std::string a_year, std::string a_month)
{
	year_=a_year;
	month_=a_month;
	std::string s = "https://www.sec.gov/Archives/edgar/monthly/xbrlrss-" + year_ + "-" + month_ + ".xml";
	url_=s;
	form_=a_form;
	CIK_=a_CIK;
}

sec::archive::fillFacts(std::string f_name)
{
	XmlDomDocument* doc = new XmlDomDocument(f_name.c_str());
	if (doc) {
		for (int i = 0; i < doc->getChildCount("channel",0,"item"); i++) {
			if ((doc->getChildValue( "item", i, "edgar::formType", 0) == form_) && (doc_>getChildValue( "item",  i, "edgar::cikNumber", 0) == CIK_)){
				item_t t;
				t.CIK_= doc->getChildValue( "item" , i, "edgar::cikNumber", 0);
				t.form_= doc->getChildValue( "item" , i, "edgar::formType", 0);
				t.accession_ = doc->getChildValue( "item" , i, "edgar::accessionNumber", 0);
				t.date_ = doc->getChildValue( "item" , i, "edgar::filingDate", 0);
				items_.push_back(t);
			}
		}
		delete doc;
	}
}

void sec::report::connect()
{
	using SimpleWeb::HTTPS;
	SimpleWeb::Client<HTTPS> c(url_.host());
    std::shared_ptr<SimpleWeb::Client<HTTPS>::Response> response_p;
    std::cout << url_.path_queries()<<"\n";
    response_p = c.request("GET",url_.path_queries());
	std::cout  << response_p->http_version <<"\t" << response_p->status_code<<"\n";
	//std::cout << response_p->content.rdbuf();

	std::string data(std::istream_iterator<char>(response_p->content),std::istream_iterator<char>());
	{std::ofstream of("temp1.xml");
		of << data; of.close();}
	{std::ifstream inputfile("temp1.xml");
		std::istream_iterator<char> begin(inputfile);
		std::istream_iterator<char> end;
		std::ofstream of("temp2.xml");
		std::ostream_iterator<char> out_it(of);
		int lines=0;
		for (std::istream_iterator<char> it=begin;it!=end;it++)
		{
			if (lines>1){
				out_it=*it;
				out_it++;
			}
			if (*it=='>'){lines++;}
		}
		inputfile.close();
		of.close();
	}
	
    this->fillFacts("temp2.xml");
}