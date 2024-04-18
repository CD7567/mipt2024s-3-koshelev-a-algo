#include "test-lib/data/test_struct.h"

TestStruct::TestStruct(size_t num, std::string &&str) : number_(num), string_(str)
{
}

bool TestStruct::operator==(const TestStruct &other) const
{
    return Compare(this, &other) == 0;
}

int TestStruct::Compare(const TestStruct *lhs, const TestStruct *rhs)
{
    size_t max_num = std::max(lhs->number_, rhs->number_);
    return (rhs->number_ == lhs->number_) ? lhs->string_.compare(rhs->string_)
                                          : (int)(max_num == rhs->number_) - (int)(max_num == lhs->number_);
}

unsigned int TestStruct::Hash(const TestStruct *it)
{
    return it->number_ + std::hash<std::string>()(it->string_);
}
