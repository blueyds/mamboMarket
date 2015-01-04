#pragma once

#include <istream>
#include <string>
#include <vector>

std::vector<std::string> CsvGetLine(std::istream& is, 
                                    bool trimWhiteSpace=true,
                                    const char fieldDelim=',',
                                    const char recordDelim='\n',
                                    const char quote='"');

