#ifndef TEST_COMMON_DEFINITIONS_HXX
#define TEST_COMMON_DEFINITIONS_HXX

#include <cstddef>
#include <string>

#define test_size 10

struct TestStruct {
    size_t number_ = 1000L;
    std::string string_ = "I am string";
};

#endif  // TEST_COMMON_DEFINITIONS_HXX
