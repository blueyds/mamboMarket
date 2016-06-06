#include <iostream>
#include <sstream>
#include <string>
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
	for (int i = 0; i < vstrings.size(); i++)
	{ 
		if (vstrings[i].compare("DATE"))
			{hasDATE=true;columns=columns+1;};
		if (vstrings[i].compare("OPEN"))
			{hasOPEN=true;columns=columns+1;};
		if (vstrings[i].compare("CLOSE"))
			{hasCLOSE=true;columns=columns+1;};
		if (vstrings[i].compare("HIGH"))
			{hasHIGH=true;columns=columns+1;};
		if (vstrings[i].compare("LOW"))
			{hasLOW=true;columns=columns+1;};
		if (vstrings[i].compare("VOLUME"))
			{hasVOLUME=true;columns=columns+1;};
		if (vstrings[i].compare("ADJ"))
			{hasADJ=true;columns=columns+1;};
		if (vstrings[i].compare("SMA10"))
			{hasSMA10=true;columns=columns+1;};
	}
	std::size_t csvfound;
	csvfound=fname.find(".csv");
	if (csvfound==std::string::npos) //fname does not have csv suffix
		{fname << ".csv"; }
	std::ofstream ofs (fname, std::ofstream::out);
	count = dates.size();
	for (int i = 0; i < count; i++)
	{
		std::string temp;
		int counter=0;
		if (hasDATE)
		{
			counter = counter +1;
			temp.append(std::to_string(dates[i]));
			if (counter<columns){temp.append(",");}
		}
		/*if (hasOPEN)
		{
			counter = counter +1;
			temp.append(std::to_string(opening_prices[i]));
			if (counter<columns){temp.append(",");}
		}
		if (hasCLOSE)
		{
			counter = counter +1;
			temp.append(std::to_string(closing_prices[i]));
			if (counter<columns){temp.append(",");}
		}
		if (hasHIGH)
		{
			counter = counter +1;
			temp.append(std::to_string(highs[i]));
			if (counter<columns){temp.append(",");}
		}
		if (hasLOW)
		{
			counter = counter +1;
			temp.append(std::string(lows[i]));
			if (counter<columns){temp.append(",");}
		}
		if (hasVOLUME)
		{
			counter = counter +1;
			temp.append(std::to_string(volumns[i]));
			if (counter<columns){temp.append(",");}
		}
		if (hasADJ)
		{
			counter = counter +1;
			temp.append(std::to_string(adj_closes[i]));
			if (counter<columns){temp.append(",");}
		}
		if (hasSMA10)
		{
			counter = counter +1;
			temp.append(std::to_string(SMAs10[i]));
			if (counter<columns){temp.append(",");}
		}*/
		temp.append("\n");
		ofs << temp;
	}
	ofs.close();
}