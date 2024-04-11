#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_DATA_MANIPULATION_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_DATA_MANIPULATION_H

#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.h"

TEST_SUITE("Task1_CDualLinkedList_TestDataManipulation")
{
    TEST_CASE("TestPushBackSize")
    {
        lab618::CDualLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushBack(str);
        }
    }

    TEST_CASE("TestPushFrontSize")
    {
        lab618::CDualLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushFront(str);
        }
    }

    TEST_CASE("TestPushBackPopFront")
    {
        lab618::CDualLinkedList<TestStruct> list;

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

    TEST_CASE("TestPushFrontPopFront")
    {
        lab618::CDualLinkedList<TestStruct> list;

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

    TEST_CASE("TestPushBackPopBack")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);

            TestStruct str = list.popBack();
            REQUIRE_EQ(str.number_, TEST_SIZE - i - 1);
        }
    }

    TEST_CASE("TestPushFrontPopBack")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);

            TestStruct str = list.popBack();
            REQUIRE_EQ(str.number_, i);
        }
    }

    TEST_CASE("TestMixedPushMixedPop")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
            list.pushBack(str);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(list.getSize(), 2 * (TEST_SIZE - i));

            TestStruct frontStr = list.popFront();
            TestStruct backStr = list.popBack();
            REQUIRE_EQ(frontStr.number_, TEST_SIZE - i - 1);
            REQUIRE_EQ(backStr.number_, TEST_SIZE - i - 1);
        }
    }

    TEST_CASE("TestClearEmpty")
    {
        lab618::CDualLinkedList<TestStruct> list;

        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE("TestClear")
    {
        lab618::CDualLinkedList<TestStruct> list;

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
            list.pushBack(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE("TestValidityAfterClear")
    {
        lab618::CDualLinkedList<TestStruct> list;

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
            list.pushBack(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
            list.pushBack(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_DATA_MANIPULATION_H
