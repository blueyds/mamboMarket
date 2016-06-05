#ifndef MACD_H
#define MACD_H
/*
if you use this with transform it will subtract b from a
*/

namespace TA{
template <class T> void macd (std::ForwardIterator{
public:
	subtract () {;};
	T operator()( T a, T b ) const    
    {    
        return a - b;    
    }  
};
}
#endif