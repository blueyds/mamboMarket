//add source header includes here
#define TESTING
#include <string>
#include "error.hpp"
#include "sec/sec_report.hpp"

int main()
{
	sec::info s("AAPL");
	std::string cik;
	std::string sic;
	cik=s.getCIK();
	sic=s.getSIC();
	
}