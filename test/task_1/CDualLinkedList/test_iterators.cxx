#include "doctest/doctest.h"

#include "../../common_definitions.hxx"
#include "list-lib/list.h"

TEST_SUITE("Task1_CDualLinkedList_TestIterators")
{
    TEST_CASE("TestIsValidForward")
    {
        lab618::CDualLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            list.pushBack(str);
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
        TestStruct str{};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            list.pushBack(str);
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

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getData().number_, i);
        }
    }

    TEST_CASE("TestDataCorrectnessGetDataBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(iter.getData().number_, TEST_SIZE - i - 1);
        }
    }

    TEST_CASE("TestDataCorrectnessAsteriskForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ((*iter).number_, i);
        }
    }

    TEST_CASE("TestDataCorrectnessAsteriskBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ((*iter).number_, TEST_SIZE - i - 1);
        }
    }

    TEST_CASE("TestDataCorrectnessGetLeafForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < TEST_SIZE; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getLeaf()->data.number_, i);
        }
    }

    TEST_CASE("TestDataCorrectnessGetLeafBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 0; i < TEST_SIZE; ++i, --iter)
        {
            REQUIRE_EQ(iter.getLeaf()->data.number_, TEST_SIZE - i - 1);
        }
    }

    TEST_CASE("TestEraseFromBeginForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushFront(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestEraseFromBeginBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 1; i < TEST_SIZE; ++i, --iter)
        {
        }

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushFront(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromMiddleForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseFromMiddleBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 1; i < TEST_SIZE / 2; ++i, --iter)
        {
        }

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushBack(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromEndForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseFromEndBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        list.eraseAndNext(iter);

        REQUIRE_EQ(list.getSize(), TEST_SIZE - 1);
        REQUIRE_FALSE(iter.isValid());

        TestStruct str{TEST_SIZE};
        list.pushBack(str);

        REQUIRE_EQ(list.getSize(), TEST_SIZE);
        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestEraseAllBeginForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseAllEndForward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.begin();

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

    TEST_CASE("TestEraseAllBeginBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = 1; i < TEST_SIZE; ++i, --iter)
        {
        }

        for (size_t i = TEST_SIZE; i > 0; --i, list.eraseAndNext(iter))
        {
            REQUIRE_EQ(iter.getData().number_, TEST_SIZE - i);
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

    TEST_CASE("TestEraseAllEndBackward")
    {
        lab618::CDualLinkedList<TestStruct> list;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CDualLinkedList<TestStruct>::CIterator iter = list.end();

        for (size_t i = TEST_SIZE; i > 0; --i, list.eraseAndNext(iter), --iter)
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
