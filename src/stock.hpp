#ifndef _STOCK_H
#define _STOCK_H

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
#include <string>
#include <vector>
#include "date/date.h"
#include "csv/csv_report.hpp"

namespace sec {
std::string GenerateStockUrl(std::string stock_symbol,char interval);


	class stock : public csv_report {
	private:
		std::string stock_name;
		std::string long_name;
		std::string description;
		date last_update;
		//all vectors contain most recent data at the front
		std::vector<date> dates;//DATE
		std::vector<double> closing_prices;//OPEN
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
		void load_stocks();
	public:
		stock(std::string sname,char interval='d');//'d','w','m'
		void fillFacts();
		int getIndex(date d1);
		void verify(date d1);
		void verify();

	};
#endif // !_STOCK_H
}