#include <vector>
#include <algorithm>
#include "TA/functions.h"

void SMA(int window,std::vector<double> &input, std::vector::<double> &output)
{
	TA::functors::SMA<double> _sma(window);
	output.reserve(adj_closes.size());
	std::transform( input.begin(), input.end(), .begin(), _sma);
}