#include "data_struct.h"

DataStruct::DataStruct(std::string &&first, std::string &&second) : first_(first), second_(second)
{
}

bool DataStruct::operator==(const DataStruct &other) const
{
    return (first_ == other.first_) && (second_ == other.second_);
}

int DataStruct::Compare(const DataStruct *lhs, const DataStruct *rhs)
{
    return lhs->first_.compare(rhs->first_) == 0 ? lhs->first_.compare(rhs->first_)
                                                 : lhs->second_.compare(rhs->second_);
}

unsigned int DataStruct::Hash(const DataStruct *it)
{
    return std::hash<std::string>()(it->first_) + std::hash<std::string>()(it->second_);
}
