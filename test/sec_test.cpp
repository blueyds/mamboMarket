//add source header includes here
#include <string>
#include <iostream>
#include "error.hpp"
#include "sec/sec_report.hpp"
#include "sec/10Q.hpp"

int main()
{
	sec::info s("AAPL");
	MSG("CIK",s.getCIK());
	MSG("SIC",s.getSIC());
	MSG("NAME",s.getName());
	MSG("STATE",s.getState());
	MSG("SYMBOL",s.getSymbol());
	MSG("YEAR END",s.getYearEnd());
	MY_ASSERT(s.getCIK()=="0000320193");
	MY_ASSERT(s.getSIC()=="3571");
	MY_ASSERT(s.getName()=="APPLE INC");
	MY_ASSERT(s.getState()=="CA");
	MY_ASSERT(s.getSymbol()=="AAPL");
	MY_ASSERT(s.getYearEnd()=="0930");
	sec::archive a(s.getCIK(),"10-Q",2017,8);
	MSG("form",a.getForm());
	MSG("lang:",a.lang_);
	MY_ASSERT(a.items_[0].CIK_ == "0000320193");
	sec::ten_q s10(a.items_[0].url_);
	
	
}