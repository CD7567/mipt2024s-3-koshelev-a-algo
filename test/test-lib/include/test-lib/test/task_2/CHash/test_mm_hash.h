#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_HASH_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_HASH_H

#include <doctest/doctest.h>

#include "hash-lib/hash.h"
#include "test-lib/common.h"
#include "test-lib/data/generators/random_generator.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("Task2_TestMMHashMap")
{
    TEST_CASE_TEMPLATE("TestConstructAndTeardownEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
    }

    TEST_CASE_TEMPLATE("TestAddNew", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(hash_table.add(data.data() + i));
        }
    }

    TEST_CASE_TEMPLATE("TestAddDuplicates", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(hash_table.add(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.add(data.data() + i));
        }
    }

    TEST_CASE_TEMPLATE("TestFindEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), nullptr);
        }
    }

    TEST_CASE_TEMPLATE("TestFindExisting", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE_TEMPLATE("TestFindNonExistent", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();
        T non_existent = T{TEST_SIZE, "I am string"};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            hash_table.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(non_existent), nullptr);
        }
    }

    TEST_CASE_TEMPLATE("TestUpdateNew", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(hash_table.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE_TEMPLATE("TestUpdateDuplicates", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestRemoveEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(hash_table.remove(data[i]));
        }
    }

    TEST_CASE_TEMPLATE("TestRemoveNonEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestClearEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        hash_table.clear();
    }

    TEST_CASE_TEMPLATE("TestClearNonEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestValidityAfterClearEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

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

    TEST_CASE_TEMPLATE("TestValidityAfterClearNonEmpty", T, TEST_HASH_TYPES)
    {
        lab618::CHash<T, T::Hash, T::Compare> hash_table(TEST_SIZE / 2, 32);
        auto data = RandomGenerator<T>().generate();

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

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_HASH_H
