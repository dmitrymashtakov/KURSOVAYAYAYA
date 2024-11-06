#include "log.h"
#include "error.h"
#include <ctime>
#include <iostream>
#include <chrono>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;
int logger::set_path(std::string path_file){
	if(path_file.find('.') == std::string::npos) {
	throw crit_err("ФАЙЛ ЛОГА НЕВЕРНОГО РАСШИРЕНИЯ. КРИТИЧЕСКАЯ ОШИБКА");
	}
    std::ofstream logfile1;
    logfile1.open(path_file,std::ios_base::out | std::ios_base::app);
    if(logfile1.is_open()) {
        return 0;
    } else { 
    throw crit_err("ОШИБКА ФАЙЛА ЛОГА 1. КРИТИЧЕСКАЯ ОШИБКА");
    }
};
string logger::gettime(){
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return string(buf);
};
int logger::writelog(std::string s)
{
    std::ofstream logfile2;
    logfile2.open(path_to_logfile, std::ios_base::out | std::ios_base::app);
    if(logfile2.is_open()) {
        std::string time = gettime();
        logfile2 << time << ' ' << s << std::endl;
    } else {
		throw crit_err("ОШИБКА ФАЙЛА ЛОГА 2. КРИТИЧЕСКАЯ ОШИБКА");
}
    return 0;
};
