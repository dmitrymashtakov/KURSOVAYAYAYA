#pragma once
#include <map>
#include <string>
class base
{
private:
    std::map<std::string,std::string> data_base;
public:
    void connect(std::string f = "base.txt");
    std::map<std::string,std::string> get_data()
    {
        return data_base;
    }
};
