//add source header includes here
#include <string>
#include <iostream>
#include "sec/sec_report.hpp"

#define BOOST_TEST_MODULE XMLtest
#include <boost/test/included/unit_test.hpp>
#define TESTING
using namespace boost::unit_test;
BOOST_AUTO_TEST_CASE(xml_test)
{
	unit_test_log.set_threshold_level(log_messages);
	sec::info s("AAPL");
	std::string cik;
	std::string sic;
	cik=s.getCIK();
	sic=s.getSIC();
	BOOST_CHECK_MESSAGE(sic=="3571",sic);
	BOOST_CHECK_MESSAGE(cik=="0000320193",cik);
	BOOST_TEST_MESSAGE("CIK: "<<cik);
	BOOST_TEST_MESSAGE("SIC: "<<sic);
}