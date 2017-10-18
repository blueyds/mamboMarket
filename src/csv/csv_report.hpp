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
/*
	The following code was derived from sec-xbrl python code available on github at
	https://github.com/altova/sec-xbrl which was released under the apache 2,.0 license.
	the apache 2.0 license is compatible with GPL 3.
*/

#include <string>
#include <vector>
#include "reports.hpp"

namespace sec{

template<class Th,class Td> class csv_report : public report
{
public:
	typedef Th headerType;
	typedef Td dataType;
	typedef std::vector<Th> headerVectorType;
	typedef std::vector<Td> dataVectorType;
private:
	headerVectorType headers_;
	dataVectorType data_;
	bool hasHeader;
/* inherited from report

	void connect(file_name);
	void disconnect();
*/
public:
	csv_report(std::string url,bool hasHeader=true,bool isLocal=false):  report(url,isLocal){
		load_csvfile();};
	~xml_report(){;};
	
	bool isParsed(){return parsed_;};
	
	void load_csvfile(){;};
	
}

} // namespace sec
#endif //!_REPORT_H

