#include "sec/10Q.hpp"

sec::ten_q::ten_q(std::string url):
	xml_report(url),
	xbrli_("http ://www.xbrl.org/2003/instance")
{
	load_xmlfile();
	fillFacts();
}

bool sec::ten_q::isContextSegment(std::string context)
{
	for (int i=0;;i++)
	{
		std::string s;
		s=getAttribute(context,{0,i},{"xbrl","context"},{xbrli_,xbrli_,""});
		if(s.length() > 0)//we found the right instance
		{
			std::string segment="";
			segment=getChildValue({0,i,0},{"xbrl","context","segment"},{xbrli_,xbrli_,xbrli_});
		}
	}
}

std::string sec::ten_q::getValue(std::string name, std::string ns)
{
	//shortcut for getting a quick value from the main xbrl instance file. returns empty if none found
	std::string ret("");
	int index;
	for (index=0;;index++)
	{
		std::string ctx;
		ctx=getAttribute("contextRef",{0,index},{"xbrl",name},{xbrli_,ns,""});
		if (isContextSegment(ctx)){break;}
	}
	ret = getChildValue({0,index},{"xbrl",name},{xbrli_,ns});
	return ret;
}

void sec::ten_q::fillFacts()
{
	sec_=getAttribute("dei",{0},{"xbrl"},{xbrli_,"xmlns"});
}