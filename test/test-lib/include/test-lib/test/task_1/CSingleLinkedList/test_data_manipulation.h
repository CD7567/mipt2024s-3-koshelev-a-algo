#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_DATA_MANIPULATION_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_DATA_MANIPULATION_H

#include <cstddef>
#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.h"

TEST_SUITE("Task1_CSingleLinkedList_TestDataManipulation")
{
    TEST_CASE_TEMPLATE("TestPushBackSize", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushBack(data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestPushFrontSize", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushFront(data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestPushBackPop", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestPushFrontPop", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestClearEmpty", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;

        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE_TEMPLATE("TestClear", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestValidityAfterClear", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CSingleLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

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
