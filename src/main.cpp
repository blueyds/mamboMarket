#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "error.hpp"
#include "sec/sec_report.hpp"
#include "csv/csv_report.hpp"
#include "sec/10Q.hpp"
#include "stock.hpp"
#include "date/date.h"

std::string pick_random_symbol()
{
	std::vector < std::string > v = {"MSFT","AAPL","FB","AMZN","GOOG" };
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<int> dist(0, v.size() - 1);
	std::string random_element = v[dist(engine)];
	//return random_element;
	return "AAPL";
}

void test()
{
	sec::info s(pick_random_symbol());
	MSG("CIK", s.getCIK());
	MSG("SIC", s.getSIC());
	MSG("NAME", s.getName());
	MSG("STATE", s.getState());
	MSG("SYMBOL", s.getSymbol());
	MSG("YEAR END", s.getYearEnd());
	//s.printUrls();
	std::vector<sec::report_item_t>::const_iterator it1;
	for (it1 = s.report_begin(); it1 != s.report_end(); ++it1)
	{
		if (it1->form_ == "10-Q")
		{
			sec::ten_q s10(it1->url_);
			MSG(it1->url_);
			MSG("Current Assets", s10.getCurrentAssets());
			
		}
	}
	/*sec::ten_q s10(a.items_[0].url_);
	MSG("just finsished the 10q");
	//sec::stock st("AAPL",'d'); segmentation fault needs fixed
	//st.verify();*/
}


int main (int argc, char *argv[])
{
	if (argc != 2) // we want a more argument
		test();
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
	sec::stock st(argv[1],'d');
	st.verify();
	
	}
	MSG("press any button");
	std::cin.ignore();
}
