#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

void string_split(const std::string& s, const char delim, 
                  std::vector<std::string>& elems);

void ltrim(std::string& s);
void rtrim(std::string& s);
void trim(std::string& s);

// 正则表达式判断日期是否合法
bool is_data(const std::string& s);