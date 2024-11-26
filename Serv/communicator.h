#pragma once
#include <string>
#include <vector>
#include <map>
#include "log.h"
#include "error.h"

using namespace std;
/** @file
 * @author Маштаков Д.С.
 * @version 1.0
 * @brief Заголовочный файл для коммуникатора сервера
 */
/** @brief Класс коммуникатора
 * @details Устанавливает соединение с сервером, производит авторизацию клиента
 * В качестве метода хэширования выбран sha224.
 */
class communicator
{
    public:
    /**
     * @brief Соединение с сервером
     * 
     * @details Производит соединение с сервером, авторизует пользователя
     * Передает вектор с данными для вычисления в класс calc.
     * @param [in] Номер порта, контейнер с базой данных, переменная типа logger для записи всех событий в журнал событий
     * @throw crit_err, если произошел сбой на этапе соединения с сервером, на этапе авторизации или отправки данных
     */
    int connection(int port,std::map<std::string,std::string> base, logger* l);
    /**
     * @brief Формирование хэша методом SHA224
     * 
     * @details Производит формирование хэша методом sha224 библиотеки cryptopp
     * Формирует хэш соли и пароля
     * @param [in] input_str
     * @return результат хэширования
     */
    std::string sha224(std::string input_str);
    /**
     * @brief Формирование соли
     * 
     * @details Производит формирование соли
     * ПОсновано на библиотеке boost
     * @param [in] input_str
     * @return сформированная соль
     */
    std::string generate_salt();
};
