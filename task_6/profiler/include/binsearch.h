#ifndef MIPT2024_S_KOSHELEV_A_ALGO_BINSEARCH_H
#define MIPT2024_S_KOSHELEV_A_ALGO_BINSEARCH_H

template <class T> T *binsearch(T **array, int begin, int end, T &element, int (*Compare)(const T *, const T *))
{
    if (end >= begin)
    {
        int mid = begin + (end - begin) / 2;
        int compare = Compare(array[mid], &element);

        if (compare == 0)
        {
            return array[mid];
        }
        else if (compare < 0)
        {
            return binsearch(array, begin, mid - 1, element, Compare);
        }
        else
        {
            return binsearch(array, mid + 1, end, element, Compare);
        }
    }
    else
    {
        return nullptr;
    }
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_BINSEARCH_H
