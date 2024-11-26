#include "interface.h"

namespace po = boost::program_options;

void interface::spravka(const po::options_description& opts) {
    std::cout << opts << std::endl;
}

bool interface::parser(int argc, const char** argv) {
    po::options_description opts("Опции");
    opts.add_options()
        ("help,h", "Справка")
        ("basefile,b", po::value<std::string>()->default_value("base.txt"), "Путь к БД")
        ("logfile,l", po::value<std::string>()->default_value("log.txt"), "Путь к логам")
        ("port,p", po::value<int>(&port)->default_value(33333), "Порт сервера");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    if (vm.count("help")) {
        spravka(opts);
        return 0; 
    }
	
    basefile = vm["basefile"].as<std::string>();
    logfile = vm["logfile"].as<std::string>();
    std::ifstream db_file(basefile);
    std::ifstream lg_file(logfile);
    if (basefile.find('.') == std::string::npos or !db_file.good()) {
        throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ БАЗЫ ДАННЫХ. КРИТИЧЕСКАЯ ОШИБКА");
        return 0;
    }
    if (logfile.find('.') == std::string::npos or !lg_file.good()) {
        throw crit_err("НЕКОРРЕКТНЫЙ ФАЙЛ ЛОГА. КРИТИЧЕСКАЯ ОШИБКА");
        return 0;
    }
    
    if (port < 1024 || port > 65535) {
        throw crit_err("НЕКОРРЕКТНЫЙ ПОРТ. КРИТИЧЕСКАЯ ОШИБКА");
        return 0;
    }

    // Логирование информации о файлах
    logger l(logfile);
    l.writelog("Путь к лог файлу: " + logfile);
    l.writelog("Путь к файлу БД: " + basefile);
    l.writelog("Используемый порт: " + std::to_string(port));

    return 1; // Успешно обработаны параметры
}

void interface::setup_connection(const std::string& basefile, const std::string& logfile) {
    base h;
    logger l(logfile); // Логирование

    try {
        h.connect(basefile);
        l.writelog("Соединение с БД успешно");
        l.writelog("Сервер запущен");
    } catch (const std::exception& e) {
        l.writelog("Ошибка соединения с БД: " + std::string(e.what()));
    }
    communicator z;
    std::cout << "Сервер запущен на порте "<< port << " -h - вызов справки"<<std::endl;
    z.connection(port, h.get_data(), &l);
}
