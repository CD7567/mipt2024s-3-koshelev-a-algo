#ifndef MIPT2024_S_KOSHELEV_A_ALGO_RANDOM_GENERATOR_H
#define MIPT2024_S_KOSHELEV_A_ALGO_RANDOM_GENERATOR_H

#include <array>
#include <cstddef>

#include "test-lib/common.h"
#include "test-lib/data/generators/inline_generators.h"

/**
 * Генератор случайного набора данных
 * @tparam T Тип данных
 * @tparam Size Размер набора
 */
template <typename T, size_t Size = TEST_SIZE> class RandomGenerator
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
template <size_t Size> class RandomGenerator<size_t, Size>
{
  public:
    std::array<size_t, Size> generate()
    {
        std::array<size_t, Size> array;

        for (auto &it : array)
        {
            it = genRandomReal();
        }

        return array;
    }
};

/**
 * Специализация для типа TestStruct
 * @tparam Size Размер набора
 */
template <size_t Size> class RandomGenerator<TestStruct, Size>
{
  public:
    std::array<TestStruct, Size> generate()
    {
        std::array<TestStruct, Size> array;

        for (auto &it : array)
        {
            it.number_ = genRandomReal();
            it.string_ = genRandomString(TEST_STRING_SIZE);
        }

        return array;
    }
};

/**
 * Специализация для типа TestStructInverted
 * @tparam Size Размер набора
 */
template <size_t Size> class RandomGenerator<TestStructInverted, Size>
{
  public:
    std::array<TestStructInverted, Size> generate()
    {
        std::array<TestStructInverted, Size> array;

        for (auto &it : array)
        {
            it.number_ = genRandomReal();
            it.string_ = genRandomString(TEST_STRING_SIZE);
        }

        return array;
    }
};

#endif // MIPT2024_S_KOSHELEV_A_ALGO_RANDOM_GENERATOR_H
