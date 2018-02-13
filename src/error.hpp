#ifndef ERROR_H
#define ERROR_H
//uncomment following line if we go into production it will disable assert macros
//#define NDEBUG
#include <cassert>
#include <exception>
#include <string>
#include <iostream>

inline void MSG(std::string msg)
{
	std::cout << msg <<"\n";
};
inline void MSG(std::string msg,std::string msg2)
{
	std::cout << msg <<":\t"<<msg2<<"\n";
};
inline void MSG(std::string msg,int i)
{
	std::cout << msg <<":\t"<<std::to_string(i)<<"\n";
};
inline void MY_ASSERT(int expression)
{assert(expression);};
/*
inline void MY_TEST_MESSAGE(std::string msg)
{
};
*/
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
