#ifndef MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H
#define MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H

#include <array>
#include <cstddef>
#include <random>
#include <string>

#include "test-lib/data/generators/inline_generators.h"
#include "test-lib/data/test_struct.h"
#include "test-lib/data/test_struct_inverted.h"

#define TEST_SIZE 10
#define TEST_STRING_SIZE 20

#define TEST_LINKED_LIST_TYPES size_t, TestStruct

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
        it.number_ = genRandomReal();
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
        it.number_ = genRandomReal();
        it.string_ = genRandomString(str_size);
    }

    return array;
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H
