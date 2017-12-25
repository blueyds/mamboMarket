#ifndef _REPORT_H
#define _REPORT_H
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
/*
	The following code was derived from sec-xbrl python code available on github at
	https://github.com/altova/sec-xbrl which was released under the apache 2,.0 license.
	the apache 2.0 license is compatible with GPL 3.
*/

#include <string>

namespace sec{

class report
{
private:
	std::string fname_;
	std::string old_fname_;
	std::string command_;
	bool open_;
	bool local_;
	bool bad_;
	std::string url_;
	void randomize_fName();
#ifdef _MSVC_VER//windows
	void setUpDeleteCmd()
	{
		command_ = "del";
	};
	void setUpCopyCmd()
	{
		command_ = "copy";
	};
	void setUpDownloadCmd()
	{
		command_ = "wget";
	};
#else//linux
	void setUpDeleteCmd()
	{
		command_ = "rm";

	};
	void setUpCopyCmd()
	{
		command_ = "cp";
	};
	void setUpDownloadCmd()
	{
		command_ = "wget";
	};
#endif
public:
	report():open_(false),command_(""){;};
	report(std::string url, bool isLocal=false);
	~report();
	std::string getUrl(){return url_;};
	void setUrl(std::string url);
	std::string getFileName(){return fname_;};
	//open is true if the file exists on filesystem temp
	bool isOpen(){return open_;};
	bool isBad(){return bad_;}; //something bad happened like a bad filename url path
	void connect();
	void connect(std::string file_name);
	void disconnect();
	void virtual fillFacts()=0;
	// derivatives of report will be responsible for connecting and disconnecting with fillFacts. Also, the derivatives must ensure that url is properly defined before calling connect. This cannot be assumed with normal construction inheritance because the base constructor is called first. And there is no reason to leave the temp file laying around outside of fillFacts.
	//ifi the  derived class specifies the url for report by using report(url) in the member initializer list then the base will be defined with proper Urls and will allow the derived class to call connect , fillFacts , disconnect within the derived constructor
};

} // namespace sec
#endif //!_REPORT_H

