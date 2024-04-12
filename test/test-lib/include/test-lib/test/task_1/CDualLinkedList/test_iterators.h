#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_ITERATORS_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_DUAL_ITERATORS_H

#include <cstddef>
#include <doctest/doctest.h>

#include "list-lib/list.h"
#include "test-lib/common.h"

TEST_SUITE("Task1_CDualLinkedList_TestIterators")
{
    TEST_CASE_TEMPLATE("TestIsValidForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE_TEMPLATE("TestIsValidBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE_TEMPLATE("TestDataCorrectnessGetDataForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getData(), data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestDataCorrectnessGetDataBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(iter.getData(), data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE_TEMPLATE("TestDataCorrectnessAsteriskForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(*iter, data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestDataCorrectnessAsteriskBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(*iter, data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE_TEMPLATE("TestDataCorrectnessGetLeafForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getLeaf()->data, data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestDataCorrectnessGetLeafBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(iter.getLeaf()->data, data[TEST_SIZE - i - 1]);
        }
    }

    TEST_CASE_TEMPLATE("TestEraseFromBeginForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        list.pushFront(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE_TEMPLATE("TestEraseFromBeginBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

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

    TEST_CASE_TEMPLATE("TestEraseFromMiddleForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

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

    TEST_CASE_TEMPLATE("TestEraseFromMiddleBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

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

    TEST_CASE_TEMPLATE("TestEraseFromEndForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

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

    TEST_CASE_TEMPLATE("TestEraseFromEndBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        list.pushBack(data[0]);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE_TEMPLATE("TestEraseAllBeginForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

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

    TEST_CASE_TEMPLATE("TestEraseAllEndForward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.begin();

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

    TEST_CASE_TEMPLATE("TestEraseAllBeginBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

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

    TEST_CASE_TEMPLATE("TestEraseAllEndBackward", T, TEST_LINKED_LIST_TYPES)
    {
        lab618::CDualLinkedList<T> list;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : data)
        {
            list.pushBack(it);
        }

        auto iter = list.end();

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
