#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_STRUCT_INVERTED_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_STRUCT_INVERTED_H

#include <cstddef>
#include <string>

/**
 * Тестовая структура данных с измененным порядком полей
 */
struct TestStructInverted
{
    std::string string_;
    size_t number_;

    /**
     * Стандартный конструктор
     * @param num Число в структуре
     * @param str Строка в структуре
     */
    explicit TestStructInverted(size_t num = 1000L, std::string &&str = "I am string");

    /**
     * Оператор сравнения
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return Признак сравнения
     */

    /**
     * Оператор сравнения
     * @param other Сравниваемый объект
     * @return Признак сравнения
     */
    bool operator==(const TestStructInverted &other) const;

    /**
     * Компаратор, приоритетно сравнение чисел структуры
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return Признак сравнения
     */
    static int Compare(const TestStructInverted *lhs, const TestStructInverted *rhs);

    /**
     * Хеш-функция для структуры
     * @param it Хешируемая структура
     * @return Хеш
     */
    static unsigned int Hash(const TestStructInverted *it);
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_STRUCT_INVERTED_H
