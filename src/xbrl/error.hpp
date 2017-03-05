#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>
using std::exception;
struct basic_error: public exception {
		std::string message_;
		basic_error(std::string message):message_(message){};
		const char * what () const throw() {
			return message_.data();} };
			

struct connection_error: public exception {
		std::string message_;
		connection_error(std::string message):message_(message){};
		const char * what () const throw() {
			std::string temp("Unable to connect: ");
			temp += message_;
			return temp.data();} };

struct status_error: public exception {
	unsigned int code_;
	std::string message_;
	status_error(unsigned int code, std::string message):code_(code),message_(message){};
	const char * what () const throw() {
		std::string temp("Invalid status code: ");
		temp += code_;
		temp += "\n";
		temp += message_;
		return temp.data();} };
		
		
#endif
