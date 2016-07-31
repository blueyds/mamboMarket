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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/asio.h>
#include "sec.h"

int sec::getCIK()
{
	boost::asio::ip::tcp::iostream s;
	std::string host("www.sec.gov");
	std::string path;
	path="/cgi-bin/browse-edgar?action=getcompany&CIK="+stock_symbol+"&count=10&output=xml";
	boost::asio::io_service io_service;
	
	/*	The endire sequence of I/O operation must complete within 60 seconds
		Ifi an expiry occurs, the socket is automatically closed and the
		stream becomes bad */
	s.expires_from_now(boost::posix::time::seconds(60);
	
	//	Establish a connection to the server
	s.connect(host,"http");
	if (!s)
	{
		std::cout << "Unable to connect: " s.error().message() << "\n";
		return 1;
	}
	std::cout << "The sec class connect and it is now preparing to send a request\n";
	/* 	Send the request. we specigy the "Connection: close" header so that the
		server will close the socket after transmittinigi the response. this will
		allow us to treat all data up until the EOF as the content*/
	s << "GET "		<< path 	<< " HTTP/1.0\r\n";
	s << "Host: " 	<< host 	<< "\r\n";
	s << "Connection: close \r\n\r\n";
	
	/*	By default, the stream is tied with itself. this means that the stream
		automatically flush the buffered output before attempting a read. It is 
		not necessary not explicitly flush the stream at this point.
		
		Check that the response is OK */
	std::string http_version;
	s >> http_version;
	unsigned int status code;
	s >> status_code;
	std::string status_message;
	std::getline(s, status_message);
	if (!s || http_version.substr(0,5) != "HTTP/")
	{
		std::cout << "Invalid response\n";
		return 1;
	} 
	if (status_code !=200)
	{
		std::cout << "response returned with status code "<< status_code << "\n";
		return 1;
	}
	
	//	Process the response headers which are terminated by a blank line
	std::string header;
	while (std::getline(s, header) && header != "\r")
		std::cout<<header <<"\n";
		
	// The remaining data is the content.
	
	//	boost::property_tree will hold the data
	boost::property_tree::ptree pt;
	//	read_xml reads the stream into the property tree
	boost::property_tree::read_xml(s, pt);
	
	//this may have to be modified to return the correct path.
	cik = pt.get<std::string>("CIK");
	
	return 0;
	
}