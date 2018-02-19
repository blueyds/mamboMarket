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
//#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm> //std::find and std::reverse
#include "stock.hpp"
#include "date/date.h"
#include "stlta/stlta.hpp"

std::string sec::GenerateStockUrl(std::string stock_symbol,char interval)
{
	std::string s;
	if (interval == 'm')
	{
		s="https://www.alphavantage.co/query?function=TIME_SERIES_MONTHLY_ADJUSTED&symbol="+stock_symbol+"&apikey=14XP400VOKHHDV93&datatype=csv";
	}
	else if (interval =='w')
	{
		s="https://www.alphavantage.co/query?function=TIME_SERIES_YEARLY_ADJUSTED&symbol="+stock_symbol+"&apikey=14XP400VOKHHDV93&datatype=csv";
	}
	else 
	{
		s="https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol="+stock_symbol+"&apikey=14XP400VOKHHDV93&datatype=csv";
	}

	return s;
}

sec::stock::stock(std::string sname, char interval):
	csv_report(sec::GenerateStockUrl(sname,interval)),
	stock_name(sname)
{
	std::cout<<"preparing to enter load_csvfile\n";
	load_csvfile();
	std::cout<<"preparing to load fillfacts\n";
	fillFacts();
}

void sec::stock::updateTA()
{
	TA::SMA(10,closing_prices,SMAs10);
	TA::EMA(13,closing_prices,EMAs13);
	TA::MACD(12,26,9,closing_prices,macds,macd_signals,macd_hists);
	TA::MAX(100,closing_prices,max_closing);
	TA::MAX(100,macd_hists,max_hist);
}


int sec::stock::getIndex(date d1)
{
	std::vector<date>::iterator dit;
	dit = std::find(dates.begin(), dates.end(), d1);
	if (dit == dates.end()) {return 0;} 
	else
	{return std::distance(dates.begin(),dit);}
}

void sec::stock::fillFacts()
{
	int col=1;
	int row=1;
	std::vector<std::string>::const_iterator it;
	for (it=cbegin();it != cend();it++)
	{
		std::cout << *it;
		if(col==1){//date
			std::cout<<"D\t";
			if(row>1){
				int day;
				int month;
				int year;
				year=std::stoi(it->substr(0,4));
				std::cout << year<<"\t";
				month=std::stoi(it->substr(6,2));
				std::cout << month<<"\t";
				day=std::stoi(it->substr(9,2));
				std::cout<< day << "\t";
			}
			col++;
		}else if(col==6){//adjusted close
			std::cout<<"C\t";
			if(row>1){
				
			}
			col++;
		}else if(col==8){
			col=1;
			row++;
			std::cout <<"\n";
		} else {
			col++;
			std::cout << "\t";
		}
	}
	updateTA();
}

void sec::stock::verify(date d1)
{
	std::cout << "DATE\t\tOPEN\tCLOSE\tHIGH\tLOW\tVOLUME\t\tADJ\tSMA10\n";
	int index = getIndex(d1);
	std::cout << dates[index] << "\t";
	std::cout << closing_prices[index] << "\t"; 
	std::cout << SMAs10[index] << "\n";
}

void sec::stock::verify()
{
	for (int i = 0;i<10;i++)
	{
		std::cout << dates[i] << "\t";
		std::cout << closing_prices[i] << "\t"; 
		std::cout << SMAs10[i] << "\n";
	}
}


