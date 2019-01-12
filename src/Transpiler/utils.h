#ifndef UTILS_H
#define UTILS_H

#include <list>
#include <string>

std::list<std::string> split(const std::string& str, const char& delimiter);
std::string join(const std::list<std::string>& str, const char& delimiter);

#endif
