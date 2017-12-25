#ifndef STLTA_HPP
#define STLTA_HPP

/*
    STL_TA
    Copyright (C) {2016}  {Craig Nunemaker}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vector>
#include <algorithm>
#include <numeric>

namespace TA
{
typedef std::vector<double> dvector;
 
namespace functors{
template <typename T>
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
		if (curSize == window) 
		{
			curSize=curSize -1;
			//T new_value;
			T sum_value;
			sum_value = std::accumulate(window_values.begin(),window_values.end(),0);
			val= sum_value / window;
			window_values.erase(window_values.begin());
		}
//		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
	
	
};

template <class T>
class SUBTRACT
{
public:
	SUBTRACT () {;};
	T operator()( T a, T b ) const    
    {    
        return a - b;    
    }  
};

template <typename T>
class ROC 
{
	std::vector<T> window_values;
	int window;
	int curSize;
public:
	ROC(int win) //window is the size of SMA lookback
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
		if (curSize == window) 
		{
			curSize=curSize -1;
			val= value / *(window_values.begin());
			window_values.erase(window_values.begin());
		}
//		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};


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
		if (curSize == window) 
		{
			curSize=curSize -1;
			val= value - *(window_values.begin());
			window_values.erase(window_values.begin());
		}
//		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};
template <typename T>
class MIN 
{
	std::vector<T> window_values;
	int window;
	int curSize;
public:
	MIN(int win) //window is the size of lookback 
	{
		window=win;
		curSize=0;
		window_values.reserve(window+1);
	};
	T operator()(T& value)
	{
		window_values.push_back(value);
		curSize++;
		T val = 0;
		if (curSize == window) 
		{
			curSize--;
			//T new_value;
			val = *(std::min_element( window_values.begin(), window_values.end() ) );
			window_values.erase(window_values.begin());
		}
//		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};

template <typename T>
class MAX 
{
	std::vector<T> window_values;
	int window;
	int curSize;
public:
	MAX(int win) //window is the size of lookback 
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
		if (curSize == window) 
		{
			curSize=curSize -1;
			//T new_value;
			val = *( std::max_element( window_values.begin(), window_values.end()) );
			window_values.erase(window_values.begin());
		}
//		std::cout << "return curSize = " <<curSize << "\t window ="<< window << "\tclosing = "<< value << "\tSMA ="<< val <<"\n";
		return val;
	}
};
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
		if (counter==window)  
		{	
			if (prior_ema==0)
			{
				T sum_value;
				val = std::accumulate( window_values.begin(), window_values.end(), 0) / window;
				prior_ema=val;
				window_values.erase(window_values.begin());
			}
			else
			{
				T closingK = value * K;
				T priorK = prior_ema * (1-K);
				val = closingK + prior_ema;
				prior_ema = val;
			}
		}
		return val;
	}
};

}//namespace TA::functors

// header based definitions
inline void SMA(int window,dvector &input, dvector &output)
{
	functors::SMA<double> _sma(window);
	output.reserve(input.size());
	std::transform(input.begin(), input.end(), output.begin(), _sma);
};

inline void EMA(int window,dvector &input, dvector &output)
{
	functors::EMA<double> _ema(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _ema);
}

inline void SUBTRACT(dvector &input1, dvector &input2, dvector &output)
{//1 - 2
	functors::SUBTRACT<double> _subtract;
	output.reserve(input1.size());
	std::transform(input1.begin(), input1.end(),input2.begin(),output.begin(), _subtract);
}

inline void MIN(int window,dvector &input, dvector &output)
{
	functors::MIN<double> _min(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _min);
}

inline void MAX(int window,dvector &input, dvector &output)
{
	functors::MAX<double> _max(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _max);
}

inline void MOMENTUM(int window,dvector &input,dvector &output)
{
	functors::MOMENTUM<double> _momentum(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _momentum);
}

inline void ROC(int window,dvector &input,dvector &output)
{
	functors::ROC<double> _roc(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _roc);
}


inline void MACD(int short_window, int long_window, int smooth_window, dvector &input, dvector &macd, dvector &macd_signal, dvector &macd_hist)
{
	std::vector<double> short_emas;
	std::vector<double> long_emas;
	short_emas.reserve(input.size());
	long_emas.reserve(input.size());
	macd.reserve(input.size());
	macd_signal.reserve(input.size());
	macd_hist.reserve(input.size());
	EMA(short_window,input,short_emas);
	EMA(long_window,input,long_emas);
	SUBTRACT(short_emas,long_emas,macd);
	EMA(smooth_window,macd,macd_signal);
	SUBTRACT(macd,macd_signal,macd_hist);
}

}//namespace TA


#endif
