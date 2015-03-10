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
#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "quotes.h"
#include "stock.h"
#include "stocks.h"
#include "csv.h"
#include <boost/asio/ip/tcp.hpp>

void loadASIO()
{
	boost::asio::ip::tcp::iostream s;
	std::string host;
	host << "www.google.com";
	std::string path;
	path << "/";

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
    std::cout << s.rdbuf();
  }
	
}

void quotes::update(int periods)
{
	using namespace std;
	using namespace boost::gregorian;
	using namespace boost::posix_time;
	ptime starttime = second_clock::local_time();
	//TODO open index
	//TODO read to new stocks object
	//1. create stocks class
	stocks s1;
	{	
		//then READ FROM FILE
		std::ifstream ifs("stocks\\index");
		
		boost::archive::text_iarchive ia(ifs);
		// read archive to archive
		ia >> s1;
		// archive and stream closed when destructors are called
	}
	cout << "Index file for stock list has been loaded into memory"<<endl;
	//TODO use stock object to cycle thru
	//we will iterate through our symbols and update ind stock
	int start=0; //start iterator
	int max=s1.s1.size();//we can quit when we reach the last one.
	int x;
	boost::gregorian::date startdate;
	startdate=day_clock::local_day() - days(periods);
	cout << "Retrieving and updating individual stocks from " <<to_simple_string(startdate)<< endl;
	for (x=start; x< max;x++)
	{
		
		{
			string s;
			s="google.exe ";
			s+=s1.s1[x];
			s+=" ";
			s+=boost::gregorian::to_iso_extended_string(startdate);
			
			//Call yahoo.exe which will 
			//connect to yahoo and download stock data and 
			//create csv file
			//system() is in standard library cstdlib
			
			int rtype=system(s.c_str());
			
			//TODO read new csv file and update stock files
			
			//reset our parameters so we can do next bunch
		}
		{
			stock st(s1.s1[x]);
			{
				std::ifstream ifs(st.getfilename().c_str());
			
	
				boost::archive::text_iarchive ia(ifs);
			
				ia >> st;
				ifs.close();
			}
			
			load(&st);
			st.updateTA(startdate);
			{
				std::ofstream ofs(st.getfilename().c_str(),ios::out|ios::trunc);
				boost::archive::text_oarchive oa(ofs);
				oa << st;
				ofs.close();
			}
			int perc = int((float(x)  / float(max)) *100);
			cout<< s1.s1[x] << " "<<perc<<"%"<<endl;
		}
	}
	ptime endtime = second_clock::local_time();
	cout<< endl<< "Update started at "<< boost::posix_time::to_simple_string(starttime) << endl;
	cout<<"Update ended at "<<boost::posix_time::to_simple_string(endtime)<<endl;
}

//loads a csv file saved by yahoo.exe and updates the st with those data
void quotes::load(stock* st)
{
	using namespace std;
	using boost::lexical_cast;
	ifstream is("quotes.csv");
	bool firstline=true;
	int count=0;
	while (true)
    {
		
		

		typedef vector<string> rec_t;

        rec_t rec = CsvGetLine(is,true,44,10,34);
		if (!firstline)
		{
        	if (rec.size() == 0) break;

        	rec_t::iterator x = rec.begin();
        
			string sym;//symbol
			boost::gregorian::date d3;
			double open;
			double close;
			double high;
			double low;
			double volume;
			string sg,sd,sm,sy;
			sg=string(*x);
			sd=sg.substr(0,sg.find_first_of('-'));
			if(sd.size()==1) 
			{	string s10='0'+sd;
				sd =s10;
			}
			sm=sg.substr(sg.find_first_of('-')+1,sg.find_last_of('-')-2);
			sy="20"+sg.substr(sg.find_last_of('-')+1,sg.size());
			string d5s;
			d5s = sy + '-' + sm + '-' + sd;
			d3=boost::gregorian::from_simple_string(d5s);
			x++;
			open=lexical_cast<double>(*x);
			x++;
			high=lexical_cast<double>(*x);
			x++;
			low=lexical_cast<double>(*x);
			x++;
			close=lexical_cast<double>(*x);
			x++;
			volume=lexical_cast<double>(*x);
			st->update(d3,open,close,high,low,volume);
		
		}else firstline=false;
		count++;
	}
	cout << count << " ";
	is.close();
}
