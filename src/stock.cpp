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
#include <sstream>
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
					SimpleWeb::Client<HTTPS> c(a.items_[i].zip_reference.host());
				    std::shared_ptr<SimpleWeb::Client<HTTPS>::Response> response_p;
				    std::cout << a.items_[i].zip_reference.path_queries()<<"\n";
				    response_p = c.request("GET",a.items_[i].zip_reference.path_queries());
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
	//std::cout << "THE stock class connected and it is now preparing to send a request" << "\n";
    // Send the request. We specify the "Connection: close" header so that the                                                                                                   
    // server will close the socket after transmitting the response. This will                                                                                                   
    // allow us to treat all data up until the EOF as the content.                                                                                                               
    s << "GET " << path << " HTTP/1.0\r\n";
    s << "Host: " << host << "\r\n";
	s << "Accept: */*\r\n";
    s << "Connection: close\r\n\r\n";

	//std::cout << "The stock class sent a request" << "\n";
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
      //std::cout << "Response returned with status code " << status_code << "\n";
      return 1;
    }

    // Process the response headers, which are terminated by a blank line.                                                                                                        
    std::string header;
    //while (std::getline(s, header) && header != "\r")
    //  std::cout << header << "\n";
    //std::cout << "\n";
	//std::cout<<"The above was the header output\n";

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
			dates.push_back(_date);
			opening_prices.push_back(open);
			closing_prices.push_back(close);
			highs.push_back(high);
			lows.push_back(low);
			volumes.push_back(volume);
			adj_closes.push_back(adj);
		  //std::cout <<sd<<"\n";
			//update(_date,sd);
			//verify(_date);
		}
	}
	//check if entries are reversed and if so fix them
	std::vector<boost::gregorian::date>::iterator it1;
	it1 = dates.end()-1;
	if(*it1 < *dates.begin())
	{
		std::reverse(dates.begin(),dates.end());
		std::reverse(opening_prices.begin(),opening_prices.end());
		std::reverse(closing_prices.begin(),closing_prices.end());
		std::reverse(highs.begin(),highs.end());
		std::reverse(lows.begin(),lows.end());
		std::reverse(volumes.begin(),volumes.end());
		std::reverse(adj_closes.begin(),adj_closes.end());
		//std::cout << "Vectors were reversed\n";
	}
}

/*
Heading options should be separated by comma and include:
	DATE
	OPEN
	CLOSE
	HIGH
	LOW
	VOLUME
	ADJ
	SMA10
*/
void stock::save(std::string fname, std::string headings)
{
	bool hasDATE(false);
	bool hasOPEN(false);
	bool hasCLOSE(false);
	bool hasHIGH(false);
	bool hasLOW(false);
	bool hasVOLUME(false);
	bool hasADJ(false);
	bool hasSMA10(false);
	bool hasEMA13(false);
	bool hasMACD(false);
	bool hasMACDSIG(false);
	bool hasMACDHIST(false);
	bool hasMAXCLOSE(false);
	bool hasMAXHIST(false);
	bool hasHISTDIV(false);
	bool hasFUTUREROC(false);                                                                                           
	std::stringstream ss(headings);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	int count = vstrings.size();
	int columns=0;
	std::cout << "vstrings size =" << count << "\n";
	for (int i = 0; i < vstrings.size(); i++)
	{ 
		if (vstrings[i].find("DATE")!=std::string::npos)
			{hasDATE=true;columns=columns+1;};
		if (vstrings[i].find("OPEN") !=std::string::npos)
			{hasOPEN=true;columns=columns+1;};
		if (vstrings[i].find("CLOSE") != std::string::npos)
			{hasCLOSE=true;columns=columns+1;};
		if (vstrings[i].find("HIGH") !=std::string::npos)
			{hasHIGH=true;columns=columns+1;};
		if (vstrings[i].find("LOW") !=std::string::npos)
			{hasLOW=true;columns=columns+1;};
		if (vstrings[i].find("VOLUME") !=std::string::npos)
			{hasVOLUME=true;columns=columns+1;};
		if (vstrings[i].find("ADJ") != std::string::npos)
			{hasADJ=true;columns=columns+1;};
		if (vstrings[i].find("SMA10") !=std::string::npos)
			{hasSMA10=true;columns=columns+1;};
		if (vstrings[i].find("EMA13") !=std::string::npos)
			{hasEMA13=true;columns=columns+1;};
		if (vstrings[i].find("MACD") !=std::string::npos)
			{hasMACD=true;columns=columns+1;};
		if (vstrings[i].find("MACDSIG") !=std::string::npos)
			{hasMACDSIG=true;columns=columns+1;};
		if (vstrings[i].find("MACDHIST") !=std::string::npos)
			{hasMACDHIST=true;columns=columns+1;};
		if (vstrings[i].find("MAXCLOSE") !=std::string::npos)
			{hasMAXCLOSE=true;columns=columns+1;};
		if (vstrings[i].find("MAXHIST") !=std::string::npos)
			{hasMAXHIST=true;columns=columns+1;};
		if (vstrings[i].find("HISTDIV") !=std::string::npos)
			{hasHISTDIV=true;columns=columns+1;};
		if (vstrings[i].find("FUTUREROC") !=std::string::npos)
			{hasFUTUREROC=true;columns=columns+1;};
	}
	std::cout << hasDATE<< "\t" << hasOPEN << "\t" << hasCLOSE << "\t" << hasHIGH<< "\t" << hasLOW<< "\t"<<columns<<"\n"; 
	std::size_t csvfound;
	csvfound=fname.find(".csv");
	if (csvfound==std::string::npos) //fname does not have csv suffix
		{fname.append(".csv"); }
	std::ofstream ofs(fname.c_str());
	if (ofs.is_open()){
		count = dates.size();
		for (int i = 0; i < count; i++)
		{
			int counter=0;
			if (hasDATE)
			{
				counter = counter +1;
				ofs << dates[i];
				if (counter<columns){ofs << ",";};
			}
			if (hasOPEN)
			{
				counter = counter +1;
				ofs << opening_prices[i];
				if (counter<columns){ofs <<",";};
			}
			if (hasCLOSE)
			{
				counter = counter +1;
				ofs << closing_prices[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasHIGH)
			{
				counter = counter +1;
				ofs << highs[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasLOW)
			{
				counter = counter +1;
				ofs << lows[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasVOLUME)
			{
				counter = counter +1;
				ofs << volumes[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasADJ)
			
			{
				counter = counter +1;
				ofs << adj_closes[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasSMA10)
			{
				counter = counter +1;
				ofs << SMAs10[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasEMA13)
			{
				counter = counter +1;
				ofs << EMAs13[i];
				if (counter<columns){ofs << ",";}
			}
			ofs << "\n";
		}
		ofs.close();
	}
}

