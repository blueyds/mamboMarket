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
