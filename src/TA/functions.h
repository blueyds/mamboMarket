#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include "sma.h"
#include "ema.h"
#include "subtract.h"
#include "max.h"
#include "min.h"
#include "momentum.h"
#include "roc.h"

namespace TA
{

void SMA(int window,std::vector<double> &input, &output);
void EMA(int window,std::vector<double> &input, &output);
void SUBTRACT(std::vector<double> &input1, &input2, &output);
void MACD(int short_window, long_window, smooth_window, std::vector<double> &input, &macd, &macd_signal, &macd_hist);
void MIN(int window,std::vector<double> &input, &output);
void MAX(int window,std::vector<double> &input, &output);
void MOMENTUM(int window,std::vector<double> &input, &output);
void ROC(int window,std::vector<double> &input, &output);
void TEST(
}//namespace TA

#endif
