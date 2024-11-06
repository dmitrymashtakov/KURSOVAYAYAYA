#include "interface.h"
#include "base.h"
#include "communicator.h"
#include "error.h"
#include "log.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
namespace po = boost::program_options;
void interface::comm_proc(int argc, const char** argv)
{
	string z1 = "/home/stud/Desktop/KURS2/base.txt";
	string z2 = "/home/stud/Desktop/KURS2/log.txt";
    int port;
    std::string logfile;
    std::string basefile;
        po::options_description opts("Allowed options");
        opts.add_options()
        ("help,h", "Справка")
        ("basefile,b",
         po::value<std::string>()->default_value(z1),
         "Путь к БД") 
        ("logfile,l",                        
         po::value<std::string>()->default_value(z2), 
         "Путь к логам")
        ("port,p",                               
         po::value<int>(&port)->default_value(33333),
         "Порт сервера");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, opts), vm);
        po::notify(vm);
        if(vm.count("help")) {
            std::cout << opts << "\n";
            exit(0);
        }
		bool flag1,flag2,flag3 = 0;
        if(vm.count("basefile")) {
            if(vm["basefile"].as<std::string>() == z1) {
                flag1 = true;
            }
            basefile = vm["basefile"].as<std::string>();
        }
        if(vm.count("logfile")) {
            if(vm["logfile"].as<std::string>() == z2) {
                flag2 = true;
            }
            logfile = vm["logfile"].as<std::string>();
        }

        if(vm.count("port")) {
            if(vm["port"].as<int>() == 33333) {
                flag3 = true;
            }
            port = vm["port"].as<int>();
    }
   	if(port < 1024 or port > 65535){
   		throw crit_err("НЕКОРРЕКТНЫЙ ПОРТ. КРИТИЧЕСКАЯ ОШИБКА");
   	}
	if(flag1 and flag2 and flag3) {
        std::cout << "Сервер запущен. -h - вызов справки"<<std::endl;
        }
    logger l(logfile);
        if(logfile != "/home/stud/Desktop/log.txt") {
            l.writelog("Путь к лог файлу: "+logfile);
        } else {
            l.writelog("Лог файл стандартный");
        }
    if(basefile != "/home/stud/Desktop/KURS2/base.txt") {
        l.writelog("Путь к файлу БД: " + basefile);
    } else {
        l.writelog("Путь к файлу БД стандартный");
    }
    if(port != 33333) {
        l.writelog("Порт принял нестандратное значение");
    } else {
        l.writelog("Порт принял стандартное значение");
    }
    base h;
    h.connect(basefile);
    l.writelog("Соединение с БД успешно");
    l.writelog("Сервер запущен");
    communicator z;
    z.connection(port,h.get_data(),&l);
}
