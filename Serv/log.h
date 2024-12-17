#pragma once
#include <string>
/** @file
 * @author Маштаков Д.С.
 * @version 1.0
 * @brief Заголовочный файл для установки журнала лога
 */
/** @brief Класс для журнала лога
 */
class logger {
private:
	/**
     * @brief Получение текущего времени
     * 
     * Позволяет получить время вместе с датой
     *
     */
    std::string gettime();
    std::string path_to_logfile; ///< Путь к файлу лога

public:
    logger(); ///< конструктор по умолчанию

    logger(const std::string& path); ///< конструктор с параметром

    /**
     * @brief Установка пути к файлу лога
     * 
     * Устанавливает путь к файлу лога
     * 
     * @param [in] Путь к файлу лога
     * @throw crit_err Если файл не открывается
     */
    int set_path(const std::string& path_file);

    /**
     * @brief Запись события в журнал
     * 
     * Записывает событие в лог
     * 
     * @param [in] Сообщение для записи
     * @throw crit_err Если файл не открывается на запись
     */
    int writelog(const std::string& message);

    /**
     * @brief Получение пути к файлу лога (для модульного тестирования)
     * 
     */
    std::string get_path() const;
};
