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
        int firstFreeIndex = 0;

        /**
         * Число заполненных ячеек
         */
        int usedCount = 0;

        /**
         * Стандартный конструктор
         * @param blk_size Размер хранимого блока
         * @param next_blk Указатель на следующий блок
         */
        block(int blk_size) : pData(static_cast<T *>(operator new(blk_size * sizeof(T)))), pNext(nullptr)
        {
        }
    };

  public:
    /**
     * Исключение, применяемое в данном классе
     */
    class CException final : public std::exception
    {
      private:
        /**
         * Сообщение об ошибке
         */
        const char *message_;

      public:
        /**
         * Стандартный конструктор
         * @param msg Сообщение об ошибке
         */
        explicit CException(const char *msg = "") : message_(msg)
        {
        }

        /**
         * Получить сообщение об ошибке
         * @return Сообщение об ошибке
         */
        [[nodiscard]] const char *what() const noexcept override
        {
            return message_;
        }
    };

  public:
    /**
     * Стандартный конструктор
     * @param default_block_size Количество элементов в блоке данных
     * @param isDeleteElementsOnDestruct Уничтожать элементы в деструкторе менеджера или проверять
     *                                   на наличие неосвобожденных функцией deleteObject элементов
     */
    CMemoryManager(int default_block_size, bool isDeleteElementsOnDestruct = false)
        : m_blkSize(default_block_size), m_pBlocks(nullptr), m_pCurrentBlk(nullptr),
          m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct)
    {
    }

    /**
     * Виртуальный деструктор, предусмотрено наследование
     */
    virtual ~CMemoryManager()
    {
        clear();
    }

    /**
     * Получить новый элемент из менеджера
     * @return Указатель на новый элемент
     */
    T *newObject()
    {
        if (m_pCurrentBlk == nullptr)
        {
            m_pBlocks = m_pCurrentBlk = newBlock();
        }
        else if (m_pCurrentBlk->usedCount == m_blkSize)
        {
            block *blk_it = m_pBlocks;

            while (blk_it != nullptr && blk_it->usedCount == m_blkSize)
            {
                blk_it = blk_it->pNext;
            }

            if (blk_it == nullptr)
            {
                m_pCurrentBlk = newBlock();
                m_pCurrentBlk->pNext = m_pBlocks;
                m_pBlocks = m_pCurrentBlk;
            }
            else
            {
                m_pCurrentBlk = blk_it;
            }
        }

        int new_index = m_pCurrentBlk->firstFreeIndex;
        m_pCurrentBlk->firstFreeIndex = *reinterpret_cast<int *>(m_pCurrentBlk->pData + new_index);
        ++m_pCurrentBlk->usedCount;

        return new (m_pCurrentBlk->pData + new_index) T();
    }

    /**
     * Удалить элемент в менеджере
     * @param elem Указатель на удаляемый объект
     * @return Признак удаления объекта
     */
    bool deleteObject(T *elem)
    {
        bool found = isInBlock(elem, m_pCurrentBlk);

        if (!found)
        {
            for (block *blk_it = m_pBlocks; blk_it != nullptr; blk_it = blk_it->pNext)
            {
                if (blk_it == m_pCurrentBlk)
                {
                    continue;
                }
                else if (isInBlock(elem, blk_it))
                {
                    found = true;
                    m_pCurrentBlk = blk_it;
                    break;
                }
            }
        }

        if (found)
        {
            elem->~T();
            *reinterpret_cast<int *>(elem) = m_pCurrentBlk->firstFreeIndex;
            m_pCurrentBlk->firstFreeIndex = elem - m_pCurrentBlk->pData;
            --m_pCurrentBlk->usedCount;
        }

        return found;
    }

    /**
     * Очистка данных
     */
    void clear()
    {
        if (!m_isDeleteElementsOnDestruct)
        {
            for (block *blk_it = m_pBlocks; blk_it != nullptr; blk_it = blk_it->pNext)
            {
                if (blk_it->usedCount > 0)
                {
                    throw CException("Some elements were not deleted!");
                }
            }
        }

        for (block *blk_it = m_pBlocks; blk_it != nullptr;)
        {
            block *to_delete = blk_it;

            blk_it = blk_it->pNext;
            deleteBlock(to_delete);
        }

        m_pBlocks = m_pCurrentBlk = nullptr;
    }

  private:
    /**
     * Создать новый блок памяти
     */
    block *newBlock()
    {
        block *new_block = new block(m_blkSize);

        for (size_t i = 0; i < m_blkSize; ++i)
        {
            *reinterpret_cast<int *>(new_block->pData + i) = i + 1;
        }

        return new_block;
    }

    /**
     * Удалить блок памяти
     * @param blk Освобождаемый блок
     */
    inline void deleteBlock(block *blk)
    {
        int count = blk->usedCount;

        for (int i = 0; i < m_blkSize && count > 0; ++i)
        {
            bool is_free = false;

            for (int index = blk->firstFreeIndex; index != m_blkSize;
                 index = *reinterpret_cast<int *>(blk->pData + index))
            {
                if (i == index)
                {
                    is_free = true;
                    break;
                }
            }

            if (!is_free)
            {
                (blk->pData + i)->~T();
                --count;
            }
        }

        operator delete(static_cast<void *>(blk->pData));
        delete blk;
    }

    /**
     * Проверка, находится ли элемент в блоке
     * @param elem Указатель на элемент
     * @param blk Указатель на блок
     * @return Признак нахождения в блоке
     */
    inline bool isInBlock(const T *elem, const block *blk)
    {
        return blk != nullptr && blk->pData <= elem && elem < blk->pData + m_blkSize;
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
