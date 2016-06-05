
#include <vector>
#include <string>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> //include all types plus i/o
#include <boost/asio.hpp>
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
		std::cout << "Vectors were reversed\n";
	}
}