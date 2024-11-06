#pragma once
#include <string>
class logger
{
    std::string gettime();
    std::string path_to_logfile;
public:
    int writelog(std::string s);
    int set_path(std::string path_file);
    logger(){
    path_to_logfile = " ";
    };
    logger(std::string s){
    path_to_logfile = s;
    };
};
