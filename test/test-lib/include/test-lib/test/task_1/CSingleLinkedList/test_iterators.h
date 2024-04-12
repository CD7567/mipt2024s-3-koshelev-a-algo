#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_ITERATORS_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_ITERATORS_H

#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("Task1_CSingleLinkedList_TestIterators")
{
    TEST_CASE("TestIsValid")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
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
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getData(), data[i]);
        }
    }

    TEST_CASE("TestDataCorrectnessAsterisk")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(*iter, data[i]);
        }
    }

    TEST_CASE("TestEraseFromEnd")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < TEST_SIZE; ++i, ++iter)
        {
        }

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        list.pushBack(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromMiddle")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < TEST_SIZE / 2; ++i, ++iter)
        {
        }

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        list.pushBack(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromBegin")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        list.pushFront(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestEraseAllBegin")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, list.erase(iter), ++iter)
        {
            REQUIRE_EQ(iter.getData(), data[i]);
            REQUIRE_EQ(list.getSize(), TEST_SIZE - i);
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        REQUIRE_EQ(list.getSize(), TEST_SIZE);

        for (auto &it : data)
        {
            list.pushFront(it);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }

    TEST_CASE("TestEraseAllEnd")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < TEST_SIZE; ++i, ++iter)
        {
        }

        for (size_t i = TEST_SIZE; i > 0; --i, list.erase(iter))
        {
            REQUIRE_EQ(iter.getData(), data[i - 1]);
            REQUIRE_EQ(list.getSize(), i);
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        REQUIRE_EQ(list.getSize(), TEST_SIZE);

        for (auto &it : data)
        {
            list.pushFront(it);
        }

        REQUIRE_EQ(list.getSize(), 2 * TEST_SIZE);
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_SINGLE_ITERATORS_H
