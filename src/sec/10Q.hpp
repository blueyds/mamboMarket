#ifndef ten_q_hpp
#define ten_q_hpp
/*
    Copyright (C) {2016}  {Craig Nunemaker}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string>
#include <map>
#include "date/date.h"
#include "xml/xml_report.hpp"


namespace sec{

class ten_q : public xml_report{
private:
	std::map < std::string, date> context_;
	std::string type_;
    std::string FYfocus_;
    std::string Period_;
    double currentAssets_;
    double currentLiabilities_;
    double cash_;
    double marketableSecurities_;
    double currentAR_;
    double currentRatio_;
    double quickRatio_;
    double cashRatio_;
	//bool isContextSegment(std::string context);
public:
	ten_q(std::string url);
    	
    std::string get10qString(std::string name, std::string ns="");
    double get10qDouble(std::string name,std::string ns="");
    void fillFacts();
    double getCurrentRatio(){return currentRatio_;};
    double getQuickRatio(){return quickRatio_;};
    double getCashRatio(){return cashRatio_;};
    double getCurrentAssets(){return currentAssets_;};
    double getCurrentLiabilities(){return currentLiabilities_;};
};



}//namepsace sec

#endif //ifndef ten_q_hpp