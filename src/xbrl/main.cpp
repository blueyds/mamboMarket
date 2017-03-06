#include <iostream>
#include "sec.hpp"

int main (int argc, char *argv[])
{

	sec::sec s(argv[1]);
	s.connect();
	std::cout << "CIK:\t" << s.CIK <<"\n";
return 0;
}
