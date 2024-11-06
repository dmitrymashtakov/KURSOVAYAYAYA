#include "error.h"
#include "base.h"
#include <iostream>
#include <fstream>
using namespace std;
int base::connect(string f)
{
	if(f.find('.')==std::string::npos){
		throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БД. КРИТИЧЕСКАЯ ОШИБКА");
	}
    ifstream rfile;
    rfile.open(f);
    string line, pass, login;
    if (rfile.is_open()) {
        while(getline(rfile,line)) {
  			size_t i = line.find(':');
  			std::string login = line.substr(0, i);
  			std::string pass = line.substr(i + 1);
            data_base[login]= pass;
        }
        return 0;
    } else {
        throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БД. КРИТИЧЕСКАЯ ОШИБКА");
    }
    if(data_base.empty()){
    	throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БД. КРИТИЧЕСКАЯ ОШИБКА");
    }
};
