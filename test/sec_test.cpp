//add source header includes here
#include <string>
#include "sec/sec_report.hpp"

#define BOOST_TEST_MODULE XMLtest
#include <boost/test/included/unit_test.hpp>
using namespace boost::unit_test;
BOOST_AUTO_TEST_CASE(xml_test)
{
	unit_test_log.set_threshold_level(log_messages);
	sec::info s("AAPL");
	std::string cik;
	std::string sic;
	cik=s.getCIK();
	sic=s.getSIC();
	BOOST_CHECK(sic=="3571");
	BOOST_CHECK(cik=="0000320193");
	BOOST_TEST_MESSAGE("CIK: "<<cik);
	BOOST_TEST_MESSAGE("SIC: "<<sic);
}