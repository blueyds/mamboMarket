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
#pragma once
#include <string>
#include <vector>
#include "stock.h"


class quotes {
private:
	std::string file_name;
	struct infoS {
		std::string sym_name;
		std::string name;
		std::string description;
	};
	typedef struct infoS info;
	std::vector<info> symbols;
	std::string conString;
	struct ql{
		std::string symbol; 	//s
		std::string date; 	//d2
		std::string opening;	//o
		std::string close;	//l1
		std::string low;		//g
		std::string high;	//h
		std::string volume;	//a2
	};
	typedef struct ql quote_line;
	std::vector<quote_line> quote;
	void load(stock* st); //loads a quotes file created by yahoo.exe
public:
	void update(int periods);//periods from current to go back on data. today = 0
};
