# Task 3: MemoryManager

## CMemoryManager

Написать шаблонный менеджер памяти по шаблону:

```c++
#ifndef MEMORY_MANAGER_HEAD_H_2024_03_07
#define MEMORY_MANAGER_HEAD_H_2024_03_07

#include <exception>

namespace lab618
{

/**
 * Шаблонный класс менеджера памяти.
 * Ограничение: размер хранимого типа должен превосходить размер int.
 * @tparam T Хранимый тип данных
 */
template <class T> class CMemoryManager
{
  private:
    /**
     * Структура, представляющая блок памяти
     */
    struct block
    {
        /**
         * Массив данных блока
         */
        T *pData;

        /**
         * Адрес следующего блока
         */
        block *pNext;

        /**
         * Первая свободная ячейка
         */
        int firstFreeIndex;

        /**
         * Число заполненных ячеек
         */
        int usedCount;
    };

  public:
    /**
     * Исключение, применяемое в данном классе
     */
    class CException
    {
    };

  public:
    /**
     * Стандартный конструктор
     * @param default_block_size Количество элементов в блоке данных
     * @param isDeleteElementsOnDestruct Уничтожать элементы в деструкторе менеджера или проверять
     *                                   на наличие неосвобожденных функцией deleteObject элементов
     */
    CMemoryManager(int default_block_size, bool isDeleteElementsOnDestruct = false)
    {
    }

    /**
     * Виртуальный деструктор, предусмотрено наследование
     */
    virtual ~CMemoryManager()
    {
    }

    /**
     * Получить новый элемент из менеджера
     * @return Указатель на новый элемент
     */
    T *newObject()
    {
    }

    /**
     * Удалить элемент в менеджере
     * @param elem Указатель на удаляемый объект
     * @return Признак удаления объекта
     */
    bool deleteObject(T *elem)
    {
    }

    /**
     * Очистка данных
     */
    void clear()
    {
    }

  private:
    /**
     * Создать новый блок памяти
     */
    block *newBlock()
    {
    }

    /**
     * Освободить память блока данных
     * @param blk Освобождаемый блок
     */
    inline void deleteBlock(block *blk)
    {
    }

    /**
     * Размер блока
     */
    int m_blkSize;

    /**
     * Начало списка блоков
     */
    block *m_pBlocks;

    /**
     * Текущий блок
     */
    block *m_pCurrentBlk;

    /**
     * Удалять ли элементы при освобождении
     */
    bool m_isDeleteElementsOnDestruct;
};

} // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2024_03_07
```
