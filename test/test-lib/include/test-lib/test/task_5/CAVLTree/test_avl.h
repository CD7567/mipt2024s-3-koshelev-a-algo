#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_AVL_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_AVL_H

#include <doctest/doctest.h>

#include "avl-lib/avltree.h"
#include "test-lib/common.h"
#include "test-lib/data/generators/random_generator.h"
#include "test-lib/data/generators/sorted_generator.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("TestAVL")
{
    TEST_CASE_TEMPLATE("TestConstructAndTeardownEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare>(TEST_SIZE);
    }

    TEST_CASE_TEMPLATE("TestAddNew", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(avl.add(data.data() + TEST_SIZE - i - 1));
        }
    }

    TEST_CASE_TEMPLATE("TestAddDuplicates", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(avl.add(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(avl.add(data.data() + i));
        }
    }

    TEST_CASE_TEMPLATE("TestFindEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), nullptr);
        }
    }

    TEST_CASE_TEMPLATE("TestFindExisting", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE_TEMPLATE("TestFindNonExistent", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();
        T non_existent = T{TEST_SIZE, "I am string"};

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(non_existent), nullptr);
        }
    }

    TEST_CASE_TEMPLATE("TestUpdateNew", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(avl.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE_TEMPLATE("TestUpdateDuplicates", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(avl.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(avl.update(data.data() + i));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE_TEMPLATE("TestRemoveEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_FALSE(avl.remove(data[i]));
        }
    }

    TEST_CASE_TEMPLATE("TestRemoveNonEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(avl.remove(data[i]));
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), nullptr);
        }
    }

    TEST_CASE_TEMPLATE("TestClearEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        avl.clear();
    }

    TEST_CASE_TEMPLATE("TestClearNonEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        avl.clear();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), nullptr);
        }
    }

    TEST_CASE_TEMPLATE("TestValidityAfterClearEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        avl.clear();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), data.data() + i);
        }
    }

    TEST_CASE_TEMPLATE("TestValidityAfterClearNonEmpty", T, TEST_AVL_TYPES)
    {
        lab618::CAVLTree<T, T::Compare> avl(TEST_SIZE);
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        avl.clear();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            avl.add(data.data() + i);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_EQ(avl.find(data[i]), data.data() + i);
        }
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_AVL_H
