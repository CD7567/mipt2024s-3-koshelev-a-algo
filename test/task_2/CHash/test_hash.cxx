#include "doctest/doctest.h"

#include "../../common_definitions.hxx"
#include "hash-lib/hash.h"

TEST_SUITE("Task2_TestHashMap")
{
    TEST_CASE("TestConstructAndTeardownEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
    }

    TEST_CASE("TestAddNew")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE(hash_table.add(array.data() + i));
        }
    }

    TEST_CASE("TestAddDuplicates")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE(hash_table.add(array.data() + i));
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.add(array.data() + i));
        }
    }

    TEST_CASE("TestFindEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), nullptr);
        }
    }

    TEST_CASE("TestFindExisting")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array.data() + i);
        }
    }

    TEST_CASE("TestFindNonExistent")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genSortedData<test_size>();
        TestStruct non_existent = TestStruct{test_size + 1, "I am string"};

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(non_existent), nullptr);
        }
    }

    TEST_CASE("TestUpdateNew")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.update(array.data() + i));
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array.data() + i);
        }
    }

    TEST_CASE("TestUpdateDuplicates")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.update(array.data() + i));
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE(hash_table.update(array.data() + i));
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array.data() + i);
        }
    }

    TEST_CASE("TestRemoveEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_FALSE(hash_table.remove(array[i]));
        }
    }

    TEST_CASE("TestRemoveNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE(hash_table.remove(array[i]));
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), nullptr);
        }
    }

    TEST_CASE("TestClearEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        hash_table.clear();
    }

    TEST_CASE("TestClearNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        hash_table.clear();

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), nullptr);
        }
    }

    TEST_CASE("TestValidityAfterClearEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        hash_table.clear();

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array.data() + i);
        }
    }

    TEST_CASE("TestValidityAfterClearNonEmpty")
    {
        lab618::CHash<TestStruct, TestStruct::Hash, TestStruct::Compare> hash_table(test_size / 2);
        auto array = genFullRandomData<test_size>();

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        hash_table.clear();

        for (size_t i = 0; i < test_size; ++i)
        {
            hash_table.add(array.data() + i);
        }

        for (size_t i = 0; i < test_size; ++i)
        {
            REQUIRE_EQ(hash_table.find(array[i]), array.data() + i);
        }
    }
}
