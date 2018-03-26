#include "stlta/stlta.hpp"

void TA::SMA(int window, TA::dvector &input, TA::dvector &output)
{
	TA::functors::SMA<double> _sma(window);
	output.resize(input.size(),0.0);
	std::transform(input.begin(), input.end(), output.begin(), _sma);
};

void TA::EMA(int window, TA::dvector &input, TA::dvector &output)
{
	TA::functors::EMA<double> _ema(window);
	output.resize(input.size(),0.0);
	std::transform(input.begin(), input.end(), output.begin(), _ema);
}

void TA::SUBTRACT(TA::dvector &input1, TA::dvector &input2, TA::dvector &output)
{//1 - 2
	TA::functors::SUBTRACT<double> _subtract;
	output.resize(input1.size(),0.0);
	std::transform(input1.begin(), input1.end(), input2.begin(), output.begin(), _subtract);
}

void TA::MIN(int window, TA::dvector &input, TA::dvector &output)
{
	TA::functors::MIN<double> _min(window);
	output.resize(input.size(),0.0);
	std::transform(input.begin(), input.end(), output.begin(), _min);
}

void TA::MAX(int window, TA::dvector &input, TA::dvector &output)
{
	TA::functors::MAX<double> _max(window);
	output.resize(input.size(),0.0);
	std::transform(input.begin(), input.end(), output.begin(), _max);
}

void TA::MOMENTUM(int window, TA::dvector &input, TA::dvector &output)
{
	TA::functors::MOMENTUM<double> _momentum(window);
	output.resize(input.size(),0.0);
	std::transform(input.begin(), input.end(), output.begin(), _momentum);
}

void TA::ROC(int window, TA::dvector &input, TA::dvector &output)
{
	TA::functors::ROC<double> _roc(window);
	output.resize(input.size(),0.0);
	std::transform(input.begin(), input.end(), output.begin(), _roc);
}


void TA::MACD(int short_window, int long_window, int smooth_window, TA::dvector &input, TA::dvector &macd, TA::dvector &macd_signal, TA::dvector &macd_hist)
{
	std::vector<double> short_emas;
	std::vector<double> long_emas;
	short_emas.resize(input.size(),0.0);
	long_emas.resize(input.size(),0.0);
	macd.resize(input.size(),0.0);
	macd_signal.resize(input.size(),0.0);
	macd_hist.resize(input.size(),0.0);
	TA::EMA(short_window, input, short_emas);
	TA::EMA(long_window, input, long_emas);
	TA::SUBTRACT(short_emas, long_emas, macd);
	TA::EMA(smooth_window, macd, macd_signal);
	TA::SUBTRACT(macd, macd_signal, macd_hist);
}
