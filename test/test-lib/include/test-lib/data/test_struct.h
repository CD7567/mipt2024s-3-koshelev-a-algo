#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_STRUCT_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_STRUCT_H

#include <cstddef>
#include <string>

/**
 * Тестовая структура данных
 */
struct TestStruct
{
    size_t number_;
    std::string string_;

    /**
     * Стандартный конструктор
     * @param num Число в структуре
     * @param str Строка в структуре
     */
    explicit TestStruct(size_t num = 1000L, std::string &&str = "I am string");

    /**
     * Оператор сравнения
     * @param other Сравниваемый объект
     * @return Признак сравнения
     */
    bool operator==(const TestStruct &other) const;

    /**
     * Компаратор, приоритетно сравнение чисел структуры
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return Признак сравнения
     */
    static int Compare(const TestStruct *lhs, const TestStruct *rhs);

    /**
     * Хеш-функция для структуры
     * @param it Хешируемая структура
     * @return Хеш
     */
    static unsigned int Hash(const TestStruct *it);
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_STRUCT_H
