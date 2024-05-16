#ifndef MIPT2024_S_KOSHELEV_A_ALGO_DATA_STRUCT_H
#define MIPT2024_S_KOSHELEV_A_ALGO_DATA_STRUCT_H

#include <string>

/**
 * Тестовая структура данных для профиляции
 */
struct DataStruct
{
    std::string first_;
    std::string second_;

    /**
     * Стандартный конструктор
     * @param first Первая из строк
     * @param second Вторая из строк
     */
    explicit DataStruct(std::string &&first = "", std::string &&second = "");

    /**
     * Оператор сравнения
     * @param other Сравниваемый объект
     * @return Признак сравнения
     */
    bool operator==(const DataStruct &other) const;

    /**
     * Компаратор, приоритетно сравнение чисел структуры
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return Признак сравнения
     */
    static int Compare(const DataStruct *lhs, const DataStruct *rhs);

    /**
     * Хеш-функция для структуры
     * @param it Хешируемая структура
     * @return Хеш
     */
    static unsigned int Hash(const DataStruct *it);
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_DATA_STRUCT_H
