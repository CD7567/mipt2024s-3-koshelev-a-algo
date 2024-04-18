#ifndef MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_MANUAL_H
#define MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_MANUAL_H

#include <array>
#include <doctest/doctest.h>

#include "memory-lib/mm.h"
#include "test-lib/common.h"
#include "test-lib/data/test_struct.h"

TEST_SUITE("TestMemoryManagerManual")
{
    TEST_CASE("TestConstructAndTeardownEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
    }

    TEST_CASE("TestAddNewObject")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> ptr_array;

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
            REQUIRE_NE(it, nullptr);
        }

        for (auto &it : ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }
    }

    TEST_CASE("TestDeleteNullptrFromEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);

        REQUIRE_FALSE(mm.deleteObject(nullptr));
    }

    TEST_CASE("TestDeleteNonExistentFromEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        TestStruct *nonExistent = new TestStruct();

        REQUIRE_FALSE(mm.deleteObject(nonExistent));

        delete nonExistent;
    }

    TEST_CASE("TestDeleteNullptrNonEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> ptr_array;

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        REQUIRE_FALSE(mm.deleteObject(nullptr));

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }
    }

    TEST_CASE("TestDeleteNonExistentNonEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> ptr_array;
        TestStruct *nonExistent = new TestStruct();

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        REQUIRE_FALSE(mm.deleteObject(nonExistent));

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        delete nonExistent;
    }

    TEST_CASE("TestValidityAfterDelete")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> ptr_array;

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

        for (auto &it : ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }
    }

    TEST_CASE("TestValidityAfterDeleteMixed")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> first_ptr_array;
        std::array<TestStruct *, TEST_SIZE> second_ptr_array;

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
            REQUIRE_NOTHROW(first_ptr_array[i]->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(second_ptr_array[i]->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(first_ptr_array[i]->string_ = "I am new string");
            REQUIRE_NOTHROW(second_ptr_array[i]->string_ = "I am new string");
        }

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            REQUIRE(mm.deleteObject(first_ptr_array[i]));
            REQUIRE(mm.deleteObject(second_ptr_array[i]));
        }
    }

    TEST_CASE("TestValidityAfterClearEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> ptr_array;

        REQUIRE_NOTHROW(mm.clear());

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        for (auto &it : ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }
    }

    TEST_CASE("TestValidityAfterClearNonEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> ptr_array;

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        REQUIRE_THROWS_AS(mm.clear(), lab618::CMemoryManager<TestStruct>::CException);

        for (auto &it : ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        REQUIRE_NOTHROW(mm.clear());

        for (auto &it : ptr_array)
        {
            it = mm.newObject();
        }

        for (auto &it : ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }
    }

    TEST_CASE("TestValidityAfterClearPartiallyEmpty")
    {
        lab618::CMemoryManager<TestStruct> mm(TEST_SIZE / 2);
        std::array<TestStruct *, TEST_SIZE> first_ptr_array;
        std::array<TestStruct *, TEST_SIZE> second_ptr_array;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            first_ptr_array[i] = mm.newObject();
            second_ptr_array[i] = mm.newObject();
        }

        for (auto &it : second_ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        REQUIRE_THROWS_AS(mm.clear(), lab618::CMemoryManager<TestStruct>::CException);

        for (auto &it : first_ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : first_ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }

        REQUIRE_NOTHROW(mm.clear());

        for (auto &it : first_ptr_array)
        {
            it = mm.newObject();
        }

        for (auto &it : first_ptr_array)
        {
            REQUIRE_NOTHROW(it->number_ = TEST_SIZE);
            REQUIRE_NOTHROW(it->string_ = "I am new string");
        }

        for (auto &it : first_ptr_array)
        {
            REQUIRE(mm.deleteObject(it));
        }
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_TEST_MM_MANUAL_H
