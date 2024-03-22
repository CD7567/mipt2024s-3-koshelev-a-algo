#ifndef TEST_COMMON_DEFINITIONS_HXX
#define TEST_COMMON_DEFINITIONS_HXX

#include <array>
#include <cstddef>
#include <random>
#include <string>

#define test_size 10
#define test_string_size 20

/**
 * Компаратор для size_t, из-за беззнаковости не обойтись разностью
 * @param lhs Левый операнд
 * @param rhs Правый операнд
 * @return Признак сравнения
 */
inline int compareSizeT(size_t lhs, size_t rhs)
{
    if (lhs <= rhs)
    {
        if (rhs <= lhs)
            return 0;
        else
            return -1;
    }
    else
        return 1;
}

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
    explicit TestStruct(size_t num = 1000L, std::string &&str = "I am string") : number_(num), string_(str)
    {
    }

    /**
     * Компаратор, приоритетно сравнение чисел структуры
     * @param lhs Левый операнд
     * @param rhs Правый операнд
     * @return
     */
    static int Compare(const TestStruct *lhs, const TestStruct *rhs)
    {
        return (rhs->number_ == lhs->number_) ? lhs->string_.compare(rhs->string_)
                                              : compareSizeT(lhs->number_, rhs->number_);
    }

    /**
     * Хеш-функция для структуры
     * @param it Хешируемая структура
     * @return Хеш
     */
    static unsigned int Hash(const TestStruct *it)
    {
        return it->number_ + std::hash<std::string>()(it->string_);
    }
};

/**
 * Генератор случайного size_t
 * @param lborder Левая граница
 * @param rborder Правая граница
 * @return Случайный size_t
 */
inline size_t genRandomSize(size_t lborder = 0, size_t rborder = SIZE_MAX)
{
    static std::random_device random_device;
    static std::mt19937 generator(random_device());
    static std::uniform_int_distribution<size_t> distribution(lborder, rborder);

    return distribution(generator);
}

/**
 * Генератор случайной строки строчной латиницей
 * @param size Длина строки
 * @return Случайная строка
 */
inline std::string genRandomString(size_t size)
{
    static std::random_device random_device;
    static std::mt19937 generator(random_device());
    static std::uniform_int_distribution<char> distribution(97, 122);
    std::string result;

    for (size_t i = 0; i < size; ++i)
    {
        result += distribution(generator);
    }

    return result;
}

/**
 * Генератор отсортированного набора TestStruct
 * @tparam size Размер массива
 * @return Массив элементов
 */
template <size_t size> std::array<TestStruct, size> genSortedData()
{
    std::array<TestStruct, size> array;

    for (size_t i = 0; i < size; ++i)
    {
        array[i].number_ = i;
    }

    return array;
}

/**
 * Генератор отсортированного по убыванию набора TestStruct с повторениями
 * @tparam size Размер массива
 * @param repeat_size Длина повторения, проверка на 0  не производится
 * @return Массив элементов
 */
template <size_t size> std::array<TestStruct, size> genSortedDescData(size_t repeat_size)
{
    std::array<TestStruct, size> array;

    size_t counter = 0;
    for (size_t i = size - 1; counter < size; --i)
    {
        for (size_t j = 0; j < repeat_size; ++j)
        {
            array[counter++].number_ = i;
        }
    }

    return array;
}

/**
 * Генератор набора TestStruct со случайными числами
 * @tparam size Размер массива
 * @return Массив элементов
 */
template <size_t size> std::array<TestStruct, size> genRandomNumData()
{
    std::array<TestStruct, size> array;

    for (auto &it : array)
    {
        it.number_ = genRandomSize();
    }

    return array;
}

/**
 * Генератор набора TestStruct со случайными полями
 * @tparam size Размер массива
 * @return Массив элементов
 */
template <size_t size> std::array<TestStruct, size> genFullRandomData(size_t str_size = test_string_size)
{
    std::array<TestStruct, size> array;

    for (auto &it : array)
    {
        it.number_ = genRandomSize();
        it.string_ = genRandomString(str_size);
    }

    return array;
}

#endif // TEST_COMMON_DEFINITIONS_HXX
