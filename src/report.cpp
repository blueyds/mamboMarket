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
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "reports.hpp"


std::string sec::report::setUrl(std::string url)
{
	disconnect();
	url_=url;
	
}
sec::report::~report()
{
	if(open_){disconnect();};
}
void sec::report::connect()
{
	if(open_){disconnect():};
	std::string alpha = "abcdefghijklmnopqrstuvwxyz";
	boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, alpha.size() - 1);
    for(int i = 0; i < 20; ++i) {
        fname_ << alpha[index_dist(rng)];
    }
    connect(fname_);
}
void sec::report::connect(std::string file_name)
{
	//add an exception ii fstream cannot open the file
	if(open_){disconnect();};
	fname_=file_name;
	std::string command="wget -O "+fname_+" '"+url_+"'";
	std::system(command.c_str());
	open_=true;
}

void sec::report::disconnect()
{
	//add an exceptioni since we are going to the system command
	if (open_)
	{
		std::string command = "rm "+fname;
		std::system(command.c_str());
		open_=false;
	}
}