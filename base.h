#pragma once
#include <map>
#include <string>
class base
{
private:
    std::map<std::string,std::string> data_base;
public:
    int connect(std::string f = "/home/stud/Desktop/KURS2/base.txt");
    std::map<std::string,std::string> get_data()
    {
        return data_base;
    }
};
