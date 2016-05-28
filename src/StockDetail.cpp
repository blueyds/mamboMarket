#include <iostream>
#include "StockDetail.h"

StockDetail::StockDetail() //Constructor
{
	open=0.0;
	close=0.0;
	high=0.0;
	low=0.0;
	volume=0.0;
	adj=0.0;
	13EMAclose_D=0.0;
}

StockDetail::StockDetail(const StockDetail &copyin) //Copy constructor to handle pass by value
{
	open = copyin.open;
	close = copyin.close;
	high = copyin.high;
	low = copyin.low;
	volume = copyin.volume;
	adj = copyin.adj;
	13EMAclose_D=copyin.13EMAclose_D;
}

std::ostream &operator<<(std::ostream &output, const StockDetail &sd)
{
	output << sd.open << "\t" \
		   << sd.close <<"\t" \
		   <<sd.high <<"\t" \
		   <<sd.low << "\t" \
		   << sd.volume <<"\t"\
		   << sd.adj << "\t" \
		<< sd.13EMAclose_D <<"\n";
	return output;
}

StockDetail& StockDetail::operator=(const StockDetail &rhs)
{
	this->open = rhs.open;
	this->close = rhs.close;
	this->high = rhs.high;
	this->low = rhs.low;
	this->volume=rhs.volume;
	this->adj=rhs.adj;
	this->13EMAclose_D=rhs.13EMAclose_D;
}
