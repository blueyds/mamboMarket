#include "date.h"

///////////////////////////// construction //////////

date::date(const int& d, const int& m, const int& y) 
{
   day_   = d; 
   month_ = m; 
   year_  = y;  // this assumes year is given fully, not Y2K corrections
};

date::date(const std::string dt, Format fmt)
{
	int year_length;
	int year_pos;
	int month_pos;
	int date_pos;
	char sep;
	if(dt.find("-")!=std::string::npos){sep='-';}
	else if(dt.find("/")!=std::string::npos){sep='/';}
	else (sep='';};
	bool error = false;
	do {
	error=false;
	switch fmt {
	case YYYYMMDD:
		month_pos=dt.find(sep)+1;
		if(month_pos==std::string::npos){month_pos=4;};
		date_pos=dt.find(sep,month_pos);
		if(date_pos==std::string::npos){date_pos=6;};
		year_length=4;
		year_pos=0;
		try{
		year_=std::stoi(dt.substr(year_pos,year_length));
		month_=std::stoi(dt.substr(month_pos,2));
		date_=std::stoi(dt.substr(date_pos,2);
		}catch (const std::exception& e)
			{error=true;
			fmt=fmt+1;
			std::cerr << "ERROR = "<<e.what()<<"\n";};
		break;
	case MMDDYYYY:
		break;	
	};
	}while (error);
};

///////////////////////////// inline definitions //////////

date::date(){ year_ = 0; month_ = 0; day_ = 0;};

int date::day()   const { return day_;   };
int date::month() const { return month_; };
int date::year()  const { return year_;  };

void date::set_day  (const int& day)     { date::day_   = day;   };
void date::set_month(const int& month)   { date::month_ = month; };
void date::set_year (const int& year)    { date::year_  = year;  };

bool date::valid() const {
// This function will check the given date is valid or not.
//  If the date is not valid then it will return the value false.
//   Need some more checks on the year, though
    if (year_ <0)                return false;
    if (month_>12 || month_<1)   return false;
    if (day_>31 || day_<1)       return false;
    if ((day_==31 && 
	 ( month_==2 || month_==4 || month_==6 || month_==9 || month_==11) ) )
	return false;
    if ( day_==30 && month_==2) return false;
    if ( year_<2000){
	if ((day_==29 && month_==2) && !((year_-1900)%4==0)) return false;
    };
    if ( year_>2000){
	if ((day_==29 && month_==2) && !((year_-2000)%4==0)) return false;
    };
    return true;
};

bool operator == (const date& d1,const date& d2)
{ // check for equality
	if (!d1.valid()) { return false; }; 
	if (!d2.valid()) { return false; }; 
	if( (d1.day()==d2.day())&& (d1.month()==d2.month()) && (d1.year()==d2.year())) { return true;};
	return false; 
};

bool operator !=(const date& d1, const date& d2)
{ 
	return !(d1==d2);
};

bool operator < (const date& d1, const date& d2)
{
	if (!d1.valid()) { return false; }; // not meaningful, return anything
	if (!d2.valid()) { return false; }; // should really be an exception, but ? if (d1.year()<d2.year()) { return true;}
	if (d1.year()>d2.year()) { return false;}
	else 
	{ // same year
		if (d1.month()<d2.month()) { return true;}
		else if (d1.month()>d2.month()) { return false;} 
		else 
		{ // same month
			if ( d1.day()<d2.day()) { return true;}
			else { return false; } 
		};
	};
	return false; 
};

bool operator > (const date& d1, const date& d2) 
{
	if (d1==d2) { return false;}; // this is strict inequality 
	if (d1<d2) { return false; };
	return true;
};

bool operator <=(const date& d1, const date& d2)
{ 
	if (d1==d2) { return true; }
	return (d1<d2);
};

bool operator >=(const date& d1, const date& d2) 
{ 
	if (d1==d2) { return true;};
	return (d1>d2);
};


inline date next_date(const date& d)
{
	date ndat;
	if (!d.valid()) { return ndat; }; 
	ndat=date((d.day()+1),d.month(),d.year());
	if (ndat.valid()) return ndat; 
	ndat=date(1,(d.month()+1),d.year()); 
	if (ndat.valid()) return ndat;
	ndat = date(1,1,(d.year()+1)); return ndat;
};

inline date previous_date(const date& d){ date ndat;
	if (!d.valid()) { return ndat; }; // return zero
	ndat = date((d.day()-1),d.month(),d.year()); 
	if (ndat.valid()) return ndat; 
	ndat = date(31,(d.month()-1),d.year()); 
	if (ndat.valid()) return ndat; 
	ndat = date(30,(d.month()-1),d.year()); 
	if (ndat.valid()) return ndat; 
	ndat = date(29,(d.month()-1),d.year()); 
	if (ndat.valid()) return ndat; 
	ndat = date(28,(d.month()-1),d.year()); 
	if (ndat.valid()) return ndat; 
	ndat = date(31,12,(d.year()-1)); 
	return ndat;
};

date date::operator ++(int)
{ // postfix operator 
	date d = *this;
	*this = next_date(d);
	return d;
};

date date::operator ++()
{ // prefix operator 
	*this = next_date(*this);
	return *this;
};

date date::operator --(int)
{ // postfix operator, return current value 
	date d = *this;
	*this = previous_date(*this);
	return d;
};

date date::operator --()
{ // prefix operator, return new value 
	*this = previous_date(*this);
	return *this;
};

inline long long_date(const date& d) 
{
	if (d.valid())
		{ return d.year() * 10000 + d.month() * 100 + d.day(); }; 
	return -1;
};

std::string date::get_string()
{
	std::string st;
	st << year_ <<"-"<<month_<<"-"<<day_;
	return st;
};

std::ostream & operator << (std::ostream& os, const date& d)
{
	if (d.valid()) 
		{ os << " " << long_date(d) << " " ; } 
	else 
		{ os << " invalid date "; };
	return os;
};