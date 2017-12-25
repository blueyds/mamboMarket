#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>
#include "csv/csv_report.hpp"

class options : public sec::csv_report<std::string, std::string> {
	/* 
	Options file will be a csv file in the main folder.
	Options file will consist of header line name and key
	2 columns only
	name column will consist of the key description
	key column will consist of option datum
	*/
private:
	std::string first_name;
	std::string alphaKey; //key from https://www.alphavantage.co/

public:

};
#endif