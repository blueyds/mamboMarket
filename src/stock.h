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
#ifndef _STOCK_H
#define _STOCK_H
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <map>

class stock {
private:
	std::string file_name;
	std::string stock_name;
	std::string long_name;
	std::string description;
	typedef std::map<boost::gregorian::date,StockDetail> price_list;
	typedef price_list::iterator price_iter;
	typedef std::pair<boost::gregorian::date,StockDetail> price_pair;
	price_list daily;
	price_list weekly;
	price_list monthly;
	int loadASIO();
public:
	stock(std::string sname);
	stock(std::string sname,std::string name,std::string descr);
	int GetStockIndex(boost::gregorian::date d1, StockDetail& st);
	price_iter GetStockDailyIndex(boost::gregorian::date d1);
	price_iter GetStockDailyIndex(boost::gregorian::date d1, int error_offset); //error_offset is used to either add or decrease if date is not found
	std::string getfilename(void);
	void update (boost::gregorian::date day, StockDetail st);	
	void verify(boost::gregorian::date d1);
	void verify();

};
#endif // !_STOCK_H
