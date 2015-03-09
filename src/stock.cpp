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
#include <fstream>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "ta_libc.h"
#include "stock.h"


stock::stock(std::string sname)
{
	using namespace std;
	using namespace boost::gregorian;
	string fname( "stocks\\" );
	fname.append(sname);
//	date d1(not_a_date_time);
//	current_day=d1;
//	oldest_day=d1;

		file_name=fname;
	
};
stock::stock(std::string sname,std::string name,std::string descr)
{
	using namespace std;
	using namespace boost::gregorian;
	string fname( "stocks\\" );
	stock_name = sname;
	fname.append(sname);
	file_name=fname;
	long_name=name;
	description =descr;
//	date d1(not_a_date_time);
//	current_day=d1;
//	oldest_day=d1;
};

std::string stock::getfilename()
{
	return file_name;
};

void stock::update(boost::gregorian::date day,
					double open,
					double close,
					double high,
					double low,
					double volume)
{
	using namespace std;
	using namespace boost::gregorian;
		StockDetail sd;
		sd.close=close;
		sd.open=open;
		sd.high=high;
		sd.low=low;
		sd.volume=volume;
		prices.insert(price_pair(day,sd));
	
/*	if (current_day.is_not_a_date()) 
		current_day=day;
	if (oldest_day.is_not_a_date()) 
		oldest_day=day;

	if (day > current_day) 
		current_day = day;
	if (day < oldest_day) 
		oldest_day =day;*/
};



void stock::verify()
{
	using namespace std;
	using namespace boost::gregorian;
	
	date d1;
	d1=day_clock::local_day()+days(1);
	cout<< to_simple_string(d1)<<endl;
	cout << "DATE" <<"\t"
		<<"OPEN"<<"\t"
		<<"CLOSE"<<"\t"
		<<"HIGH"<<"\t"
		<<"LOW"<<"\t"
		<<"VOLUME"<<endl;	
	for (int i=0;i<300;i++){
		d1=d1-days(1);
		price_iter iter;
		iter=prices.find(d1);
		cout << to_simple_string(d1)<< "\t";
		if(iter!=prices.end()){
			StockDetail s1;
			date d2;
			d2 = iter->first;
			s1=iter->second;
			cout << to_simple_string(d2)<<"\t"
				<< s1.open<< "\t"
				<< s1.close<<"\t"
				<< s1.high<<"\t"
				<< s1.low<<"\t"
				<< s1.volume;
			}
		cout <<endl;
		}


};

int stock::GetStockIndex(boost::gregorian::date d1, StockDetail &st)
{
	d1=d1-days(1);
	price_iter iter;
	iter=prices.find(d1);
	if(iter!=prices.end()){
		StockDetail s1;
		date d2;
		d2 = iter->first;
		s1=iter->second;
		st->open=s1.open;
		st->close=s1.close;
		st->high=s1.high;
		st->low=s1.low;
		st->volume=s1.volume;
		return true;
		}
	else return false;
}
