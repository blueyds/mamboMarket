#include <list> //std::list
#include <numeric> //std::accumulate
template <class T>
class SMA 
{
	std::list<T> window_values;
public:
	std::vector<T> sma_vector;
	void operator()(int window, T value)
	{
		window_values.push_back(value);
		T val = 0;
		if window_values.size() > win 
		{
			window_values.pop_front();
			T new_value;
			T sum_value;
			sum_value = std::accumulate(window_values.begin(),window_values.end(),0);
			val= sum_value / window;
		}
		sma_vector.push_back(val);
	}
};