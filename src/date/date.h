// file: date.h 
// author: Bernt A Oedegaard.

#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>


class date {
protected:
    int year_;
    int month_;
    int day_;
public:
	enum Format {
		YYYYMMDD,
		MMDDYYYY};
    
    date();
    date(const int& d, const int& m, const int& y);
    date(const std::string dt,Format fmt=YYYYMMDD);

    bool valid(void)  const;

    int day()   const;
    int month() const;
    int year()  const;

    void set_day   (const int& day   );
    void set_month (const int& month );
    void set_year  (const int& year  );
    
    std::string get_string();

    date operator ++();    // prefix  
    date operator ++(int); // postfix  
    date operator --();    // prefix
    date operator --(int); // postfix
};

bool operator == (const date&, const date&);   // comparison operators
bool operator != (const date&, const date&); 
bool operator <  (const date&, const date&); 
bool operator >  (const date&, const date&); 
bool operator <= (const date&, const date&); 
bool operator >= (const date&, const date&); 

std::ostream& operator << ( std::ostream& os, const date& d);  // output operator

#endif
