#include <iostream>
#include <string>
#include "error.hpp"
#include "sec/sec_report.hpp"
#include "csv/csv_report.hpp"
#include "sec/10Q.hpp"
#include "stock.hpp"
#include "date/date.h"

void test()
{
	date d1("2017-01-20");
	
	sec::info s("AAPL");
	MSG("CIK", s.getCIK());
	MSG("SIC", s.getSIC());
	MSG("NAME", s.getName());
	MSG("STATE", s.getState());
	MSG("SYMBOL", s.getSymbol());
	MSG("YEAR END", s.getYearEnd());
	MY_ASSERT(s.getCIK() == "0000320193");
	MY_ASSERT(s.getSIC() == "3571");
	MY_ASSERT(s.getName() == "APPLE INC");
	MY_ASSERT(s.getState() == "CA");
	MY_ASSERT(s.getSymbol() == "AAPL");
	MY_ASSERT(s.getYearEnd() == "0930");
	sec::archive a(s.getCIK(), "10-Q", 2017, 8);
	MSG("form", a.getForm());
	MSG("lang:", a.lang_);
	MY_ASSERT(a.items_[0].CIK_ == "0000320193");
	MSG("10q Url:", a.items_[0].url_);
	sec::ten_q s10(a.items_[0].url_);
	MSG("
	sec::stock st("AAPL",'d');
	st.verify();
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
}
