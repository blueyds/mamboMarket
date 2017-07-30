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
#include <csystem> //for std::system
#include <fstream>
#include <cstdlib>
#include "reports.hpp"


std::string sec::report::setUrl(std::string url)
{
	disconnect();
	url_=url;
	
}
sec::report::~report()
{
	if(open){disconnect();};
}
void sec::report::connect()
{
	std::strin alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int size=alpha.length();
	std::string fname="";
	
	for (int i=1;i<20;i++)
	{
		int x=rand() % size;
		fname=fname + alpha[x];
	}
	connect(fname);
}
void sec::report::connect(std::string file_name)
{
	//add an exception ii fstream cannot open the file
	fname_=file_name;
	std::string command="wget -O "+fname_+" '"+url_+"'";
	std::system(command.c_str());
	open=true;
	std::fstream f(fname_);
	f.close();
}

void sec::report::disconnect()
{
	//add an exceptioni since we are going to the system command
	if (open)
	{
		std::string command = "rm "+fname;
		std::system(command.c_str());
		open=false;
	}
}