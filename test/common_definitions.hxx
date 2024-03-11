#ifndef TEST_COMMON_DEFINITIONS_HXX
#define TEST_COMMON_DEFINITIONS_HXX

#include <cstddef>
#include <string>

#define test_size 10

struct TestStruct
{
    size_t number_ = 1000L;
    std::string string_ = "I am string";

    static int Compare(const TestStruct *lhs, const TestStruct *rhs)
    {
        return (rhs->number_ - lhs->number_ == 0) ? lhs->string_.compare(rhs->string_) : rhs->number_ - lhs->number_;
    }

    static unsigned int Hash(const TestStruct *it)
    {
        return it->number_ + std::hash<std::string>()(it->string_);
    }
};

#endif // TEST_COMMON_DEFINITIONS_HXX
