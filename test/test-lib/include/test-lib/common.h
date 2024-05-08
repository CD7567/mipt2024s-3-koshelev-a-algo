#ifndef MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H
#define MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H

#include "test-lib/data/test_struct.h"
#include "test-lib/data/test_struct_inverted.h"

#define TEST_SIZE 10
#define TEST_STRING_SIZE 20

#define TEST_LINKED_LIST_TYPES size_t, TestStruct
#define TEST_HASH_TYPES TestStruct, TestStructInverted
#define TEST_MEMORY_MANAGER_TYPES size_t, TestStruct, TestStructInverted
#define TEST_SORT_TYPES TestStruct, TestStructInverted

#endif // MIPT2024_S_KOSHELEV_A_ALGO_COMMON_H
