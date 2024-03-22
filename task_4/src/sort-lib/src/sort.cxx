#include "sort-lib/sort.h"

#include <algorithm>

namespace templates
{

/**
 * Проверить и установить инвариант кучи по максимуму в поддереве с индекса idx
 * @param ppArray Сортируемый массив
 * @param length Длина массива
 * @param idx Индекс корня поддерева
 * @param pCompareFunc Компаратор
 */
inline void heapify(void **ppArray, int length, int idx, CompareSortType pCompareFunc)
{
    const int lChild = 2 * idx + 1;
    const int rChild = lChild + 1;
    int largest = idx;

    if (lChild < length && pCompareFunc(ppArray[lChild], ppArray[largest]) > 0)
    {
        largest = lChild;
    }

    if (rChild < length && pCompareFunc(ppArray[rChild], ppArray[largest]) > 0)
    {
        largest = rChild;
    }

    if (largest != idx)
    {
        std::swap(ppArray[idx], ppArray[largest]);
        heapify(ppArray, length, largest, pCompareFunc);
    }
}

void heapSort(void **ppArray, int length, CompareSortType pCompareFunc)
{
    // Построение исходной кучи
    for (int i = length / 2 - 1; i >= 0; --i)
    {
        heapify(ppArray, length, i, pCompareFunc);
    }

    for (int i = length - 1; i > 0; --i)
    {
        std::swap(ppArray[0], ppArray[i]);
        heapify(ppArray, i, 0, pCompareFunc);
    }
}

/**
 * Функция сортировки слиянием. Реализована in-place версия алгоритма, где merge происходит между разными кусками
 * исходного массива.
 * @param ppArray Сортируемый массив
 * @param length Длина массива
 * @param pCompareFunc Компаратор
 */
void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc)
{
    if (length < 2)
    {
        return;
    }

    const int middle = length / 2;

    mergeSort(ppArray, middle, pCompareFunc);
    mergeSort(ppArray + middle, length - middle, pCompareFunc);

    void **ppMiddle = ppArray + middle;
    void **ppEnd = ppArray + length;
    for (void **it = ppMiddle; ppArray < it && it < ppEnd; ++ppArray)
    {
        if (pCompareFunc(*ppArray, *it) > 0)
        {
            for (void **tmp = it; tmp > ppArray; --tmp)
            {
                std::swap(*tmp, *(tmp - 1));
            }
            ++it;
        }
    }
}

} // namespace templates