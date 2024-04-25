#ifndef MIPT2024_S_KOSHELEV_A_ALGO_REPETITIVE_GENERATOR_H
#define MIPT2024_S_KOSHELEV_A_ALGO_REPETITIVE_GENERATOR_H

#include <array>
#include <cstddef>

#include "test-lib/common.h"
#include "test-lib/data/generators/inline_generators.h"

/**
 * Генератор отсортированного набора данных с повторениями
 * @tparam T Тип данных
 * @tparam Size Размер набора
 */
template <typename T, size_t Size = TEST_SIZE, size_t Period = Size / 5> class RepetitiveGenerator
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
template <size_t Size, size_t Period> class RepetitiveGenerator<size_t, Size, Period>
{
  public:
    std::array<size_t, Size> generate()
    {
        std::array<size_t, Size> array;
        size_t total = 0;

        for (size_t i = 0; total < Size; ++i)
        {
            for (size_t j = 0; j < Period && total < Size; ++j, ++total)
            {
                array[i * Period + j] = i;
            }
        }

        return array;
    }
};

/**
 * Специализация для типа TestStruct
 * @tparam Size Размер набора
 */
template <size_t Size, size_t Period> class RepetitiveGenerator<TestStruct, Size, Period>
{
  public:
    std::array<TestStruct, Size> generate()
    {
        std::array<TestStruct, Size> array;
        size_t total = 0;

        for (size_t i = 0; total < Size; ++i)
        {
            for (size_t j = 0; j < Period && total < Size; ++j, ++total)
            {
                array[i * Period + j].number_ = i;
                array[i * Period + j].string_ = "I am string";
            }
        }

        return array;
    }
};

/**
 * Специализация для типа TestStructInverted
 * @tparam Size Размер набора
 */
template <size_t Size, size_t Period> class RepetitiveGenerator<TestStructInverted, Size, Period>
{
  public:
    std::array<TestStructInverted, Size> generate()
    {
        std::array<TestStructInverted, Size> array;
        size_t total = 0;

        for (size_t i = 0; total < Size; ++i)
        {
            for (size_t j = 0; j < Period && total < Size; ++j, ++total)
            {
                array[i * Period + j].number_ = i;
                array[i * Period + j].string_ = "I am string";
            }
        }

        return array;
    }
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_REPETITIVE_GENERATOR_H
