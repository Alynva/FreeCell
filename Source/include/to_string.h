#ifndef TO_STRING_H
#define TO_STRING_H

#include <iostream>// std::string
#include <string> // std::string
#include <sstream> // std::ostringstream

using namespace std;

template <typename T>
string to_string(T Number) {
    string Result;
    ostringstream convert;
    convert << Number;
    Result = convert.str();
    return Result;
}

#endif
