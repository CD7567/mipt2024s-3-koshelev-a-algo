#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_QUICK_SORT_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_QUICK_SORT_H

#include <doctest/doctest.h>

#include "sort-lib/sort.h"
#include "test-lib/common.h"
#include "test-lib/data/generators/repetitive_generator.h"
#include "test-lib/data/generators/sorted_generator.h"
#include "test-lib/data/generators/random_generator.h"

TEST_SUITE("TestQuickSort")
{
    TEST_CASE_TEMPLATE("TestCorrectnessOnSortedAsc", T, TEST_SORT_TYPES)
    {
        auto array = SortedGenerator<T>().generate();
        auto ptrArray = std::array<T *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::quickSort(ptrArray.data(), TEST_SIZE, T::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(T::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE_TEMPLATE("TestCorrectnessOnSortedDesc", T, TEST_SORT_TYPES)
    {
        auto array = SortedGenerator<T>().generate();
        auto ptrArray = std::array<T *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + TEST_SIZE - i - 1;
        }

        templates::quickSort(ptrArray.data(), TEST_SIZE, T::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(T::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE_TEMPLATE("TestCorrectnessOnRepetitiveAsc", T, TEST_SORT_TYPES)
    {
        auto array = RepetitiveGenerator<T>().generate();
        auto ptrArray = std::array<T *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::quickSort(ptrArray.data(), TEST_SIZE, T::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(T::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE_TEMPLATE("TestCorrectnessOnRepetitiveDesc", T, TEST_SORT_TYPES)
    {
        auto array = RepetitiveGenerator<T>().generate();
        auto ptrArray = std::array<T *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + TEST_SIZE - i - 1;
        }

        templates::quickSort(ptrArray.data(), TEST_SIZE, T::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(T::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE_TEMPLATE("TestCorrectnessOnRandom", T, TEST_SORT_TYPES)
    {
        auto array = RandomGenerator<T>().generate();
        auto ptrArray = std::array<T *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::quickSort(ptrArray.data(), TEST_SIZE, T::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(T::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_QUICK_SORT_H
