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

template<class Td> class csv_report : public report
{
public:
	typedef Td dataType;
	typedef std::vector<std::string> headerVectorType;
	typedef std::vector<Td> dataVectorType;
private:
	headerVectorType headers_;
	dataVectorType data_;
	bool hasHeader;
	bool parsed_;
	int num_cols_;
	bool parsed_;
/* inherited from report

	void connect(file_name);
	void disconnect();
*/
public:
	csv_report(std::string url,bool hasHeader=true,bool isLocal=false):
		report(url,isLocal),
		parsed_(false)
	{
		load_csvfile();
	};
	~csv_report(){;};
	
	bool isParsed(){return parsed_;};
	
	void load_csvfile(){;};


	
};

} // namespace sec
#endif //!_REPORT_H

