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
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> //include all types plus i/o
#include "stock.hpp"
#include "stlta/stlta.hpp"


sec::stock::stock(std::string sname):
	sec::csv_report<double>("bad url")
	,sec_info(sname)
{
	stock_name = sname;
	sec_info.connect();
	for (int y = 2005; y<2018; y++) {
		for (int m = 1; m<13; m++) {
			sec::archive a(sec_info.getCIK(), "10-K", y, m);
			a.connect();

			a.disconnect();
		}
	}
	//loadASIO();
	//update_OpenClose();
	
	updateTA();
	last_update=*(dates.end()-1);
//	save(sname,"OPEN CLOSE");
}

void sec::stock::updateTA()
{
	TA::SMA(10,adj_closes,SMAs10);
	TA::EMA(13,adj_closes,EMAs13);
	TA::MACD(12,26,9,adj_closes,macds,macd_signals,macd_hists);
	TA::MAX(100,adj_closes,max_closing);
	TA::MAX(100,macd_hists,max_hist);
}

std::string sec::stock::getfilename()
{
	return file_name;
}

int sec::stock::getIndex(boost::gregorian::date d1)
{
	std::vector<boost::gregorian::date>::iterator dit;
	dit = std::find(dates.begin(), dates.end(), d1);
	if (dit == dates.end()) {return 0;} 
	else
	{return std::distance(dates.begin(),dit);}
}

void sec::stock::fillFacts()
{

}

void sec::stock::verify(boost::gregorian::date d1)
{
	std::cout << "DATE\t\tOPEN\tCLOSE\tHIGH\tLOW\tVOLUME\t\tADJ\tSMA10\n";
	int index = getIndex(d1);
	std::cout << boost::gregorian::to_simple_string(dates[index]) << "\t";
	std::cout << opening_prices[index] << "\t";
	std::cout << closing_prices[index] << "\t"; 
	std::cout << highs[index] << "\t";
	std::cout << lows[index] << "\t";
	std::cout << volumes[index] << "\t";
	std::cout << adj_closes[index] << "\t";
	std::cout << SMAs10[index] << "\n";
}

void sec::stock::verify()
{
	using namespace boost::gregorian;
	first_day_of_the_week_before fdbf(Monday);
	date d1=fdbf.get_date(day_clock::local_day());
	verify(d1);
	day_iterator diter(d1,1);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	++diter;
	verify(*diter);
	std::cout << "verify open close vector\nOpen=" << opening_prices.back() << "\nClose=" <<closing_prices.back() <<"\nCIK=" << sec_info.getCIK() << "\n";
}


/*
Heading options should be separated by comma and include:
	DATE
	OPEN
	CLOSE
	HIGH
	LOW
	VOLUME
	ADJ
	SMA10
*/
/*
void sec::stock::save(std::string fname, std::string headings)
{
	bool hasDATE(false);
	bool hasOPEN(false);
	bool hasCLOSE(false);
	bool hasHIGH(false);
	bool hasLOW(false);
	bool hasVOLUME(false);
	bool hasADJ(false);
	bool hasSMA10(false);
	bool hasEMA13(false);
	bool hasMACD(false);
	bool hasMACDSIG(false);
	bool hasMACDHIST(false);
	bool hasMAXCLOSE(false);
	bool hasMAXHIST(false);
	bool hasHISTDIV(false);
	bool hasFUTUREROC(false);                                                                                           
	std::stringstream ss(headings);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	int count = vstrings.size();
	int columns=0;
	std::cout << "vstrings size =" << count << "\n";
	for (int i = 0; i < vstrings.size(); i++)
	{ 
		if (vstrings[i].find("DATE")!=std::string::npos)
			{hasDATE=true;columns=columns+1;};
		if (vstrings[i].find("OPEN") !=std::string::npos)
			{hasOPEN=true;columns=columns+1;};
		if (vstrings[i].find("CLOSE") != std::string::npos)
			{hasCLOSE=true;columns=columns+1;};
		if (vstrings[i].find("HIGH") !=std::string::npos)
			{hasHIGH=true;columns=columns+1;};
		if (vstrings[i].find("LOW") !=std::string::npos)
			{hasLOW=true;columns=columns+1;};
		if (vstrings[i].find("VOLUME") !=std::string::npos)
			{hasVOLUME=true;columns=columns+1;};
		if (vstrings[i].find("ADJ") != std::string::npos)
			{hasADJ=true;columns=columns+1;};
		if (vstrings[i].find("SMA10") !=std::string::npos)
			{hasSMA10=true;columns=columns+1;};
		if (vstrings[i].find("EMA13") !=std::string::npos)
			{hasEMA13=true;columns=columns+1;};
		if (vstrings[i].find("MACD") !=std::string::npos)
			{hasMACD=true;columns=columns+1;};
		if (vstrings[i].find("MACDSIG") !=std::string::npos)
			{hasMACDSIG=true;columns=columns+1;};
		if (vstrings[i].find("MACDHIST") !=std::string::npos)
			{hasMACDHIST=true;columns=columns+1;};
		if (vstrings[i].find("MAXCLOSE") !=std::string::npos)
			{hasMAXCLOSE=true;columns=columns+1;};
		if (vstrings[i].find("MAXHIST") !=std::string::npos)
			{hasMAXHIST=true;columns=columns+1;};
		if (vstrings[i].find("HISTDIV") !=std::string::npos)
			{hasHISTDIV=true;columns=columns+1;};
		if (vstrings[i].find("FUTUREROC") !=std::string::npos)
			{hasFUTUREROC=true;columns=columns+1;};
	}
	std::cout << hasDATE<< "\t" << hasOPEN << "\t" << hasCLOSE << "\t" << hasHIGH<< "\t" << hasLOW<< "\t"<<columns<<"\n"; 
	std::size_t csvfound;
	csvfound=fname.find(".csv");
	if (csvfound==std::string::npos) //fname does not have csv suffix
		{fname.append(".csv"); }
	std::ofstream ofs(fname.c_str());
	if (ofs.is_open()){
		count = dates.size();
		for (int i = 0; i < count; i++)
		{
			int counter=0;
			if (hasDATE)
			{
				counter = counter +1;
				ofs << dates_[i];
				if (counter<columns){ofs << ",";};
			}
			if (hasOPEN)
			{
				counter = counter +1;
				ofs << opening_prices_[i];
				if (counter<columns){ofs <<",";};
			}
			if (hasCLOSE)
			{
				counter = counter +1;
				ofs << closing_prices_[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasHIGH)
			{
				counter = counter +1;
				ofs << highs_[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasLOW)
			{
				counter = counter +1;
				ofs << lows_[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasVOLUME)
			{
				counter = counter +1;
				ofs << volumes_[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasADJ)
			
			{
				counter = counter +1;
				ofs << adj_closes[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasSMA10)
			{
				counter = counter +1;
				ofs << SMAs10[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasEMA13)
			{
				counter = counter +1;
				ofs << EMAs13[i];
				if (counter<columns){ofs << ",";}
			}
			ofs << "\n";
		}
		ofs.close();
	}
}
*/
