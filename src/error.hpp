#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>

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
