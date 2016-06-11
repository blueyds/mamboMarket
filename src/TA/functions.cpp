#include <vector>
#include <algorithm>
#include "functions.h"

void TA::SMA(int window,std::vector<double> &input, std::vector<double> &output)
{
	TA::functors::SMA<double> _sma(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _sma);
}
