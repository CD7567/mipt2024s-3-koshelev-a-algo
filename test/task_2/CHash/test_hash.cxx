#include "doctest/doctest.h"

#include "../../common_definitions.hxx"
#include "hash-lib/hash.h"

TEST_SUITE("Task2_TestHashMap")
{
    TEST_CASE("TestConstructAndTeardownEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);
    }

    TEST_CASE("TestAddNew")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE(hash_table.add(array + i));
        }

        delete[] array;
    }

    TEST_CASE("TestAddDuplicates")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE(hash_table.add(array + i));
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.add(array + i));
        }

        delete[] array;
    }

    TEST_CASE("TestFindEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), nullptr);
        }

        delete[] array;
    }

    TEST_CASE("TestFindExisting")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array + i);
        }

        delete[] array;
    }

    TEST_CASE("TestFindNonExistent")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];
        TestStruct non_existent = TestStruct(0, "I am not on table");

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(non_existent), nullptr);
        }

        delete[] array;
    }

    TEST_CASE("TestUpdateNew")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.update(array + i));
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array + i);
        }

        delete[] array;
    }

    TEST_CASE("TestUpdateDuplicates")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.update(array + i));
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE(hash_table.update(array + i));
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array + i);
        }

        delete[] array;
    }

    TEST_CASE("TestRemoveEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.remove(array[i]));
        }

        delete[] array;
    }

    TEST_CASE("TestRemoveNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE(hash_table.remove(array[i]));
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), nullptr);
        }

        delete[] array;
    }

    TEST_CASE("TestClearEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);
        hash_table.clear();
    }

    TEST_CASE("TestClearNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        hash_table.clear();

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), nullptr);
        }

        delete[] array;
    }

    TEST_CASE("TestValidityAfterClearEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);
        hash_table.clear();

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array + i);
        }

        delete[] array;
    }

    TEST_CASE("TestValidityAfterClearNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size);

        auto *array = new TestStruct[2 * test_size];

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            array[i].number_ = i;
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        hash_table.clear();

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            hash_table.add(array + i);
        }

        for (size_t i = 0; i < 2 * test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array + i);
        }

        delete[] array;
    }
}