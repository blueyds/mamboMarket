#include <list> //std::list
#include <numeric> //std::accumulate
template <class T>
class SMA 
{
	std::list<T> window_values;
	int window;
public:
	SMA(int win)
	{
		window=win;
		window_values.reserve(window+1);
	};
	T operator()(T value)
	{
		window_values.push_back(value);
		T val = 0;
		if (window_values.size() > window) 
		{
			window_values.pop_front();
			T new_value;
			T sum_value;
			sum_value = std::accumulate(window_values.begin(),window_values.end(),0);
			val= sum_value / window;
		}
		return val;
	}
};