#include <fstream>
#include <iostream>
#include <ctype.h>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "stocks.h"
#include "stock.h"
#include "csv.h"


stocks::stocks(void)
{
}

stocks::~stocks(void)
{
}

void stocks::regenerate()
{
	using namespace std;
	cout << "Opening nyse.csv" << endl;
	ifstream is("nyse.csv");
	//ifstream is2("nasdaq.csv");
	cout << "Generating individual stock files from csv file" << endl;
	while (true)
    {
		typedef vector<string> rec_t;
	
        rec_t rec = CsvGetLine(is,true,44,10,34);

        if (rec.size() == 0) break;

        rec_t::iterator x = rec.begin();
		string name(*x);
		x++;
		string sym_name(*x);
		x++;
		x++;
		string description(*x);

		bool alpha=true;	//we need to test for any non alphabetic characters file 
		{					//name screws up so we will ignore these odd symbols
			int i=0;
			//char *str=sym_name.c_str();
			while (sym_name[i])
			{
				if (!isalpha(sym_name[i]))
				{
					if (alpha) alpha=false;
				}
				i++;
			}
		}
		if (alpha)
		{
			s1.push_back(sym_name);
			stock st(sym_name,name,description);
			
			std::ofstream ofs(st.getfilename().c_str(),ios::out|ios::trunc);

			// save data to archive
		
			boost::archive::text_oarchive oa(ofs);
			// write class instance to archive
			oa << st;
    		// archive and stream closed when destructors are called
			cout<<sym_name<< "\t";;
		}
	}

};
