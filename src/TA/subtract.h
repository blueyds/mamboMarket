#ifndef SUBTRACT_H
#define SUBTRACT_H
/*
if you use this with transform it will subtract b from a
*/

namespace TA{
template <class T>
class subtract
{
public:
	subtract () {;};
	T operator()( T a, T b ) const    
    {    
        return a - b;    
    }  
};
}
#endif