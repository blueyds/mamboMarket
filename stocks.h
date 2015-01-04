#pragma once
#include <vector>

#include <boost/serialization/vector.hpp>

#include <boost/serialization/version.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class stocks
{
private:
	friend class boost::serialization::access;

	template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & s1;
    }

public:
	std::vector<std::string> s1; // stock name

	stocks(void);
	~stocks(void);
	void regenerate();
};
