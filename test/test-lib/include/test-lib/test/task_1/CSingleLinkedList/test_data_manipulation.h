#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_DATA_MANIPULATION_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_DATA_MANIPULATION_H

#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("Task1_CSingleLinkedList_TestDataManipulation")
{
    TEST_CASE("TestPushBackSize")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushBack(data[i]);
        }
    }

    TEST_CASE("TestPushFrontSize")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushFront(data[i]);
        }
    }

    TEST_CASE("TestPushBackPop")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);
            REQUIRE_EQ(list.popFront(), data[i]);
        }
    }

    TEST_CASE("TestPushFrontPop")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushFront(it);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);
            REQUIRE_EQ(list.popFront(), data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE("TestClearEmpty")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE("TestClear")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (auto &it : data)
        {
            list.pushFront(it);
            list.pushBack(it);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE("TestValidityAfterClear")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (auto &it : data)
        {
            list.pushFront(it);
            list.pushBack(it);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (auto &it : data)
        {
            list.pushFront(it);
            list.pushBack(it);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_DATA_MANIPULATION_H
