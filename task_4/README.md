# Task 4: Sort

## HeapSort && MergeSort

Написать функции сортировки кучей и слиянием по шаблону:

```c++
#ifndef SORT_HEAD_H_2024_03_21
#define SORT_HEAD_H_2024_03_21

namespace templates
{
    
/**
 * Функция сравнения элементов
 */
typedef int(CompareSortType)(const void *pElem1, const void *pElem2);

/**
 * Элементарная функция сортировки слиянием
 * @param ppArray Сортируемый массив
 * @param length Длина массива
 * @param pCompareFunc Компаратор
 */
void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc);

/**
 * Элементарная функция сортировки кучей
 * @param ppArray Сортируемый массив
 * @param length Длина массива
 * @param pCompareFunc Компаратор
 */
void heapSort(void **ppArray, int length, CompareSortType pCompareFunc);

/**
 * Типобезопасная функция сортировки слиянием
 * @param ppArray Сортируемый массив
 * @param length Длина массива
 * @param pCompareFunc Компаратор
 */
template <class T> void mergeSort(T **ppArray, int length, int(pCompareFunc)(const T *pElem1, const T *pElem2))
{
    mergeSort(reinterpret_cast<void **>(ppArray), length, (CompareSortType *)pCompareFunc);
}

/**
 * Типобезопасная функция сортировки кучей
 * @param ppArray Сортируемый массив
 * @param length Длина массива
 * @param pCompareFunc Компаратор
 */
template <class T> void heapSort(T **ppArray, int length, int(pCompareFunc)(const T *pElem1, const T *pElem2))
{
    heapSort(reinterpret_cast<void **>(ppArray), length, (CompareSortType *)pCompareFunc);
}

} // namespace templates

#endif // #define SORT_HEAD_H_2024_03_21
```
