#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>
#ifdef TESTING
#include <boost/test/included/unit_test.hpp>
#define MY_TEST_MESSAGE(msg) BOOST_TEST_MESSAGE(msg)
#else
#define MY_TEST_MESSAGE(msg)  //
#endif

struct basic_error: public std::exception 
{
	std::string message_;
	basic_error(std::string message):message_(message){};
	basic_error(std::string message, std::string code):message_(message+"; "+code){};
	const char * what () const throw()
	{
		return message_.data();
	}
}

#endif
