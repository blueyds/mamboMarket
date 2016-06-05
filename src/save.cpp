#include <iostream>
#include <sstream>
#include <string>
#include "stock.h"


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
	
	std::cout << "endtering save\n";
	std::stringstream ss(headings);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	std::cout <<vstrings[0] << "\t" <<vstrings[1]<<"\n";
	//std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}