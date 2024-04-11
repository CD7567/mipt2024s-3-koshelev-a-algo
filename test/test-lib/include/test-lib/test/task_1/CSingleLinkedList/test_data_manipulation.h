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
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushBack(str);
        }
    }

    TEST_CASE("TestPushFrontSize")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushFront(str);
        }
    }

    TEST_CASE("TestPushBackPop")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);

            TestStruct str = list.popFront();
            REQUIRE_EQ(str.number_, i);
        }
    }

    TEST_CASE("TestPushFrontPop")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);

            TestStruct str = list.popFront();
            REQUIRE_EQ(str.number_, TEST_SIZE - i - 1);
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

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE("TestValidityAfterClear")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_DATA_MANIPULATION_H
