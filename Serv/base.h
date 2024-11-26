#pragma once
#include <map>
#include <string>
/** @file
 * @author Маштаков Д.С.
 * @version 1.0
 * @brief Заголовочный файл для модуля базы данных
 */
/** @brief Класс для чтения базы данных
 * @details Контейнер data_base хранит в себе логин и пароль пользователя
 * Для получения базы используется метод get_data()
 */
class base
{
private:
    std::map<std::string,std::string> data_base; ///< Контейнер "логин+пароль"
public:
	 /**
     * @brief Установка соединения с базой данных
     * 
     * Читает из файла строку базы данных
     * 
     * @param [in] Путь к файлу базы данных
     * @throw crit_err Если файл не открывается, либо несоответствие формату строки "логин:пароль"
     */
    void connect(std::string f); 
    /**
     * @brief Получить базу данных
     */
    std::map<std::string,std::string> get_data()
    {
        return data_base;
    }
};
