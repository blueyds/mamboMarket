#ifndef EMA_H
#define EMA_H

#include <vector> //std::vector
#include <iostream> //std::cout
#include <numeric> //std::accumulate
namespace TA{
template <class T>
class EMA
{
	std::vector<T> window_values;
	int window;
	T K;
	int counter;
	T prior_ema;
public:
	EMA(int win) //window is the size of EMA lookback
	{
		window=win;
		counter=0;
		prior_ema = 0;
		K = 2 / (window+1);
		window_values.reserve(window+1);
	};
	T operator()(T& value)
	{
		window_values.push_back(value);
		counter = counter +1;
		T val = 0;
		if (counter < window) 
		{
			return val;
		}
		else if (counter==window) 
		// the only time the counter should exactly equal the window is the first time it reaches that magic number, for this we will calculate a SMA 
		{	
			for (int i=0; i<counter;i++)
			{
				window_values[i]=window_values[i+1];
			}
			window_values.pop_back();
			T sum_value;
			val = std::accumulate( window_values.begin(), window_values.end(), 0) / window;
			prior_ma=val;
		}
		else if (counter > window)
		{
			T closingK = value * K;
			T priorK = prior_ema * (1-K);
			val = closingK + prior_ema;
			prior_ema = val;
		}
		return val;
	}
};
}
#endif