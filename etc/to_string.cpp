#include <iostream> // std::cout
#include <string> // std::string
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
    cout << "Number to convert: " << endl;
    int i;
    cin >> i;
    string s = to_string(i);
    cout << s << endl;
    return 0;
}
