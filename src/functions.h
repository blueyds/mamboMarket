#include <vector> //std::vector
#include <iostream> //std::cout
#include <numeric> //std::accumulate
template <class T>
class SMA 
{
	std::vector<T> window_values;
	int window;
	int curSize;
public:
	SMA(int win)
	{
		window=win;
		curSize=0;
		window_values.reserve(window+1);
	};
	T operator()(T value)
	{
		window_values.push_back(value);
		curSize = curSize +1;
		T val = 0;
		if (curSize > window) 
		{
			for (int i=0; i<curSize;i++)
			{
				window_values[i]=window_values[i+1];
			}
			window_values.pop_back();
			curSize=curSize -1;
			T new_value;
			T sum_value;
			sum_value = std::accumulate(window_values.begin(),window_values.end(),0);
			val= sum_value / window;
		}
		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};