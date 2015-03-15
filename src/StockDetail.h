

#ifndef STOCK_DETAIL_H
#define STOCK_DETAIL_H
#include <iostream>

class StockDetail
{
	friend std::ostream &operator<<(std::ostream &, const StockDetail &);

public:
	double open;
	double close;
	double high;
	double low;
	double volume;
	double adj;
	StockDetail ();
	StockDetail (const StockDetail &);
	~StockDetail(){};
	StockDetail &operator=(const StockDetail &rhs);
};

#endif
