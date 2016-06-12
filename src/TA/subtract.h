#ifndef SUBTRACT_H
#define SUBTRACT_H
/*
if you use this with transform it will subtract each
element of b from each element of a
*/

namespace TA{
namespace functors{
template <class T>
class SUBTRACT
{
public:
	subtract () {;};
	T operator()( T a, T b ) const    
    {    
        return a - b;    
    }  
};
}//namespace TA::functors
}//namespace TA
#endif