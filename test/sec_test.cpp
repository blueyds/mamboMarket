//add source header includes here
#include <string>
#include <iostream>
#include "error.hpp"
#include "sec/sec_report.hpp"

int main()
{
	sec::info s("AAPL");
	std::string cik;
	std::string sic;
	MY_TEST_MESSAGE("CIK: "+s.getCIK());
	MY_TEST_MESSAGE("SIC: "+s.getSIC());
	if(s.getCIK()!="0000320193")
	{return 1;};
	if(s.getSIC()!="3571"){return 2;};
	
}