#include "error.h"
#include "base.h"
#include "interface.h"
#include <iostream>
#include <fstream>
using namespace std;
void base::connect(string f)
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
  			if (i == std::string::npos) {
                throw crit_err("Формат строки неверен; требуется 'login:password'");
                exit(0);
            }
  			std::string login = line.substr(0, i);
  			std::string pass = line.substr(i + 1);
  			if (login.empty() && !pass.empty()) {
                throw crit_err("Присутствует только пароль без логина");
                exit(0);
            }
            if (!login.empty() && pass.empty()) {
                throw crit_err("Присутствует только логин без пароля");
                exit(0);
            }
            data_base[login]= pass;
        }
    } else {
        throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БД. КРИТИЧЕСКАЯ ОШИБКА");
    }
    if(data_base.empty()){
    	throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БД. КРИТИЧЕСКАЯ ОШИБКА");
    }
};
