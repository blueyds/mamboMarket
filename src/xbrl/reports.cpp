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
	std::string s="https://www.sec.gov/cgi-bin/browse-edgar?action=getcompany&CIK="+stock_symbol+"&count=10&output=xml";
	url_ = s;
}

void sec::sec::fillFacts(std::string f_name)
{
	
	XmlDomDocument* doc = new XmlDomDocument(f_name.c_str());
	std::cout << "fillFacts called/n";
    if (doc) {
        for (int i = 0; i < doc->getChildCount("companyFilings", 0, "companyInfo"); i++) {
            CIK= doc->getChildValue("companyInfo", i, "CIK", 0);
            printf("CIK      - %s\n", CIK.c_str());
            SIC = doc->getChildValue("companyInfo", i, "SIC", 0);
            printf("SIC      - %s\n", SIC.c_str());
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
	{std::ofstream of("temp.xml");
		of << data; of.close();}
	{ std::ifstream inputfile("temp.xml");
		std::istream_iterator<char> begin(inputfile);
		std::istream_iterator<char> end;
		std::ofstream of("data.xml");
		std::ostream_iterator<char> out_it(of);
		for (std::istream_iterator<char> it=begin;it!=end;it++)
		{	
			out_it=*it;
			out_it++;
			if (*it='>')
			{
				std::istream_iterator<char> tit=it;
				tit++;
				if (*tit='<')
				{
					out_it='\n';
					out_it++;
				}
			}
		}
		inputfile.close();
		of.close();
	}	
    this->fillFacts("data.xml");
}