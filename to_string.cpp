#include <string> // std::string
#include <iostream> // std::cout
#include <sstream> // std::ostringstream

using namespace std;

template <typename T>
string to_string ( T Number ) {
    string Result;
    ostringstream convert;
    convert << Number;
    Result = convert.str();
    return Result;
}

int main(){
    string s = to_string(2);
    cout << s << endl;

    return 0;
}
