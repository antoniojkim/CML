
#include "utils.h"
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

list<string> split(const string& str, const char& delimiter) {
    list<string> strList;
    istringstream iss{str};

    ostringstream oss;
    unsigned int size = 0;
    char c;
    while (iss.get(c)) {
        if (c == delimiter && size > 0) {
            strList.emplace_back(oss.str());
            oss.str("");
            oss.clear();
            size = 0;
        } else {
            oss << c;
            ++size;
        }
    }
    if (size > 0) {
        strList.emplace_back(oss.str());
    }

    return strList;
}

std::string join(const std::list<std::string>& str, const char& delimiter){
    ostringstream out;
    bool first = true;
    for (auto& s : str){
        if (!first){
            out << delimiter;
        }
        else{
            first = false;
        }
        out << s;
    }
    return out.str();
}
