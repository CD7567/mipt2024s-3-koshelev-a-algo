#include "generate.h"

DataStruct *generateRandomStructs(size_t size)
{
    auto array = new DataStruct[size];

    for (size_t i = 0; i < size; ++i)
    {
        array[i].first_ = genRandomString(genRandomReal(MIN_LENGTH, MAX_LENGTH));
        array[i].second_ = genRandomString(genRandomReal(MIN_LENGTH, MAX_LENGTH));
    }

    return array;
}
