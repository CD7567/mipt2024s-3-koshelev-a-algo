#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_HEAP_SORT_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_HEAP_SORT_H

#include <doctest/doctest.h>

#include "sort-lib/sort.h"
#include "test-lib/common.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("TestHeapSort")
{
    TEST_CASE("TestCorrectnessOnSorted")
    {
        auto array = genSortedData<TEST_SIZE>();
        auto ptrArray = std::array<TestStruct *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), TEST_SIZE, TestStruct::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE("TestCorrectnessOnReverseWithRepetition")
    {
        auto array = genSortedDescData<TEST_SIZE>(TEST_SIZE / 5);
        auto ptrArray = std::array<TestStruct *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), TEST_SIZE, TestStruct::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE("TestCorrectnessOnRandomNum")
    {
        auto array = genRandomNumData<TEST_SIZE>();
        auto ptrArray = std::array<TestStruct *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), TEST_SIZE, TestStruct::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE("TestCorrectnessOnFullyRandom")
    {
        auto array = genFullRandomData<TEST_SIZE>();
        auto ptrArray = std::array<TestStruct *, TEST_SIZE>();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), TEST_SIZE, TestStruct::Compare);

        for (size_t i = 1; i < TEST_SIZE; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_HEAP_SORT_H
