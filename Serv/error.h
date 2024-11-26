#pragma once
#include <system_error>
#include <stdexcept>
#include <string>
#include <cstdlib>
/** @file
 * @author Маштаков Д.С.
 * @version 1.0
 * @brief Заголовочный файл модуля возбуждения ошибок
 */
/** @brief Класс для возбуждения критических ошибок
 * Возбуждает критические ошибки
 */
class crit_err:public std::runtime_error
{
	public:
		crit_err(const std::string& s):std::runtime_error(s){}
		
};
/** @brief Класс для возбуждения некритических ошибок
 * Возбуждает некритические ошибки
 */
class no_crit_err:public std::runtime_error
{
	public:
		no_crit_err(const std::string s): std::runtime_error(s){}
};
