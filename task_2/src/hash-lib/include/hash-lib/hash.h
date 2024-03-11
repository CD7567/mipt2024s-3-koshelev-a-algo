#ifndef HASH_HEAD_H_2024_02_23
#define HASH_HEAD_H_2024_02_23

#include <exception>

namespace lab618
{
/**
Шаблонный класс CHash.
В качестве параметров шаблона применяется:
тип - T;
функция вычисления хеша - unsigned int HashFunc(const T* pElement);
функция сравнения - int Compare(const T *pElement, const T* pElement2).

 Класс реализует алгоритм контейнера Хеш-таблица (ассоциативный массив). Данный алгоритм базируется на идее формирования
линейной адресации произвольных элементов в зависимости от специально вычисляемого целого значения, уникального для
каждого элемента (хеш). Формирование линейной адресации позволяет получать и сохранять элементы в контейнер за время не
зависящее от числа элементов в контейнере — O(1). В идеальном случае каждому хешу соответствует ячейка в линейном
массиве данных. На самом деле подобрать функцию вычисления хеша, таким образом, чтобы соблюдалась уникальность сложно,
или получаются числа очень большой размерности. Для преодоления данной проблемы, в Хеш-таблице допускаются коллизии —
одинаковые значения, уникальность элементов определяется их полями (функциями сравнения). Существует два способа
разрешения коллизий — разреженная Хеш-таблица и Хеш-таблица со списками. Разреженные Хеш-таблицы при возникновении
коллизии начинают искать первую свободную ячейку в самой таблице, поиск аналогично происходит от ячейки с номером равным
значению хеша, пока не найдется нужный элемент. Хеш-таблица со списками, в каждой ячейке Хеш-таблицы хранит начало
списка элементов с одинаковыми значениями хеша. Соответственно, вставка производится по алгоритму: вычисляем значение
хеша для элемента, проверяем есть ли в списке с данным индексом (значение хеш функции) данный элемент с помощью функции
сравнения, если нет до добавляем его в список. Поиск производится по алгоритму: вычисляем значение хеша для элемента,
проверяем есть ли в списке с данным индексом искомый элемент с помощью функции сравнения.
 Размер Хеш-таблицы, как правило, меньше размерности функции вычисления хеша, поэтому вычисленное значение хеша
ограничивают по размеру таблицы с помощью операции вычисления остатка от деления. Функция вычисления хеша и операция
сравнения задаются как параметры шаблона, что позволяет построить разные Хеш-таблицы для одного набора элементов.
 Основные недостатки Хеш-таблиц:
  1. Сложность подбора хорошей хеш функции (функции дающей наименьшее число коллизий);
  2. Отсутствие упорядоченности элементов;
  3. Вычислительная сложность хеш функции может добавить большую константу в вычислительную сложность алгоритма.

Данный класс реализует алгоритм Хеш-таблицы со списками
Данный класс не хранит данные — хранит, только указатели на них.
Хранение данных производится вне рамок данного класса!
*/
template <class T, unsigned int (*HashFunc)(const T *pElement), int (*Compare)(const T *pElement, const T *pElement2)>
class CHash
{
  private:
    /**
    Лист списка элементов. Обратите внимание, что хранится указатель на данные.
    Данный класс не хранит данные — хранит, только указатели на них.
    Хранение данных производится вне рамок данного класса!
    */
    struct leaf
    {
        T *pData;
        leaf *pNext;

        explicit leaf(T *data = nullptr, leaf *next = nullptr) : pData(data), pNext(next)
        {
        }
    };

  public:
    /**
    Исключение, которое применяется при нехватке памяти на работу алгоритма
    */
    class CMemoryException final : public std::exception
    {
      private:
        const char *message_;

      public:
        explicit CMemoryException(const char *msg = "Not enough memory!") : message_(msg)
        {
        }

        [[nodiscard]] const char *what() const noexcept override
        {
            return message_;
        }
    };

  public:
    /**
    Конструктор с параметрами: размер Хеш-таблицы
    Размер Хеш таблицы реализуем жестко — изменение размера таблицы в зависимости от числа элементов в контейнере не
    требуется.
    */
    explicit CHash(int hashTableSize) : m_tableSize(hashTableSize), m_pTable(new leaf *[hashTableSize]())
    {
    }

    /**
    Деструктор. Должен освобождать всю выделенную память
    */
    virtual ~CHash()
    {
        leaf **it_bucket = m_pTable;

        for (int i = 0; i < m_tableSize; ++i)
        {
            for (leaf *it = *(it_bucket++); it != nullptr;)
            {
                leaf *to_delete = it;

                it = it->pNext;
                delete to_delete;
            }
        }

        delete[] m_pTable;
    }

    /**
    Функция добавления элемента в Хеш-таблицу. Возвращает false, если элемент уже есть и true, если элемент добавлен.
    */
    bool add(T *pElement)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(pElement, idx);

        if (elem_it == nullptr)
        {
            leaf *bucket_it = m_pTable[idx];

            if (bucket_it == nullptr)
            {
                try
                {
                    m_pTable[idx] = new leaf(pElement, nullptr);
                }
                catch (std::bad_alloc &exception)
                {
                    throw CMemoryException("Couldn't allocate new leaf!");
                }
            }
            else
            {
                while (bucket_it->pNext != nullptr)
                {
                    bucket_it = bucket_it->pNext;
                }

                try
                {
                    bucket_it->pNext = new leaf(pElement, nullptr);
                }
                catch (std::bad_alloc &exception)
                {
                    throw CMemoryException("Couldn't allocate new leaf!");
                }
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    /**
    Функция обновления элемента в Хеш-таблице. Обновляет, если элемент уже есть; добавляет, если элемента еще нет.
    Возвращает false, если был добавлен новый элемент; true, если элемент обновлен.
    */
    bool update(T *pElement)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(pElement, idx);

        if (elem_it == nullptr)
        {
            add(pElement);
            return false;
        }
        else
        {
            elem_it->pData = pElement;
            return true;
        }
    }

    /**
    Функция поиска элемента в Хеш-таблице. Возвращает указатель на данные. Если элемента не нашлось, то null.
    Обратите внимание, что для поиска используется частично заполненный объект, т.е. В нем должны быть заполнены поля на
    основе которых рассчитывается хеш.*/
    T *find(const T &element)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(&element, idx);
        return elem_it == nullptr ? nullptr : elem_it->pData;
    }

    /**
    Функция удаления элемента из Хеш-таблицы. Возвращает false, если не нашлось элемента, true если элемент был удален.
    */
    bool remove(const T &element)
    {
        unsigned int idx;
        leaf *elem_it = findLeaf(&element, idx);

        if (elem_it != nullptr)
        {
            leaf *bucket_it = m_pTable[idx];

            if (Compare(bucket_it->pData, &element) == 0)
            {
                m_pTable[idx] = bucket_it->pNext;
            }
            else
            {
                while (Compare(bucket_it->pNext->pData, &element) != 0)
                {
                    bucket_it = bucket_it->pNext;
                }

                bucket_it->pNext = bucket_it->pNext->pNext;
            }

            delete elem_it;
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
    Удаление всех элементов. Можно вызвать в деструкторе
    */
    void clear()
    {
        leaf **it_bucket = m_pTable;

        for (int i = 0; i < m_tableSize; ++i)
        {
            for (leaf *it = *(it_bucket++); it != nullptr;)
            {
                leaf *to_delete = it;

                it = it->pNext;
                delete to_delete;
            }

            m_pTable[i] = nullptr;
        }
    }

  private:
    /**
    Элементарная функция поиска узла в Хеш-таблице. Возвращает найденный узел и в переменную idx выставляет актуальный
    индекс хеш-таблицы. Данную функцию следует использовать в функциях add, update, find. Алгоритм функции:
     1. вычисляем хеш функцию
     2. вычисляем индекс в Хеш-таблице (приводим вычисленное значение хеш функции к размеру массива)
     3. Перебираем список значений и если нашли, то возвращаем его.
     4. Если ничего не нашли, то возвращаем null
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
    Размер Хеш-таблицы
    */
    int m_tableSize;

    /**
    Хеш-таблица
    */
    leaf **m_pTable;
};
} // namespace lab618

#endif // #define HASH_HEAD_H_2024_02_23