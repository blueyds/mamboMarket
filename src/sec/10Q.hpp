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
#include "xml/xml_report.hpp"


namespace sec{

class ten_q : public xml_report{
private:
    std::string sec_;
    std::string fasb_;
    std::string xbrli_;
    std::string period_ctx_; //for amount that cover time periods.
    std::string instance_ctx_;//for amount that represents point in time
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
    	
    std::string getValue(std::string name, std::string ns="");
    double getValue(std::string name, std::string ns="");
    void fillFacts();
    double getCurrentRatio(){return currentRatio_;};
    double getQuickRatio(){return quickRatio_;};
    double getCashRatio(){return cashRatio_;};
    double getCurrentAssets(){return currentAssets_;};
    double getCurrentLiabilities(){return currentLiabilities_;};
    std::string getSecNS(){return sec_;};
    std::string getFasbNS(){return fasb_;};
};



}//namepsace sec

#endif //ifndef ten_q_hpp