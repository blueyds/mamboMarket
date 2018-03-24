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
			//my methodoogy is currently ignoring new lines so this followinig if statement had to be added to account for new lines
			if (data.find('\r')!=std::string::npos)
			{
				std::string data1;
				std::string data2;
				data1=data.substr(0,data.find('\r')-1);
				data2=data.substr(data.find('\n') + 1, data.length()-data.find('\n'));
				data_.push_back(data1);
				if(data2.length>0)
				{
					data_.push_back(data2);
				}
			}
			else {data_.push_back(data);}
		}
	}
	if(isOpen()){disconnect();}
}