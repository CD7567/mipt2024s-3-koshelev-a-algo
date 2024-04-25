#ifndef MIPT2024_S_KOSHELEV_A_ALGO_SORTED_GENERATOR_H
#define MIPT2024_S_KOSHELEV_A_ALGO_SORTED_GENERATOR_H

#include <array>
#include <cstddef>

#include "test-lib/common.h"
#include "test-lib/data/generators/inline_generators.h"

/**
 * Генератор отсортированного набора данных
 * @tparam T Тип данных
 * @tparam Size Размер набора
 */
template <typename T, size_t Size = TEST_SIZE> class SortedGenerator
{
  public:
    /**
     * Функция генерации набора
     * @return Набор данных
     */
    std::array<T, Size> generate();
};

/**
 * Специализация для типа size_t
 * @tparam Size Размер набора
 */
template <size_t Size> class SortedGenerator<size_t, Size>
{
  public:
    std::array<size_t, Size> generate()
    {
        std::array<size_t, Size> array;

        for (size_t i = 0; i < Size; ++i)
        {
            array[i] = i;
        }

        return array;
    }
};

/**
 * Специализация для типа TestStruct
 * @tparam Size Размер набора
 */
template <size_t Size> class SortedGenerator<TestStruct, Size>
{
  public:
    std::array<TestStruct, Size> generate()
    {
        std::array<TestStruct, Size> array;

        for (size_t i = 0; i < Size; ++i)
        {
            array[i].number_ = i;
            array[i].string_ = "I am string";
        }

        return array;
    }
};

/**
 * Специализация для типа TestStructInverted
 * @tparam Size Размер набора
 */
template <size_t Size> class SortedGenerator<TestStructInverted, Size>
{
  public:
    std::array<TestStructInverted, Size> generate()
    {
        std::array<TestStructInverted, Size> array;

        for (size_t i = 0; i < Size; ++i)
        {
            array[i].number_ = i;
            array[i].string_ = "I am string";
        }

        return array;
    }
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_SORTED_GENERATOR_H
