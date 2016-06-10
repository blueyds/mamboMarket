#ifndef SMA_H
#define SMA_H
#include <vector> //std::vector
#include <numeric> //std::accumulate
/* example usage adj_closes is a vector of double closing prices
	SMA<double> sma10(10);
	SMAs10.reserve(adj_closes.size());
	std::transform( adj_closes.begin(), adj_closes.end(), SMAs10.begin(), sma10);
*/
namespace TA{
namespace functors{
template <class T>
class SMA 
{
	std::vector<T> window_values;
	int window;
	int curSize;
public:
	SMA(int win) //window is the size of SMA lookback
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
			for (int i=0; i<curSize;i++)
			{
				window_values[i]=window_values[i+1];
			}
			window_values.pop_back();
			curSize=curSize -1;
			//T new_value;
			T sum_value;
			sum_value = std::accumulate(window_values.begin(),window_values.end(),0);
			val= sum_value / window;
		}
		//std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};
}//namespace TA::functors
template<typename A>
void SMA(int window,const std::vector<A> &input,std::vector<A> output)
{
	typename std::vector<A>::const_iterator begIt;
	typename std::vector<A>::const_iterator endIt;
	typename std::vector<A>::iterator destIt;
	begIt=input.begin();
	endIt=input.end();
	destIt=output.begin();
	functors::SMA<A> _sma(window);
	output.reserve(input.size());
	std::transform(begIt,endIt,destIt,_sma);
} 
}//namespace TA
#endif
