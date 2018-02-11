#include <fstream>
#include <string>
#include <vector>
#include "csv/csv_report.hpp"

void sec::csv_report::load_csvfile()
{
	if(!isOpen()){connect();};
	if(!isParsed())
	{
		std::string fname;
		fname=getFileName();
		std::ifstream file(fname);
		while ( file.good() )
		{
			std::string data;
			std::getline ( file, data, ',' ); // read a string until next comma
			data_.push_back(data);
		}
	}
	disconnect();
}