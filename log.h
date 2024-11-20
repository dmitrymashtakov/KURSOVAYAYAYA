#pragma once
#include <string>

class logger {
private:
    std::string gettime(); // Получение текущего времени
    std::string path_to_logfile; // Путь к файлу лога

public:
    // Конструктор по умолчанию
    logger();

    // Конструктор с параметром
    logger(const std::string& path);

    // Установка пути к файлу лога
    int set_path(const std::string& path_file);

    // Запись сообщения в лог
    int writelog(const std::string& message);

    // Получение пути к файлу лога (для тестирования)
    std::string get_path() const;
};
