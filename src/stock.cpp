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
#include <map>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> //include all types plus i/o
#include <boost/asio.hpp>
#include "ta-lib/ta_libc.h"
#include "StockDetail.h"
#include "stock.h"

int stock::loadASIO()
{
    boost::asio::ip::tcp::iostream s;
    std::string host( "ichart.yahoo.com");
    std::string path("/table.csv?s=" + stock_name);

	boost::asio::io_service io_service;

  	
    // The entire sequence of I/O operations must complete within 60 seconds.                                                                                                    
    // If an expiry occurs, the socket is automatically closed and the stream                                                                                                    
    // becomes bad.                                                                                                                                                               
    s.expires_from_now(boost::posix_time::seconds(60));

    // Establish a connection to the server.                                                                                                                                      
    s.connect(host, "http");
    if (!s)
    {
      std::cout << "Unable to connect: " << s.error().message() << "\n";
      return 1;
    }
	std::cout << "THE stock class connected and it is now preparing to send a request" << "\n";
    // Send the request. We specify the "Connection: close" header so that the                                                                                                   
    // server will close the socket after transmitting the response. This will                                                                                                   
    // allow us to treat all data up until the EOF as the content.                                                                                                               
    s << "GET " << path << " HTTP/1.0\r\n";
    s << "Host: " << host << "\r\n";
	s << "Accept: */*\r\n";
    s << "Connection: close\r\n\r\n";

	std::cout << "The stock class sent a request" << "\n";
    // By default, the stream is tied with itself. This means that the stream                                                                                                    
    // automatically flush the buffered output before attempting a read. It is                                                                                                   
    // not necessary not explicitly flush the stream at this point.                                                                                                              

    // Check that response is OK.                                                                                                                                                 
    std::string http_version;
    s >> http_version;
    unsigned int status_code;
    s >> status_code;
    std::string status_message;
    std::getline(s, status_message);
    if (!s || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return 1;
    }
    if (status_code != 200)
    {
      std::cout << "Response returned with status code " << status_code << "\n";
      return 1;
    }

    // Process the response headers, which are terminated by a blank line.                                                                                                        
    std::string header;
    while (std::getline(s, header) && header != "\r")
      std::cout << header << "\n";
    std::cout << "\n";
	std::cout<<"The above was the header output\n";

    // Write the remaining data to output.
	bool isFirstLine=true;
	while (!s.eof())
    {
		//std::cout << "entering while loop and isFirstLIne= "<<isFirstLine <<"\n";
		std::string datum;
		std::string ds;
		double open, high, low, close, volume, adj;
		if (!isFirstLine)
		{
			std::getline(s,datum,'-');	    
			ds=datum;
			std::getline(s,datum,'-');
			ds = ds + datum;
			std::getline(s,datum,',');
			ds = ds + datum;
		}
		//std::cout << "L106\t";
		if(isFirstLine) ds="19900101";
		//std::cout << ds<<"\t";
		if(ds=="")break;
		boost::gregorian::date _date(boost::gregorian::from_undelimited_string(ds));
		std::getline(s,datum,',');
		if(!isFirstLine) open = strtod(datum.c_str(),NULL);
		std::getline(s,datum,',');
		if(!isFirstLine) high  = strtod(datum.c_str(),NULL);
		std::getline(s,datum,',');
		if(!isFirstLine) low = strtod(datum.c_str(),NULL);
		std::getline(s,datum,',');
		if(!isFirstLine) close = strtod(datum.c_str(),NULL);
		std::getline(s,datum,',');
		if(!isFirstLine) volume = strtod(datum.c_str(),NULL);
		std::getline(s,datum,'\n');
		if(!isFirstLine) adj = strtod(datum.c_str(),NULL);
		if(isFirstLine)
		{
			//std::cout << "Break routing in first line\n";
			isFirstLine=false;
		}
		else
		{
			//std::cout << boost::gregorian::to_simple_string(_date)<<open<< "\n";
			StockDetail sd;
			sd.open=open;
			sd.high=high;
			sd.low=low;
			sd.close=close;
			sd.volume=volume;
			sd.adj=adj;
		  //std::cout <<sd<<"\n";
			update(_date,sd);
			//verify(_date);
		}
	}
}
 
stock::stock(std::string sname){
	stock_name = sname;
	loadASIO();
	update_OpenClose();
	updateTA();
}

void stock::updateTA(){
	
}
void stock::update_OpenClose(){
	opening_prices.resize(0);
	closing_prices.resize(0);
	for (price_iter it=daily.begin(); it != daily.end();it++){
		opening_prices.push_back(it->second.open);
		closing_prices.push_back(it->second.close);
	}
}

stock::stock(std::string sname,std::string name,std::string descr)
{
	std::string fname( "stocks\\" );
	stock_name = sname;
	fname.append(sname);
	file_name=fname;
	long_name=name;
	description =descr;
	loadASIO();
//	date d1(not_a_date_time);
//	current_day=d1;
//	oldest_day=d1;
}

std::string stock::getfilename()
{
	return file_name;
}

void stock::update(boost::gregorian::date day, StockDetail sd)
{
	daily.insert(price_pair(day,sd));
}

void stock::verify(boost::gregorian::date d1)
{
	std::cout << "DATE\t\tOPEN\tCLOSE\tHIGH\tLOW\tVOLUME\t\tADJ\n";
	price_iter piter;
	piter=GetStockDailyIndex(d1);
	if (piter!=daily.end()){
		std::cout << boost::gregorian::to_simple_string(piter->first) << "\t"<< piter->second;
	}
	else{
		std::cout << boost::gregorian::to_simple_string(d1)<<"\tcould not find date in index: \n";
	}
}

void stock::verify()
{
	using namespace boost::gregorian;
	first_day_of_the_week_before fdbf(Monday);
	date d1=fdbf.get_date(day_clock::local_day());
	verify(d1);
}

stock::price_iter stock::GetStockDailyIndex(boost::gregorian::date d1)
{
	return GetStockDailyIndex(d1,0);
}


stock::price_iter stock::GetStockDailyIndex(boost::gregorian::date d1, int error_offset)
{
	using namespace boost::gregorian;
	day_iterator diter(d1,1);
	stock::price_iter piter;
	bool IterCheck(true);
	while(IterCheck){
		piter=daily.find(*diter);
		if (piter!=daily.end()){break;}
		else{
			if (error_offset <0) ++diter;
			if (error_offset >0) --diter;
			if (error_offset == 0) {break;}
		}
	}
	return piter;
}

int stock::GetStockIndex(boost::gregorian::date d1, StockDetail& st)
{
	price_iter iter;
	//std::cout<<"entering getstockindex\n";
	iter= GetStockDailyIndex(d1);
	if(iter !=daily.end()){
		st=iter->second;
		return true;
		}
	else {
		std::cout << "Could not find date in index: "<< boost::gregorian::to_simple_string(d1);
		return false;
	};
}
