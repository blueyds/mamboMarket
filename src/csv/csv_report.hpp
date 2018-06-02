#ifndef CSV_REPORT_H
#define CSV_REPORT_H
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
#include <vector>
#include "report.hpp"

namespace sec{

class csv_report : public report
{
private:
	std::vector<std::string> headers_; //headers are not implemented yet
	std::vector<std::string> data_;
	bool header_;
	bool parsed_;
	int num_cols_;
/* inherited from report

	void connect(file_name);
	void disconnect();
*/
public:
	csv_report(std::string url,bool hasHeader=true,bool isLocal=false):
		report(url,isLocal),
		header_(hasHeader),
		parsed_(false){;};
	~csv_report(){;};
	void fillFacts(){;};
	std::vector<std::string>::const_iterator cbegin(){return data_.cbegin();};
	std::vector<std::string>::const_iterator cend(){return data_.cend();};
	bool isParsed(){return parsed_;};
	
	void load_csvfile();
	void unload_csvfile();
	std::string getValue(int row, int col);
	

	
};

} // namespace sec
#endif //!_REPORT_H

