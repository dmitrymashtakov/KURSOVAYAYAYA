#pragma once
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "log.h"
#include "base.h"
#include "communicator.h"
#include "error.h"
/** @file
 * @author Маштаков Д.С.
 * @version 1.0
 * @brief Заголовочный файл для интерфейса
 */
/** @brief Класс интерфейса
 * @details Получает порт, по умолчанию 33333
 * Парсер выполняет чтение операндов ком. строки
 * Устанавливается соединение с базой данных и журналом лога
 * Выполняется вызов справки
 */
class interface {
    int port; ///< Переменная с номером порта
    string basefile;
    string logfile;

public:
    interface() : port(33333), basefile("base.txt"), logfile("log.txt") {} //< конструктор по умолчанию
    /**
     * @brief Парсер
     * 
     * @details Читает операнды ком.строки
     * В случае передачи операнда -h производится вызов справки
     * @param [in] Кол-во операндов, значение операндов
     * @throw crit_err в случае передачи некорректного значения порта
     * @return true или false в случае корректной или некорретной передачи аргументов
     */
    bool parser(int argc, const char** argv);
    /**
     * @brief Установка соединения с базой данных и журналом лога
     * 
     * @details Устанавливает соединение с базой банных и журналом лога
     * @param [in] путь к файлу базы данных и журналу лога
     */
    void setup_connection(const std::string& basefile, const std::string& logfile);
    /**
     * @brief Справка
     * 
     * Вызов справки
     *
     */
    void spravka(const boost::program_options::options_description& opts);
    /**
     * @brief Получение порта
     * 
     * Этот метод передает значение порта в коммуникатор
     *
     */
    int get_port() const { return port; }
    std::string get_base() { return basefile;}
    std::string get_log() { return logfile;}
};
