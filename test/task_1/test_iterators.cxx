#include "doctest/doctest.h"

#include "../common_definitions.hxx"
#include "single-list-lib/list.h"

TEST_SUITE("Task1_TestIterators") {
    TEST_CASE("TestIsValid") {
        lab618::CSingleLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < test_size; ++i)
        {
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < test_size; ++i, ++iter)
        {
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());
    }

    TEST_CASE("TestDataCorrectness") {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 0; i < test_size; ++i, ++iter)
        {
            REQUIRE_EQ(iter.getData().number_, i);
        }
    }

    TEST_CASE("TestEraseFromEnd") {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < test_size; ++i, ++iter)
        {
        }

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), test_size - 1);
        REQUIRE(iter.isValid());

        TestStruct str{test_size};
        list.pushBack(str);

        REQUIRE_EQ(list.getSize(), test_size);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromMiddle") {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < test_size / 2; ++i, ++iter)
        {
        }

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), test_size - 1);
        REQUIRE(iter.isValid());

        TestStruct str{test_size};
        list.pushBack(str);

        REQUIRE_EQ(list.getSize(), test_size);
        REQUIRE(iter.isValid());
    }

    TEST_CASE("TestEraseFromBegin") {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        list.erase(iter);

        REQUIRE_EQ(list.getSize(), test_size - 1);
        REQUIRE_FALSE(iter.isValid());

        TestStruct str{test_size};
        list.pushFront(str);

        REQUIRE_EQ(list.getSize(), test_size);
        REQUIRE_FALSE(iter.isValid());
    }


    TEST_CASE("TestEraseAll") {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        lab618::CSingleLinkedList<TestStruct>::CIterator iter = list.begin();

        for (size_t i = 1; i < test_size; ++i, ++iter)
        {
        }

        for (size_t i = test_size; i > 0; --i, list.erase(iter)) {
            REQUIRE_EQ(iter.getData().number_, i - 1);
            REQUIRE_EQ(list.getSize(), i);
            REQUIRE(iter.isValid());
        }

        REQUIRE_FALSE(iter.isValid());

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        REQUIRE_EQ(list.getSize(), test_size);

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * test_size);
    }
}