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
#include <vector>

class stock {
private:
	std::string file_name;
	std::string stock_name;
	std::string long_name;
	std::string description;
	boost::gregorian::date last_update;
	std::vector<boost::gregorian::date> dates;//DATE
	std::vector<double> opening_prices;//OPEN
	std::vector<double> closing_prices;//CLOSE
	std::vector<double> highs;//HIGH
	std::vector<double> lows;//LOW
	std::vector<double> volumes;//VOLUME
	std::vector<double> adj_closes;//ADJ
	std::vector<double> SMAs10;//SMA10
	std::vector<double> EMAs13;//EMA13
	std::vector<double> macds;//MACD
	std::vector<double> macd_signals;//MACDSIG
	std::vector<double> macd_hists;//MACDHIST
	std::vector<double> max_closing;//MAXCLOSE
	std::vector<double> max_hist; //MAXHIST
	std::vector<bool> isHist_divergence;//HISTDIV
	std::vector<double> futureROC; //FUTUREROC
	void updateTA();
	int loadASIO();
public:
	stock(std::string sname);
	stock(std::string sname,std::string name,std::string descr);
	void save(std::string fname, std::string headings);
	int getIndex(boost::gregorian::date d1);
	std::string getfilename(void);	
	void verify(boost::gregorian::date d1);
	void verify();

};
#endif // !_STOCK_H
