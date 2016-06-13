#include <vector>
#include <algorithm>
#include <iostream>
#include "functions.h"

void TA::SMA(int window,TA::dvector &input, TA::dvector &output)
{
	TA::functors::SMA<double> _sma(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _sma);
}

void TA::EMA(int window,TA::dvector &input, TA::dvector &output)
{
	TA::functors::EMA<double> _ema(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _ema);
}

void TA::SUBTRACT(TA::dvector &input1, TA::devector &input2, TA::dvector &output)
{//1 - 2
	TA::functors::SUBTRACT<double> _subtract;
	output.reserve(input1.size());
	std::transform(input1.begin(), input1.end(),input2.begin(),output.begin(), _subtract);
}

void MIN(int window,TA::dvector &input, TA::dvector &output)
{
	TA::functors::MIN<double> _min(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _min);
}

void MAX(int window,TA::dvector &input, TA::dvector &output)
{
	TA::functors::MAX<double> _max(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _max);
}

void MOMENTUM(int window,TA::dvector &input,TA::dvector &output)
{
	TA::functors::MOMENTUM<double> _momentum(window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _momentum);
}

void ROC(int window,TA::dvector &input,TA::dvector &output)
{
	TA::functors::EMA<double> (window);
	output.reserve(input.size());
	std::transform( input.begin(), input.end(), output.begin(), _roc);
}


void TA::MACD(int short_window, int long_window, int smooth_win, TA::dvecctor &input, TA::dvector &macd, TA::dvector &macd_signal, TA::dvector &macd_hist)
{
	std::vector<double> short_emas;
	std::vector<double> long_emas;
	short_emas.reserve(input.size());
	long_emas.reserve(input.size());
	macd.reserve(input.size());
	macd_signal.reserve(input.size());
	macd_hist.reserve(input.size());
	TA::EMA(short_window,input,short_emas);
	TA::EMA(long_window,input,long_emas);
	TA::SUBTRACT(short_emas,long_emas,macd);
	TA::EMA(smooth_window,fast_macd,macd_signal);
	TA::SUBTRACT(macd,macd_signal,macd_hist);
}

void TA::TEST()
{
	std::vector<double> test= {10.0,15.0,13.0,9.0,16.0,14,0,11.0,10.0,13.0,18.0,20.0};
	std::vector<double> out_test;
	std::cout << "test vector \t";
	for (auto i: test)
  		std::cout << i << "\t";
  	std::cout<< "\n";
	TA::SMA(5,test,out_test);
	std::cout << "sma test\t";
	for (auto i: out_test)
  		std::cout << i << "\t";
  	std::cout<< "\n";
}