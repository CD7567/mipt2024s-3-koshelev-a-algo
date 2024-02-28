#include "doctest/doctest.h"

#include "../common_definitions.hxx"
#include "list-lib/list.h"

TEST_SUITE("Task1_TestDataManipulation")
{
    TEST_CASE("TestPushBackSize")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushBack(str);
        }
    }

    TEST_CASE("TestPushFrontSize")
    {
        lab618::CSingleLinkedList<TestStruct> list;
        TestStruct str{};

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(list.getSize(), i);
            list.pushFront(str);
        }
    }

    TEST_CASE("TestPushBackPop")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(list.getSize(), test_size - i);

            TestStruct str = list.popFront();
            REQUIRE_EQ(str.number_, i);
        }
    }

    TEST_CASE("TestPushFrontPop")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(list.getSize(), test_size - i);

            TestStruct str = list.popFront();
            REQUIRE_EQ(str.number_, test_size - i - 1);
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

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * test_size);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);
    }

    TEST_CASE("TestValidityAfterClear")
    {
        lab618::CSingleLinkedList<TestStruct> list;

        REQUIRE_EQ(list.getSize(), 0L);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * test_size);
        REQUIRE_NOTHROW(list.clear());
        REQUIRE_EQ(list.getSize(), 0L);

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushBack(str);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            TestStruct str{i};
            list.pushFront(str);
        }

        REQUIRE_EQ(list.getSize(), 2 * test_size);
    }
}