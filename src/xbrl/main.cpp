#include <iostream>
#include "sec.hpp"

int main (int argc, char *argv[])
{

	sec::sec s(argv[1]);
	std::cout << "CIK:/t" << s.CIK;
return 0;
}
