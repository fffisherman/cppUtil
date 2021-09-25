#include "string_util.h"

int main() {
    std::string s = " 2&3&4&4&5";
    std::vector<std::string> split_res;
    string_split(s, '&', split_res);

    for(auto it:split_res) {
        std::cout << it << " " ;
    }
    std::cout << std::endl;
    std::string data = "2021-09-13";
    std::string data2 = "2021-19-13";
    std::cout << data << "is correct data :" << is_data(data) << std ::endl;
    std::cout << data << "is correct data :" << is_data(data2) << std ::endl;
}