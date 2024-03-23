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
        block(int blk_size, block *next_blk = nullptr) : pData(new T[blk_size]), pNext(next_blk)
        {
            for (int i = 1; i < blk_size; ++i)
            {
                *reinterpret_cast<int *>(pData + i - 1) = i;
            }

            *reinterpret_cast<int *>(pData + blk_size - 1) = -1;
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
        explicit CException(const char *msg = "Stub!") : message_(msg)
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
        : m_blkSize(default_block_size), m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct), m_pBlocks(nullptr),
          m_pCurrentBlk(nullptr)
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
        block *blk_it = m_pBlocks;

        while (blk_it != nullptr && blk_it->usedCount == m_blkSize)
        {
            blk_it = blk_it->pNext;
        }

        if (blk_it == nullptr)
        {
            blk_it = newBlock();
        }

        int firstFreeIndex = blk_it->firstFreeIndex;
        blk_it->firstFreeIndex = *reinterpret_cast<int *>(blk_it->pData + firstFreeIndex);
        blk_it->pData[firstFreeIndex] = T();
        ++blk_it->usedCount;

        return blk_it->pData + firstFreeIndex;
    }

    /**
     * Удалить элемент в менеджере
     * @param elem Указатель на удаляемый объект
     * @return Признак удаления объекта
     */
    bool deleteObject(T *elem)
    {
        block *blk_it = m_pBlocks;

        while (blk_it != nullptr && !isInBlock(elem, blk_it))
        {
            blk_it = blk_it->pNext;
        }

        if (blk_it != nullptr)
        {
            elem->~T();

            *reinterpret_cast<int *>(elem) = blk_it->firstFreeIndex;
            blk_it->firstFreeIndex = elem - blk_it->pData;
            --blk_it->usedCount;
        }

        return blk_it != nullptr;
    }

    /**
     * Очистка данных
     */
    void clear()
    {
        block *blk_it = m_pBlocks;

        if (!m_isDeleteElementsOnDestruct)
        {
            while (blk_it != nullptr)
            {
                if (blk_it->usedCount > 0)
                {
                    throw CException("Some elements were not deleted!");
                }
                blk_it = blk_it->pNext;
            }
        }

        blk_it = m_pBlocks;

        while (blk_it != nullptr)
        {
            block *to_delete = blk_it;

            blk_it = blk_it->pNext;
            deleteBlock(to_delete);
            delete to_delete;
        }

        m_pBlocks = m_pCurrentBlk = nullptr;
    }

  private:
    /**
     * Создать новый блок памяти
     */
    block *newBlock()
    {
        try
        {
            if (m_pBlocks == nullptr)
            {
                m_pBlocks = new block(m_blkSize);
                m_pCurrentBlk = m_pBlocks;
            }
            else
            {
                m_pCurrentBlk->pNext = new block(m_blkSize);
                m_pCurrentBlk = m_pCurrentBlk->pNext;
            }

            return m_pCurrentBlk;
        }
        catch (std::bad_alloc &exception)
        {
            throw CException("Not enough memory for new block!");
        }
    }

    /**
     * Освободить память блока данных
     * @param blk Освобождаемый блок
     */
    inline void deleteBlock(block *blk)
    {
        delete[] blk->pData;
    }

    /**
     * Проверка, находится ли элемент в блоке
     * @param elem Указатель на элемент
     * @param blk Указатель на блок
     * @return Признак нахождения в блоке
     */
    inline bool isInBlock(const T *elem, const block *blk)
    {
        return blk->pData <= elem && elem < blk->pData + m_blkSize;
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
