//add source header includes here
#include <string>
#include <iostream>
#include "error.hpp"
#include "sec/sec_report.hpp"

int main()
{
	std::cout << "what\n";
	MY_TEST_MESSAGE("begiinnign or craig nunemaker");
	sec::info s("AAPL");
	std::string cik;
	std::string sic;
	cik=s.getCIK();
	sic=s.getSIC();
	
}