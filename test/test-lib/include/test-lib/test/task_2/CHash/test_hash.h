#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_HASH_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_HASH_H

#include <doctest/doctest.h>

#include "hash-lib/hash.h"
#include "test-lib/common.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("Task2_TestHashMap")
{
    TEST_CASE("TestConstructAndTeardownEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
    }

    TEST_CASE("TestAddNew")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(hash_table.add(data.data() + i));
        }
    }

    TEST_CASE("TestAddDuplicates")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(hash_table.add(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.add(data.data() + i));
        }
    }

    TEST_CASE("TestFindEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), nullptr);
        }
    }

    TEST_CASE("TestFindExisting")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE("TestFindNonExistent")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();
        TestStruct non_existent = TestStruct{TEST_SIZE, "I am string"};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(non_existent), nullptr);
        }
    }

    TEST_CASE("TestUpdateNew")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE("TestUpdateDuplicates")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(hash_table.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE("TestRemoveEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.remove(data[i]));
        }
    }

    TEST_CASE("TestRemoveNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(hash_table.remove(data[i]));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), nullptr);
        }
    }

    TEST_CASE("TestClearEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        hash_table.clear();
    }

    TEST_CASE("TestClearNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        hash_table.clear();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), nullptr);
        }
    }

    TEST_CASE("TestValidityAfterClearEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        hash_table.clear();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE("TestValidityAfterClearNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(TEST_SIZE / 2);
        auto data = RandomGenerator<TestStruct>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        hash_table.clear();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_HASH_H
