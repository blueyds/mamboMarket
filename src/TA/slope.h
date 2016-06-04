
/* example usage adj_closes is a vector of double closing prices
	SLOPE<double> slope();
	slopes.reserve(adj_closes.size());
	std::transform( adj_closes.begin(), adj_closes.end(), slopes.begin(), sma10);
*/
template <class T>
class SLOPE
{
	T prior_value;
public:
	slope() //window is the size of SMA lookback
	{ prior_value=0;};
	T operator()(T& value)
	{
		if (prior_value==0)
		{
			prior_value=value;
			return 0;
		}else
		{
			T ret_val = 0;
			ret_val=value/prior_value;
			prior_value=value;
			return ret_val;
		}
	}
};