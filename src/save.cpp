#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "stock.h"


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
void stock::save(std::string fname, std::string headings)
{
	bool hasDATE(false);
	bool hasOPEN(false);
	bool hasCLOSE(false);
	bool hasHIGH(false);
	bool hasLOW(false);
	bool hasVOLUME(false);
	bool hasADJ(false);
	bool hasSMA10(false);
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
				ofs << dates[i];
				if (counter<columns){ofs << ",";};
			}
			if (hasOPEN)
			{
				counter = counter +1;
				ofs << opening_prices[i];
				if (counter<columns){ofs <<",";};
			}
			if (hasCLOSE)
			{
				counter = counter +1;
				ofs << closing_prices[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasHIGH)
			{
				counter = counter +1;
				ofs << highs[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasLOW)
			{
				counter = counter +1;
				ofs << lows[i];
				if (counter<columns){ofs << ",";}
			}
			if (hasVOLUME)
			{
				counter = counter +1;
				ofs << volumes[i];
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
			ofs << "\n";
		}
		ofs.close();
	}
}