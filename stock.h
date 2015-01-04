#pragma once
#include <boost/serialization/map.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <vector>
#include <string>
#include <map>
#include "StockDetail.h"


class stock {
private:
	friend class boost::serialization::access;

	
	std::string file_name;
	std::string stock_name;
	std::string long_name;
	std::string description;
	//boost::gregorian::date current_day; //most recent day information was updated for
	//boost::gregorian::date oldest_day; //oldest day information was updated for
	typedef std::map<boost::gregorian::date,StockDetail> price_list;
	typedef price_list::iterator price_iter;
	typedef std::pair<boost::gregorian::date,StockDetail> price_pair;
	price_list prices;
	//index will work as such
	// dopen[0] is most recent closed period day or week
	//dopen[1] is current - 1 days
//	std::vector<double> dopen; 
//	std::vector<double> dclose;
//	std::vector<double> dhigh;
//	std::vector<double> dlow;
//	std::vector<double> dvolume;
	std::vector<double> opens;
	std::vector<double> closes;
	std::vector<double> highs;
	std::vector<double> lows;
	std::vector<double> volumes;

	

	template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & file_name;
        ar & stock_name;
        ar & long_name;
		ar & description;
	//	ar & current_day;
	//	ar & oldest_day;
		ar & prices;
//		ar & dopen;
//		ar & dclose;
//		ar & dhigh;
//		ar & dlow;
//		ar & dvolume;
    }


public:
	stock(std::string sname);
	stock(std::string sname,std::string name,std::string descr);
	int GetStockIndex(boost::gregorian::date d1, StockDetail &st);
	std::string getfilename(void);
	void update(boost::gregorian::date day, 
				double open, 
				double close, 
				double high,
				double low,
				double volume);
	
	void verify();

};
