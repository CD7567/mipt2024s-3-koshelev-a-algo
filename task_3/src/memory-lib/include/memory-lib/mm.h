#ifndef MEMORY_MANAGER_HEAD_H_2024_03_07
#define MEMORY_MANAGER_HEAD_H_2024_03_07

namespace lab618
{
template <class T> class CMemoryManager
{
  private:
    struct block
    {
        // Массив данных блока
        T *pdata;
        // Адрес следующего блока
        block *pnext;
        // Первая свободная ячейка
        int firstFreeIndex;
        // Число заполненных ячеек
        int usedCount;
    };

  public:
    class CException
    {
      public:
        CException()
        {
        }
    };

  public:
    /**
     * @param _default_block_size Количество элементов в блоке данных
     * @param isDeleteElementsOnDestruct Уничтожать элементы в деструкторе менеджера или проверять
     *                                   на наличие неосвобожденных функцией deleteObject элементов.
     */
    CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false)
    {
    }

    virtual ~CMemoryManager()
    {
    }

    // Получить адрес нового элемента из менеджера
    T *newObject()
    {
    }

    // Освободить элемент в менеджере
    bool deleteObject(T *p)
    {
    }

    // Очистка данных, зависит от m_isDeleteElementsOnDestruct
    void clear()
    {
    }

  private:
    // Создать новый блок данных. применяется в newObject
    block *newBlock()
    {
    }

    // Освободить память блока данных. Применяется в clear
    void deleteBlock(block *p)
    {
    }

    // Размер блока
    int m_blkSize;
    // Начало списка блоков
    block *m_pBlocks;
    // Текущий блок
    block *m_pCurrentBlk;
    // Удалять ли элементы при освобождении
    bool m_isDeleteElementsOnDestruct;
};
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2024_03_07