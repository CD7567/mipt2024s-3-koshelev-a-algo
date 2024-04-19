#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_AUTO_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_AUTO_H

#include <array>
#include <doctest/doctest.h>

#include "memory-lib/mm.h"
#include "test-lib/common.h"

TEST_SUITE("TestMemoryManagerAuto")
{
    TEST_CASE_TEMPLATE("TestConstructAndTeardownEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
    }

    TEST_CASE_TEMPLATE("TestAddNewObject", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> ptr_array;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
            REQUIRE_NE(it, nullptr);
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_NOTHROW(*ptr_array[i] = data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestDeleteNullptrFromEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);

        REQUIRE_FALSE(mm.deleteObject(nullptr));
    }

    TEST_CASE_TEMPLATE("TestDeleteNonExistentFromEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        auto data = RandomGenerator<T, 1>().generate();

        REQUIRE_FALSE(mm.deleteObject(data.data()));
    }

    TEST_CASE_TEMPLATE("TestDeleteNullptrNonEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> ptr_array;

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        REQUIRE_FALSE(mm.deleteObject(nullptr));
    }

    TEST_CASE_TEMPLATE("TestDeleteNonExistentNonEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> ptr_array;
        auto nonExistent = RandomGenerator<T, 1>().generate();

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        REQUIRE_FALSE(mm.deleteObject(nonExistent.data()));
    }

    TEST_CASE_TEMPLATE("TestValidityAfterDelete", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> ptr_array;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_NOTHROW(*ptr_array[i] = data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestValidityAfterDeleteMixed", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> first_ptr_array;
        std::array<T *, TEST_SIZE> second_ptr_array;
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            first_ptr_array[i] = mm.newObject();
            second_ptr_array[i] = mm.newObject();
        }

        for (auto &it : second_ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        for (auto &it : second_ptr_array)
        {
            it = mm.newObject();
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_NOTHROW(*first_ptr_array[i] = data[i]);
            REQUIRE_NOTHROW(*second_ptr_array[i] = data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestValidityAfterClearEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> ptr_array;
        auto data = RandomGenerator<T>().generate();

        REQUIRE_NOTHROW(mm.clear());

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_NOTHROW(*ptr_array[i] = data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestValidityAfterClearNonEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> ptr_array;
        auto data = RandomGenerator<T>().generate();

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        REQUIRE_NOTHROW(mm.clear());

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_NOTHROW(*ptr_array[i] = data[i]);
        }
    }

    TEST_CASE_TEMPLATE("TestValidityAfterClearPartiallyEmpty", T, TEST_MEMORY_MANAGER_TYPES)
    {
        lab618::CMemoryManager<T> mm(TEST_SIZE / 2, true);
        std::array<T *, TEST_SIZE> first_ptr_array;
        std::array<T *, TEST_SIZE> second_ptr_array;
        auto data = RandomGenerator<T>().generate();

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            first_ptr_array[i] = mm.newObject();
            second_ptr_array[i] = mm.newObject();
        }

        for (auto &it : second_ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        REQUIRE_NOTHROW(mm.clear());

        for (auto &it : first_ptr_array)
        {
            it = mm.newObject();
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE_NOTHROW(*first_ptr_array[i] = data[i]);
        }
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_AUTO_H
