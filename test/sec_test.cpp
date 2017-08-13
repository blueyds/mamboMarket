//add source header includes here
#include <string>
#include "sec/sec_report.hpp"

#define BOOST_TEST_MODULE XMLtest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(xml_test)
{
	boost::unit_test::unit_test_log.set_stream( std::cout );
	sec::info s("AAPL");
	std::string cik;
	std::string sic;
	cik=s.getCIK();
	sic=s.getSIC();
	BOOST_CHECK(sic=="3571");
	BOOST_CHECK(cik=="0000320193");
}