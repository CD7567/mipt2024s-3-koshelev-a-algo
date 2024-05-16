#ifndef HASH_HEAD_H_2024_03_07
#define HASH_HEAD_H_2024_03_07

#include <algorithm>
#include <exception>

#include "memory-lib/mm.h"

namespace lab618
{
/**
 * Класс реализует алгоритм контейнера Хеш-таблица (ассоциативный массив). Данный алгоритм базируется на идее
 * формирования линейной адресации произвольных элементов в зависимости от специально вычисляемого целого значения,
 * уникального для каждого элемента (хеш). Формирование линейной адресации позволяет получать и сохранять элементы в
 * контейнер за время не зависящее от числа элементов в контейнере — O(1). В идеальном случае каждому хешу соответствует
 * ячейка в линейном массиве данных. На самом деле подобрать функцию вычисления хеша, таким образом, чтобы соблюдалась
 * уникальность сложно, или получаются числа очень большой размерности. Для преодоления данной проблемы, в Хеш-таблице
 * допускаются коллизии — одинаковые значения, уникальность элементов определяется их полями (функциями сравнения).
 * Существует два способа разрешения коллизий — разреженная Хеш-таблица и Хеш-таблица со списками. Разреженные
 * Хеш-таблицы при возникновении коллизии начинают искать первую свободную ячейку в самой таблице, поиск аналогично
 * происходит от ячейки с номером равным значению хеша, пока не найдется нужный элемент. Хеш-таблица со списками, в
 * каждой ячейке Хеш-таблицы хранит начало списка элементов с одинаковыми значениями хеша. Соответственно, вставка
 * производится по алгоритму: вычисляем значение хеша для элемента, проверяем есть ли в списке с данным индексом
 * (значение хеш функции) данный элемент с помощью функции сравнения, если нет до добавляем его в список. Поиск
 * производится по алгоритму: вычисляем значение хеша для элемента, проверяем есть ли в списке с данным индексом искомый
 * элемент с помощью функции сравнения. Размер Хеш-таблицы, как правило, меньше размерности функции вычисления хеша,
 * поэтому вычисленное значение хеша ограничивают по размеру таблицы с помощью операции вычисления остатка от деления.
 * Функция вычисления хеша и операция сравнения задаются как параметры шаблона, что позволяет построить разные
 * Хеш-таблицы для одного набора элементов. Основные недостатки Хеш-таблиц:
 * 1. Сложность подбора хорошей хеш функции (функции дающей наименьшее число коллизий);
 * 2. Отсутствие упорядоченности элементов;
 * 3. Вычислительная сложность хеш функции может добавить большую константу в вычислительную сложность алгоритма.
 *
 * Данный класс реализует алгоритм Хеш-таблицы со списками
 * Данный класс не хранит данные — хранит, только указатели на них.
 * Хранение данных производится вне рамок данного класса!
 *
 * @tparam T Хранимый тип
 * @tparam HashFunc Хеш-функция
 * @tparam Compare Компаратор
 */
template <class T, unsigned int (*HashFunc)(const T *pElement), int (*Compare)(const T *pElement, const T *pElement2)>
class CHash
{
  private:
    /**
     * Лист списка элементов. Обратите внимание, что хранится указатель на данные.
     * Данный класс не хранит данные — хранит, только указатели на них.
     * Хранение данных производится вне рамок данного класса!
     */
    struct leaf
    {
        /**
         * Указатель на хранимые данные
         */
        T *pData;

        /**
         * Указатель на следующий в корзине лист
         */
        leaf *pNext;

        /**
         * Стандартный конструктор
         * @param data Указатель на данные
         * @param next Указатель на следующий в корзине лист
         */
        explicit leaf(T *data = nullptr, leaf *next = nullptr) : pData(data), pNext(next)
        {
        }
    };

  public:
    /**
     * Исключение, которое применяется при нехватке памяти на работу алгоритма
     */
    class CMemoryException final : public std::exception
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
        explicit CMemoryException(const char *msg = "Not enough memory!") : message_(msg)
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
     * Стандартный конструктор.
     * Размер хеш таблицы реализуем жестко — изменение размера таблицы в зависимости от числа элементов в контейнере не
     * требуется.
     * @param hashTableSize Размер хеш-таблицы
     */
    explicit CHash(int hashTableSize, int defaultBlockSize)
        : m_tableSize(hashTableSize), m_pTable(new leaf *[hashTableSize]),
          m_Memory(CMemoryManager<leaf>(defaultBlockSize, true))
    {
        std::fill(m_pTable, m_pTable + m_tableSize, nullptr);
    }

    /**
     * Деструктор, освобождает все листья.
     */
    virtual ~CHash()
    {
        delete[] m_pTable;
    }

    /**
     * Функция добавления элемента в хеш-таблицу.
     * @param pElement Указатель на добавляемый элемент
     * @return false, если элемент уже есть и true, если элемент добавлен
     */
    bool add(T *pElement)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(pElement, idx);

        if (elem_it == nullptr)
        {
            addLeaf(pElement, idx);
        }

        return elem_it == nullptr;
    }

    /**
     * Функция обновления элемента в хеш-таблице.
     * Обновляет, если элемент уже есть; добавляет, если элемента еще нет.
     * @param pElement Обновляемый элемент
     * @return false, если был добавлен новый элемент; true, если элемент обновлен
     */
    bool update(T *pElement)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(pElement, idx);

        if (elem_it == nullptr)
        {
            addLeaf(pElement, idx);
        }
        else
        {
            elem_it->pData = pElement;
        }

        return elem_it != nullptr;
    }

    /**
     * Функция поиска элемента в хеш-таблице
     * @param element Искомый элемент
     * @return Указатель на данные; если не нашлось, то nullptr
     */
    T *find(const T &element)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(&element, idx);
        return elem_it == nullptr ? nullptr : elem_it->pData;
    }

    /**
     * Функция удаления элемента из хеш-таблицы
     * @param element Элемент, который необходимо удалить
     * @return false, если не нашлось элемента; true если элемент был удален
     */
    bool remove(const T &element)
    {
        unsigned int idx = HashFunc(&element) % m_tableSize;
        leaf *bucket_it = m_pTable[idx];

        if (bucket_it == nullptr)
        {
            return false;
        }

        if (Compare(&element, bucket_it->pData) == 0)
        {
            m_pTable[idx] = bucket_it->pNext;
            m_Memory.deleteObject(bucket_it);

            return true;
        }

        while (bucket_it->pNext != nullptr && Compare(&element, bucket_it->pNext->pData) != 0)
        {
            bucket_it = bucket_it->pNext;
        }

        leaf *to_delete = bucket_it->pNext;
        if (to_delete != nullptr)
        {
            bucket_it->pNext = to_delete->pNext;
            m_Memory.deleteObject(to_delete);

            return true;
        }

        return false;
    }

    /**
     * Удаление всех элементов
     */
    void clear()
    {
        m_Memory.clear();
        delete[] m_pTable;

        m_pTable = new leaf*[m_tableSize];
        std::fill(m_pTable, m_pTable + m_tableSize, nullptr);
    }

  private:
    /**
     * Элементарная функция поиска узла в хеш-таблице
     * @param pElement Искомый элемент
     * @param idx Выставляет индекс корзины с элементом
     * @return Указатель на лист с элементом; nullptr, если элемента не нашлось
     */
    leaf *findLeaf(const T *pElement, unsigned int &idx)
    {
        idx = HashFunc(pElement) % m_tableSize;

        leaf *bucket_it = m_pTable[idx];

        while (bucket_it != nullptr)
        {
            if (Compare(bucket_it->pData, pElement) == 0)
            {
                return bucket_it;
            }

            bucket_it = bucket_it->pNext;
        }

        return nullptr;
    }

    /**
     * Элементарная функция добавления листа в корзину хеш-таблицы.
     * Добавляет новый лист в начало корзины.
     * @param pElement Добавляемый элемент
     * @param idx Индекс корзины
     */
    void addLeaf(T *pElement, unsigned int idx)
    {
        try
        {
            leaf *new_leaf = m_Memory.newObject();
            new_leaf->pData = pElement;
            new_leaf->pNext = m_pTable[idx];
            m_pTable[idx] = new_leaf;
        }
        catch (std::bad_alloc &exception)
        {
            throw CMemoryException("Couldn't allocate new leaf!");
        }
    }

    /**
     * Размер Хеш-таблицы
     */
    int m_tableSize;

    /**
     * Хеш-таблица
     */
    leaf **m_pTable;

    /**
     * Менеджер памяти, предназначен для хранение листов списков разрешения коллизий
     */
    CMemoryManager<leaf> m_Memory;
};
} // namespace lab618

#endif // #define HASH_HEAD_H_2024_03_07
