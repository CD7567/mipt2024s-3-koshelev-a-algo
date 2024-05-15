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

    if (lChild < length && pCompareFunc(ppArray[lChild], ppArray[largest]) < 0)
    {
        largest = lChild;
    }

    if (rChild < length && pCompareFunc(ppArray[rChild], ppArray[largest]) < 0)
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
 * Функция слияния частей массива с дополнительной памятью
 * @param ppArrayBegin Начало сортируемой части
 * @param ppArrayMid Середина сортируемой части
 * @param ppArrayEnd Конец сортируемой части
 * @param pCompareFunc Компаратор
 */
void merge(void **ppArrayBegin, void **ppArrayMid, void **ppArrayEnd, CompareSortType pCompareFunc)
{
    void **l_iter = ppArrayBegin;
    void **r_iter = ppArrayMid;

    void **result = new void *[ppArrayEnd - ppArrayBegin];
    void **result_iter = result;

    while (l_iter < ppArrayMid && r_iter < ppArrayEnd)
    {
        if (pCompareFunc(*l_iter, *r_iter) >= 0)
        {
            *(result_iter++) = *(l_iter++);
        }
        else
        {
            *(result_iter++) = *(r_iter++);
        }
    }

    while (l_iter < ppArrayMid)
    {
        *(result_iter++) = *(l_iter++);
    }

    while (r_iter < ppArrayEnd)
    {
        *(result_iter++) = *(r_iter++);
    }

    std::copy(result, result + (ppArrayEnd - ppArrayBegin), ppArrayBegin);
    delete[] result;
}

void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc)
{
    for (int i = 1; i < length; i *= 2)
    {
        for (int j = 0; j < length - i; j += 2 * i)
        {
            merge(ppArray + j, ppArray + j + i, ppArray + std::min(j + 2 * i, length), pCompareFunc);
        }
    }
}

/**
 * Функция партиционирования быстрой сортировки
 * @param ppArrayBegin Начало сортируемого участка
 * @param ppArrayEnd Конец сортируемого участка (не включительно)
 * @param pCompareFunc Компаратор
 * @return Середина сортируемого участка
 */
void **partition(void **ppArrayBegin, void **ppArrayEnd, CompareSortType pCompareFunc)
{
    void **l_iter = ppArrayBegin;
    void **r_iter = ppArrayEnd - 1;
    void *pivot = *(ppArrayBegin + (r_iter - l_iter) / 2);

    while (l_iter <= r_iter)
    {
        for (; pCompareFunc(*l_iter, pivot) > 0; ++l_iter)
        {
        }

        for (; pCompareFunc(*r_iter, pivot) < 0; --r_iter)
        {
        }

        if (l_iter >= r_iter)
        {
            break;
        }

        std::swap(*(l_iter++), *(r_iter--));
    }

    return r_iter;
}

/**
 * Функция быстрой сортировки участка
 * @param ppArrayBegin Начало сортируемого участка
 * @param ppArrayEnd Конец сортируемого участка (не включительно)
 * @param pCompareFunc Компаратор
 */
void quickSortRange(void **ppArrayBegin, void **ppArrayEnd, CompareSortType pCompareFunc)
{
    if (ppArrayBegin + 1 < ppArrayEnd)
    {
        void **ppArrayMiddle = partition(ppArrayBegin, ppArrayEnd, pCompareFunc);
        quickSortRange(ppArrayBegin, ppArrayMiddle + 1, pCompareFunc);
        quickSortRange(ppArrayMiddle + 1, ppArrayEnd, pCompareFunc);
    }
}

void quickSort(void **ppArray, int length, CompareSortType pCompareFunc)
{
    quickSortRange(ppArray, ppArray + length, pCompareFunc);
}

} // namespace templates
