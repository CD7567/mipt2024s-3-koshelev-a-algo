#ifndef MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H
#define MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H

#include <array>
#include <cstddef>
#include <random>
#include <string>

#include "test-lib/data/test_struct.h"

#define TEST_SIZE 10
#define TEST_STRING_SIZE 20

/**
 * Генератор случайного size_t
 * @param lborder Левая граница
 * @param rborder Правая граница
 * @return Случайный size_t
 */
inline size_t getRandomReal(size_t lborder = 0, size_t rborder = SIZE_MAX)
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
        it.number_ = getRandomReal();
    }

    return array;
}

template <typename T, size_t Size = TEST_SIZE> std::array<T, Size> genTestDataRandom();

/**
 * Генератор набора тестовых данных size_t
 * @tparam Size Размер набора
 * @return Массив данных
 */
template <size_t Size = TEST_SIZE> std::array<size_t, Size> genTestDataRandom()
{
    std::array<size_t, TEST_SIZE> array;

    for (size_t i = 0; i < TEST_SIZE; ++i)
    {
        array[i] = getRandomReal();
    }

    return array;
}

/**
 * Генератор набора тестовых данных TestStruct
 * @tparam Size Размер набора
 * @return Массив данных
 */
template <size_t Size = TEST_SIZE> std::array<TestStruct, Size> genTestDataRandom()
{
    std::array<TestStruct, TEST_SIZE> array;

    for (auto &it : array)
    {
        it.number_ = getRandomReal();
        it.string_ = genRandomString(TEST_STRING_SIZE);
    }

    return array;
}

/**
 * Генератор набора TestStruct со случайными полями
 * @tparam size Размер массива
 * @return Массив элементов
 */
template <size_t size> std::array<TestStruct, size> genFullRandomData(size_t str_size = TEST_STRING_SIZE)
{
    std::array<TestStruct, size> array;

    for (auto &it : array)
    {
        it.number_ = getRandomReal();
        it.string_ = genRandomString(str_size);
    }

    return array;
}

template<size_t Size = TEST_SIZE>
class RandomDataGenerator {
    static std::array<TestStruct, Size> gen() {

    }
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H
