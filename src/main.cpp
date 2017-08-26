#include <iostream>
//#include <mlpack/core.hpp>
#include "sec/sec_report.hpp"
#include "error.hpp"

int main (int argc, char *argv[])
{
	if (argc != 2) // we want a more argument
		std::cout << "Usage : "<< argv[0] << " <stock_symbol>\n";
	else
	{
	sec::info s(argv[1]);
	MSG("CIK",s.getCIK());
	MSG("SIC",s.getSIC());
	MSG("NAME",s.getName());
	MSG("STATE",s.getState());
	MSG("SYMBOL",s.getSymbol());
	MSG("YEAR END",s.getYearEnd());
	sec::archive a(s.getCIK(),"10-Q",2017,8);
	MSG("form",a.getForm());
	MSG("lang:",a.lang_);
	}
}
