#include <iostream>
#include "StockDetail.h"
#include "stock.h"

int main (int argc, char *argv[])
{
	if (argc != 4) // we want a more argument
		std::cout << "Usage : "<< argv[0] << " <stock_symbol> <postgres_host> <postgres_db>";
	else
	{
		std::cout << "What is your password for postgres? :>";
		 
		std::cout << "Preparing to pull from internet still in main.cpp\n";
		std::cout << argv[1]<<"\n";
		std::cout << "calling the stock class now\n";
	   	stock s (argv[1]);
		s.verify();
	}
}
