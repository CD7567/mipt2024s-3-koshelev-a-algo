#include "test-lib/data/test_struct_inverted.h"

TestStructInverted::TestStructInverted(size_t num, std::string &&str)
{
}

bool TestStructInverted::operator==(const TestStructInverted &other) const
{
    return Compare(this, &other) == 0;
}

int TestStructInverted::Compare(const TestStructInverted *lhs, const TestStructInverted *rhs)
{
    size_t max_num = std::max(lhs->number_, rhs->number_);
    return (rhs->number_ == lhs->number_) ? lhs->string_.compare(rhs->string_)
                                          : (int)(max_num == rhs->number_) - (int)(max_num == lhs->number_);
}

unsigned int TestStructInverted::Hash(const TestStructInverted *it)
{
    return it->number_ + std::hash<std::string>()(it->string_);
}
