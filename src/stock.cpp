/*
    mamboMarket 
    Copyright (C) {2015}  {Craig Nunemaker}

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
//#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm> //std::find and std::reverse
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> //include all types plus i/o
#include "xbrl/client_https.hpp"
#include "stock.h"
#include "stlta/functions.h" //


stock::stock(std::string sname):sec_info(sname){
	stock_name = sname;
	sec_info.connect();
	
	loadASIO();
	//update_OpenClose();
	
	updateTA();
	last_update=*(dates.end()-1);
	save(sname,"OPEN CLOSE");
}

void stock::updateTA()
{
	TA::SMA(10,adj_closes,SMAs10);
	TA::EMA(13,adj_closes,EMAs13);
	TA::MACD(12,26,9,adj_closes,macds,macd_signals,macd_hists);
	TA::MAX(100,adj_closes,max_closing);
	TA::MAX(100,macd_hists,max_hist);
}

stock::stock(std::string sname,std::string name,std::string descr):
	sec_info(sname)
{
	std::string fname( "stocks\\" );
	sec_info.connect();
	stock_name = sname;
	fname.append(sname);
	file_name=fname;
	long_name=name;
	description =descr;
	loadASIO();
	updateTA();
	for (int y=2005; y<2018; y++) {
		for (int m=1;m<13;m++) {
			sec::archive a( sec_info.CIK, "10-K", y, m);
			a.connect();
			for (int i=0;i<a.items_.size();i++){
				
					using SimpleWeb::HTTPS;
					SimpleWeb::Client<HTTPS> c(a.items[i].url_.host());
				    std::shared_ptr<SimpleWeb::Client<HTTPS>::Response> response_p;
				    std::cout << a.items[i].url_.path_queries()<<"\n";
				    response_p = c.request("GET",a.items[i].url_.path_queries());
					std::cout  << response_p->http_version <<"\t" << response_p->status_code<<"\n";
					//std::cout << response_p->content.rdbuf()
					std::string data(std::istream_iterator<char>(response_p->content),std::istream_iterator<char>());
					{std::ofstream of("temp.zip");
						of << data; of.close();}
				
				
			}
		}
	}
	
//	date d1(not_a_date_time);
//	current_day=d1;
//	oldest_day=d1;
}

std::string stock::getfilename()
{
	return file_name;
}

int stock::getIndex(boost::gregorian::date d1)
{
	std::vector<boost::gregorian::date>::iterator dit;
	dit = std::find(dates.begin(), dates.end(), d1);
	if (dit == dates.end()) {return 0;} 
	else
	{return std::distance(dates.begin(),dit);}
}
void stock::verify(boost::gregorian::date d1)
{
	std::cout << "DATE\t\tOPEN\tCLOSE\tHIGH\tLOW\tVOLUME\t\tADJ\tSMA10\n";
	int index = getIndex(d1);
	std::cout << boost::gregorian::to_simple_string(dates[index]) << "\t";
	std::cout << opening_prices[index] << "\t";
	std::cout << closing_prices[index] << "\t"; 
	std::cout << highs[index] << "\t";
	std::cout << lows[index] << "\t";
	std::cout << volumes[index] << "\t";
	std::cout << adj_closes[index] << "\t";
	std::cout << SMAs10[index] << "\n";
}

void stock::verify()
{
	using namespace boost::gregorian;
	first_day_of_the_week_before fdbf(Monday);
	date d1=fdbf.get_date(day_clock::local_day());
	verify(d1);
	day_iterator diter(d1,1);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	std::cout << "verify open close vector\nOpen=" << opening_prices.back() << "\nClose=" <<closing_prices.back() <<"\nCIK=" << sec_info.CIK << "\n";
}


