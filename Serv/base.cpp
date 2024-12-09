#include "error.h"
#include "base.h"
#include "interface.h"
#include <iostream>
#include <fstream>
using namespace std;
void base::connect(string f)
{
	interface z;
	f = z.get_base();
	if(f.find('.')==std::string::npos){
		throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БД. КРИТИЧЕСКАЯ ОШИБКА");
		exit(1);
	}
    ifstream rfile;
    rfile.open(f);
    string line, pass, login;
    if (rfile.is_open()) {
        while(getline(rfile,line)) {
  			size_t i = line.find(':');
  			if (i == std::string::npos) {
                throw crit_err("Формат строки неверен; требуется 'login:password'");
            }
  			std::string login = line.substr(0, i);
  			std::string pass = line.substr(i + 1);
  			if (login.empty() && !pass.empty()) {
                throw crit_err("Присутствует только пароль без логина");
            }
            if (!login.empty() && pass.empty()) {
                throw crit_err("Присутствует только логин без пароля");
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
