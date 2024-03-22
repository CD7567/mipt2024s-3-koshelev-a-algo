#include "doctest/doctest.h"

#include "../common_definitions.hxx"
#include "sort-lib/sort.h"

TEST_SUITE("TestHeapSort")
{
    TEST_CASE("TestCorrectnessOnSorted")
    {
        auto array = genSortedData<test_size>();
        auto ptrArray = std::array<TestStruct *, test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), test_size, TestStruct::Compare);

        for (size_t i = 1; i < test_size; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE("TestCorrectnessOnReverseWithRepetition")
    {
        auto array = genSortedDescData<test_size>(test_size / 5);
        auto ptrArray = std::array<TestStruct *, test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), test_size, TestStruct::Compare);

        for (size_t i = 1; i < test_size; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE("TestCorrectnessOnRandomNum")
    {
        auto array = genRandomNumData<test_size>();
        auto ptrArray = std::array<TestStruct *, test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), test_size, TestStruct::Compare);

        for (size_t i = 1; i < test_size; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }

    TEST_CASE("TestCorrectnessOnFullyRandom")
    {
        auto array = genFullRandomData<test_size>();
        auto ptrArray = std::array<TestStruct *, test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            ptrArray[i] = array.data() + i;
        }

        templates::heapSort(ptrArray.data(), test_size, TestStruct::Compare);

        for (size_t i = 1; i < test_size; ++i)
        {
            REQUIRE_LE(TestStruct::Compare(ptrArray[i - 1], ptrArray[i]), 0);
        }
    }
}