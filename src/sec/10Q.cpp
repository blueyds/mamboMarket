
#include "sec/10Q.hpp"

sec::ten_q::ten_q(std::string url):
	xml_report(url)
{
	load_xmlfile();
	fillFacts();
	unload_xmlfile();
}



std::string sec::ten_q::get10qString(std::string name, std::string ns)
{
	std::string ret;
	date best_date("1920-01-01");

	findXpath("//" + ns + ":" + name);


	for (int i = 0; i < getNodeCount(); ++i)
	{
		pugi::xpath_node node;
		std::string ctx;
		std::map<std::string, date>::iterator it;

		node = getNode(i);
		ctx = node.node().attribute("contextRef").as_string();
		if (getNodeCount()==1) //the requested data does not have a context so ignore that part
		{
			return node.node().text().as_string();
		}
		it = context_.find(ctx);
		if (it->second < best_date) //we want to return the most recent
		{
			best_date = it->second;
			ret = node.node().text().as_string();
		}
	}
	return ret;
}

double sec::ten_q::get10qDouble(std::string name, std::string ns)
{
	double ret(0);
	date best_date("1920-01-01");
	findXpath("//"+ns+":"+name);
	
	
	for (int i = 0; i < getNodeCount(); ++i)
	{
		pugi::xpath_node node;
		std::string ctx;
		std::map<std::string, date>::iterator it;
		
		node = getNode(i);
		ctx = node.node().attribute("contextRef").as_string();
		if (ctx.size() > 10) { continue; };
		if (getNodeCount()==1) //the requested data does not have a context so ignore that part
		{
			return node.node().text().as_double();
		}
		it = context_.find(ctx);
		if (it->second > best_date) //we want to return the most recent
		{
			best_date = it->second;
			ret = node.node().text().as_double();
		}
	}
	return ret;
}

void sec::ten_q::fillFacts()
{
	Period_= get10qString("DocumentPeriodEndDate", "dei");
	//date dper(Period_);
	//we now go through all the first context sections and pull the first one with instance of PeriodEndDate for instance_ctx
	findXpath("//xbrli:context");
	pugi::xpath_node_set::const_iterator it = xml_begin();
	if (it == xml_end()) { findXpath("//context"); it = xml_begin(); };
	for (it; it != xml_end(); ++it)
	{
		pugi::xpath_node node = *it;
		std::string instance = node.node().child("xbrli:period").child("xbrli:instant").text().as_string();
		std::string period = node.node().child("xbrli:period").child("xbrli:endDate").text().as_string();
		if ((instance.length() == 0) && (period.length() == 0))
		{
			instance = node.node().child("xbrli:period").child("xbrli:instant").text().as_string();
			period = node.node().child("xbrli:period").child("xbrli:endDate").text().as_string();
		}
		std::string context = node.node().attribute("id").as_string();
		
		if (instance.size() > 1)
		{
			date d1(instance);
			context_.insert(std::pair<std::string, date>(context, d1));
		}
		else if (period.size() > 1)
		{
			date d1(period);
			context_.insert(std::pair<std::string, date>(context, d1));
		}
	}
	
	currentAssets_= get10qDouble("AssetsCurrent","us-gaap");
	currentLiabilities_= get10qDouble("LiabilitiesCurrent", "us-gaap");

    cash_= get10qDouble("Cash", "us-gaap");
    if(cash_==0.0)
    	{cash_ = get10qDouble("CashAndCashEquivalentsAtCarryingValue", "us-gaap");}
    if(cash_==0.0)
    	{cash_ = get10qDouble("CashCashEquivalentsAndShortTermInvestments", "us-gaap");}

    marketableSecurities_= get10qDouble("MarketableSecuritiesCurrent", "us-gaap");
    if (marketableSecurities_==0.0)
    	{marketableSecurities_ = get10qDouble("AvailableForSaleSecuritiesCurrent", "us-gaap");}
    if (marketableSecurities_==0.0)
    	{marketableSecurities_ = get10qDouble("ShortTermInvestments", "us-gaap");}
 	if (marketableSecurities_ ==0.0)
    	{marketableSecurities_ = get10qDouble("OtherShortTermInvestments", "us-gaap");}
 


    currentAR_ = get10qDouble("AccountsReceivableNetCurrent", "us-gaap");
    currentRatio_ = currentAssets_/currentLiabilities_;
    quickRatio_=(cash_+marketableSecurities_+currentAR_)/currentLiabilities_;
	cashRatio_=cash_/currentLiabilities_;

}