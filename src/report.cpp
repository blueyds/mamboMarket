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
#include <cstdlib> //for std::system
#include <random>
#include "report.hpp"

#ifdef _MSVS_VER //windows
std::string rm_cmd("del");
std::string cp_cmd("copy")
#else //linux gmu
std::string rm_cmd("del");
std::string cp_cmd("cp");
#endif

void sec::report::setUrl(std::string url, bool isLocal=false)
{
	disconnect();
	url_=url;
	local_ = isLocal;
}

sec::report::report(std::string url,bool isLocal)
{
	setUrl(url, isLocal);
	bad_=false;
	open_=false;
}
sec::report::~report()
{
	disconnect();
}

void sec::report::randomize_fName()
{
	std::string alpha = "abcdefghijklmnopqrstuvwxyz";
	std::random_device rng;
	std::uniform_int_distribution<int> index_dist(0, alpha.size() - 1);
	for (int i = 0; i < 20; ++i) {
		fname_.push_back(alpha[index_dist(rng)]);
	}
}
void sec::report::connect()
{
	disconnect();
	ramdomize_fName();
    if(local_){setupCopyCmd();}
	else {setupDownloadCmd();};
	if(!std::system(command_.c_str())){bad_=true;open_=false;}
	else {open_=true;};
}


void sec::report::disconnect()
{
	//add an exceptioni since we are going to the system command
	if (open_)
	{
		setupDeleteCmd();
		if(!std::system(command_.c_str()))
			{bad_=true;open_=true;}
		else{open_=false;};
	}
}