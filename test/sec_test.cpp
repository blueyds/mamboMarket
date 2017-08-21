//add source header includes here
#include <string>
#include <iostream>
#include "error.hpp"
#include "sec/sec_report.hpp"

int main()
{
	sec::info s("AAPL");
	MY_TEST_MESSAGE("CIK:     "+s.getCIK());
	MY_TEST_MESSAGE("SIC:     "+s.getSIC());
	MY_TEST_MESSAGE("NAME:    "+s.getName());
	MY_TEST_MESSAGE("STATE:   "+s.getState());
	MY_TEST_MESSAGE("SYMBOL:  "+s.getSymbol());
	MY_TEST_MESSAGE("YEAR END:"+s.getYearEnd());
	MY_ASSERT(s.getCIK()=="0000320193");
	MY_ASSERT(s.getSIC()=="3571");
	MY_ASSERT(s.getName()=="APPLE INC");
	MY_ASSERT(s.getState()=="CA");
	MY_ASSERT(s.getSymbol()=="AAPL");
	MY_ASSERT(s.getYearEnd()=="0930");
	sec::archive a(s.getCIK(),"10-Q",2017,8);
	MY_TEST_MESSAGE("lang:      "+a.lang_);
	MY_ASSERT(a.lang_=="en-us");
}