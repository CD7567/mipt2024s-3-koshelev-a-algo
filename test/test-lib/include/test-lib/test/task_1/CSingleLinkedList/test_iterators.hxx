#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_ITERATORS_HXX
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_ITERATORS_HXX

#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.hxx"

TEST_SUITE("Task1_CSingleLinkedList_TestIterators")
{
    TEST_CASE("TestIsValid")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestDataCorrectnessGetData")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getData().number_, i);
        }
    }

    TEST_CASE("TestDataCorrectnessAsterisk")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ((*iter).number_, i);
        }
    }

    TEST_CASE("TestEraseFromEnd")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < TEST_SIZE; ++i, ++iter)
        {
        }

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushBack(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromMiddle")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < TEST_SIZE / 2; ++i, ++iter)
        {
        }

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushBack(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromBegin")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushFront(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestEraseAllBegin")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, list.erase(iter), ++iter)
        {
            REQUIRE_EQ(iter.getData().number_, i);
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        REQUIRE_EQ(list.getSize(), TEST_SIZE);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }

    TEST_CASE("TestEraseAllEnd")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < TEST_SIZE; ++i, ++iter)
        {
        }

        for (size_t i = TEST_SIZE; i > 0; --i, list.erase(iter))
        {
            REQUIRE_EQ(iter.getData().number_, i - 1);
            REQUIRE_EQ(list.getSize(), i);
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        REQUIRE_EQ(list.getSize(), TEST_SIZE);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_ITERATORS_HXX
