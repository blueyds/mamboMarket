#ifndef ERROR_H
#define ERROR_H
#define TESTING
#include <exception>
#include <string>

#ifdef TESTING
#include <iostream>
inline void MY_TEST_MESSAGE(std::string msg)
{
	std::cout << msg <<"\n";
};
#else
inline void MY_TEST_MESSAGE(std::string msg)
{
};
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
};

#endif
