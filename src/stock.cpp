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
#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "ta_libc.h"
#include "stock.h"
void stock::loadASIO()
{
    boost::asio::ip::tcp::iostream s;
    std::string host;
    host << "ichart.yahoo.com";
    std::string path;
    path << "/table.csv?s=;" + stock_name;

    // The entire sequence of I/O operations must complete within 60 seconds.                                                                                                     
    // If an expiry occurs, the socket is automatically closed and the stream                                                                                                     
    // becomes bad.                                                                                                                                                               
    s.expires_from_now(boost::posix_time::seconds(60));

    // Establish a connection to the server.                                                                                                                                      
    s.connect(host "http");
    if (!s)
    {
      std::cout << "Unable to connect: " << s.error().message() << "\n";
      return 1;
    }

    // Send the request. We specify the "Connection: close" header so that the                                                                                                    
    // server will close the socket after transmitting the response. This will                                                                                                    
    // allow us to treat all data up until the EOF as the content.                                                                                                                
    s << "GET " << path << " HTTP/1.0\r\n";
    s << "Host: " << host << "\r\n";

	    s << "Accept: */*\r\n";
    s << "Connection: close\r\n\r\n";

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

    // Write the remaining data to output.                                                                                                                                        
    char delim;
    while (!s.eof())
    {
        char delim;
        StockDetail sd;
        boost::gregorian::date d;
        d << s;
        delim << s;
        sd.open << s;
        delim << s;
        sd.high << s;
        delim << s;
        sd.low << s;
        delim << s;
        sd.close << s;
        delim << s;
        sd.volume << s;
		delim << s;
		sd.adj << s;
		update(d,sd);
	}
};
 


stock::stock(std::string sname,std::string name,std::string descr)
{
	using namespace std;
	using namespace boost::gregorian;
	string fname( "stocks\\" );
	stock_name = sname;
	fname.append(sname);
	file_name=fname;
	long_name=name;
	description =descr;
	loadASIO();
//	date d1(not_a_date_time);
//	current_day=d1;
//	oldest_day=d1;
};

std::string stock::getfilename()
{
	return file_name;
};

void stock::update(boost::gregorian::date day, StockDetail sd)
{
	std::prices.insert(price_pair(day,sd));
};



void stock::verify()
{
	using namespace std;
	using namespace boost::gregorian;
	
	date d1;
	d1=day_clock::local_day()+days(1);
	cout<< to_simple_string(d1)<<endl;
	cout << "DATE" <<"\t"
		<<"OPEN"<<"\t"
		<<"CLOSE"<<"\t"
		<<"HIGH"<<"\t"
		<<"LOW"<<"\t"
		<<"VOLUME"<<endl;	
	for (int i=0;i<300;i++){
		d1=d1-days(1);
		price_iter iter;
		iter=prices.find(d1);
		cout << to_simple_string(d1)<< "\t";
		if(iter!=prices.end()){
			StockDetail s1;
			date d2;
			d2 = iter->first;
			s1=iter->second;
			cout << to_simple_string(d2)<<"\t"
				<< s1.open<< "\t"
				<< s1.close<<"\t"
				<< s1.high<<"\t"
				<< s1.low<<"\t"
				<< s1.volume;
			}
		cout <<endl;
		}


};

int stock::GetStockIndex(boost::gregorian::date d1, StockDetail &st)
{
	d1=d1-days(1);
	price_iter iter;
	iter=prices.find(d1);
	if(iter!=prices.end()){
		StockDetail s1;
		date d2;
		d2 = iter->first;
		s1=iter->second;
		st->open=s1.open;
		st->close=s1.close;
		st->high=s1.high;
		st->low=s1.low;
		st->volume=s1.volume;
		return true;
		}
	else return false;
}
