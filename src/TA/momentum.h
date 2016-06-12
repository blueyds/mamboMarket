#ifndef MOMENTUM_H
#define MOMENTUM_H
#include <vector> //std::vector
#include <numeric> //std::accumulate


namespace TA{
namespace functors{
template <typename T>
class MOMENTUM 
{
	std::vector<T> window_values;
	int window;
	int curSize;
public:
	MOMENTUM(int win) //window is the size of SMA lookback
	{
		window=win;
		curSize=0;
		window_values.reserve(window+1);
	};
	T operator()(T& value)
	{
		window_values.push_back(value);
		curSize = curSize +1;
		T val = 0;
		if (curSize > window) 
		{
			curSize=curSize -1;
			val= value - window_values.begin();
			window_values.erase(window_values.begin());
		}
//		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};
}//namespace TA::functors
}//namespace TA
#endif
