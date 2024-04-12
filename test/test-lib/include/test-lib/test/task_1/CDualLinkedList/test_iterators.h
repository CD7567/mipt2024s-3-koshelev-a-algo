#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_ITERATORS_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_ITERATORS_H

#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("Task1_CDualLinkedList_TestIterators")
{
    TEST_CASE("TestIsValidForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestIsValidBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestDataCorrectnessGetDataForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getData(), data[i]);
        }
    }

    TEST_CASE("TestDataCorrectnessGetDataBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(iter.getData(), data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE("TestDataCorrectnessAsteriskForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(*iter, data[i]);
        }
    }

    TEST_CASE("TestDataCorrectnessAsteriskBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(*iter, data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE("TestDataCorrectnessGetLeafForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getLeaf()->data, data[i]);
        }
    }

    TEST_CASE("TestDataCorrectnessGetLeafBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(iter.getLeaf()->data, data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE("TestEraseFromBeginForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        list.pushFront(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestEraseFromBeginBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 1; i < TEST_SIZE; ++i, --iter)
        {
        }

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        list.pushFront(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromMiddleForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseFromMiddleBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 1; i < TEST_SIZE / 2; ++i, --iter)
        {
        }

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        list.pushBack(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromEndForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseFromEndBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        list.pushBack(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestEraseAllBeginForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseAllEndForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseAllBeginBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 1; i < TEST_SIZE; ++i, --iter)
        {
        }

        for (size_t i = TEST_SIZE; i > 0; --i, list.eraseAndNext(iter))
        {
            REQUIRE_EQ(iter.getData(), data[TEST_SIZE - i]);
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

    TEST_CASE("TestEraseAllEndBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        auto data = RandomGenerator<TestStruct>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = TEST_SIZE; i > 0; --i, list.eraseAndNext(iter), --iter)
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

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_ITERATORS_H
