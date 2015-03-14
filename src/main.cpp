#include <iostream>
#include "stock.h"

int main (int argc, char *argv[])
{
	if (argc != 2) // we want a second argument
		std::cout << "USage : "<< argv[0] << " <file_name>";
	else
	{
		std::cout << "Preparing to pull from internet still in main.cpp\n";
		std::cout << argv[1]<<"\n";
		std::cout << "calling the stock class now\n";
	   	stock s (argv[1]);
		
	}
}
