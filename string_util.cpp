#include "string_util.h"

#include <regex.h>
#include <algorithm>

static const char white_space[] = " \n\t\v\r\f"; 
void ltrim(std::string& s) {
    s.erase(0, s.find_first_of(white_space));
}
void rtrim(std::string& s) {
    s.erase(s.find_last_of(white_space)+1U);
}
void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

void string_split(const std::string& s, const char delim, 
                  std::vector<std::string>& elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)){
        elems.emplace_back(item);
    }
}

// 正则表达式判断日期是否合法 yy-mm-dd
bool is_data(const std::string& s) {
    std::string data_regex = 
        "^([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$";

    regex_t data_pattern;
    int flags = REG_NOSUB | REG_EXTENDED;
    regcomp(&data_pattern, data_regex.c_str(), flags);
    bool result = regexec(&data_pattern, s.c_str(), (size_t)0, nullptr, 0) == 0;
    regfree(&data_pattern);
    return result;
}
