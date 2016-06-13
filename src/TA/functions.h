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
typedef std::vector<double> dvector;
void SMA(int window,dvector &input, dvector &output);
void EMA(int window,dvector &input, dvector &output);
void SUBTRACT(dvector &input1, dvector &input2, dvector &output);
void MACD(int short_window, int long_window, int smooth_window, dvector &input, dvector &macd, dvector &macd_signal, dvector &macd_hist);
void MIN(int window, dvector &input, dvector &output);
void MAX(int window,dvector &input, dvector &output);
void MOMENTUM(int window,dvector &input,dvector &output);
void ROC(int window,dvector &input,dvector &output);
void TEST();
}//namespace TA

#endif
