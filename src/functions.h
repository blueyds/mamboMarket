#include <vector> //std::vector
#include <numeric> //std::accumulate
template <class T>
class SMA 
{
	std::vector<T> window_values;
	int window;
	int curSize =0;
public:
	SMA(int win)
	{
		window=win;
		window_values.reserve(window+1);
	};
	T operator()(T value)
	{
		window_values.push_back(value);
		curSize = curSize++;
		T val = 0;
		if (window_values.size() > window) 
		{
			for (int i=0; i<curSize;i++)
			{
				window_values[i]=window_values[i+1];
			}
			window_values.pop_back();
			curSize=curSize--;
			T new_value;
			T sum_value;
			sum_value = std::accumulate(window_values.begin(),window_values.end(),0);
			val= sum_value / window;
		}
		return val;
	}
};