#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <limits>
#include <stdlib.h>
/** @file
 * @author Маштаков Д.С.
 * @version 1.0
 * @brief Заголовочный файл для модуля вычислений
 */
/** @brief Класс для операции среднего арифметического элементов вектора
 * @details Вектор указывается в параметрах конструктора.
 * Для получения результат вычислений используется метод send_res.
 */
class calc
{
	public:
	float res; ///< Переменная,в которую будет записан результат
	/**
 	* @brief Вычисление
	 * @param [in] chisla Вектор данных. Не должен быть пустой.
 	* Тип данных float
 	* @throw no_crit_err, если вектор пуст.
 	*/
    calc(std::vector<float>chisla);
   	float send_res(); ///< Метод для отправки результата
};
