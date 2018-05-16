#include "sec/10Q.hpp"

sec::ten_q::ten_q(std::string url):
	xml_report(url),
	xbrli_("http://www.xbrl.org/2003/instance"),
	period_ctx_("")
{
	load_xmlfile();
	fillFacts();
}



std::string sec::ten_q::getSValue(std::string name, std::string ns)
{
	//shortcut for getting a quick value from the main xbrl instance file. returns empty if none found
	std::string ret("");
	int index;
	for (index=0;;index++)
	{
		std::string ctx;
		ctx=getAttribute("contextRef",{0,index},{"xbrl",name},{xbrli_,ns,""});
		if (period_ctx_=="") {break;}//if we have not defined ctx yet then ignore any further checks
		if (period_ctx_==ctx){break;}
		if (instance_ctx_==ctx){break;}
	}
	ret = getChildValue({0,index},{"xbrl",name},{xbrli_,ns});
	return ret;
}

double sec::ten_q::getDValue(std::string name, std::string ns)
{
	double ret=0.0;
	std::string value=getSValue(name,ns);
	try{
		ret=std::stod(value);
	} catch(const std::invalid_argument& ia) {
		ret=0.0;
	}
	return ret;
}

void sec::ten_q::fillFacts()
{
	sec_=getAttribute("dei",{0},{"xbrl"},{xbrli_,"xmlns"});
	fasb_=getAttribute("us-gaap",{0},{"xbrl"},{xbrli_,"xmlns"});
	std::string PeriodEndDate = getSValue("DocumentPeriodEndDate",sec_);
	//we now go through all the first context sections and pull the first one with instance of PeriodEndDate for instance_ctx
	for (int i=0;;i++) {
		std::string s;
		s=getAttribute("id",{0,i},{"xbrl","context"},{xbrli_,xbrli_,""});
		if(s.length() > 0)//we found the right instance
		{ 	if(getChildValue({0,i,0},{"xbrl","context","instant"},{xbrli_,xbrli_,xbrli_})==PeriodEndDate) 
			{break;} 
		}
		instance_ctx_ = s; 
	}
	for (int i=0;;i++) {
		std::string s;
		s=getAttribute("id",{0,i},{"xbrl","context"},{xbrli_,xbrli_,""});
		if(s.length() > 0)//we found the right instance
		{ 	if(getChildValue({0,i,0},{"xbrl","context","endDate"},{xbrli_,xbrli_,xbrli_}) == PeriodEndDate) 
			{break;} 
		}
		period_ctx_ = s;
	}
	currentAssets_=getDValue("AssetsCurrent",fasb_);
	currentLiabilities_=getDValue("LiabilitiesCurrent",fasb_);
    cash_=getDValue("Cash",fasb_);
    if(cash_==0.0)
    	{cash_ = getDValue("CashAndCashEquivalentsAtCarryingValue",fasb_);}
    if(cash_==0.0)
    	{cash_ = getDValue("CashCashEquivalentsAndShortTermInvestments",fasb_);}
    marketableSecurities_=getDValue("MarketableSecuritiesCurrent",fasb_);
    if (marketableSecurities_==0.0)
    	{marketableSecurities_ = getDValue("AvailableForSaleSecuritiesCurrent",fasb_);}
    if (marketableSecurities_==0.0)
    	{marketableSecurities_ = getDValue("ShortTermInvestments",fasb_);}
 	if (marketableSecurities_ ==0.0)
    	{marketableSecurities_ = getDValue("OtherShortTermInvestments",fasb_);}
 
    currentAR_ = getDValue("AccountsReceivableNetCurrent",fasb_);
    //currentRatio_;
    //quickRatio_;
    //cashRatio_;
}