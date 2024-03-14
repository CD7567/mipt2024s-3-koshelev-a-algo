#ifndef TEMPLATES_LIST_2024_02_12
#define TEMPLATES_LIST_2024_02_12

namespace lab618
{

/**
 * Класс шаблонного односвязного списка
 * @tparam T    Хранимый тип
 */
template <class T> class CSingleLinkedList
{
  private:
    /**
     * Структура, реализующая лист односвязного списка
     */
    struct leaf
    {
        /**
         * Хранимый объект
         */
        T data;

        /**
         * Указатель на следующий лист списка
         */
        leaf *pNext;

        /**
         * Стандартный конструктор
         * @param _data Элемент, конструируется копированием
         * @param _pNext Указатель на следующий элемент
         */
        leaf(T &_data, leaf *_pNext) : data(_data), pNext(_pNext)
        {
        }
    };

  public:
    /**
     * Forward-итератор односвязного списка
     */
    class CIterator
    {
      public:
        /**
         * Конструктор по умолчанию, итератор совпадает с итератором сразу за списком
         */
        CIterator() : m_pCurrent(nullptr), m_pBegin(nullptr)
        {
        }

        /**
         * Конструктор по листу
         * @param p Лист, на который указывает итератор
         */
        explicit CIterator(leaf *p) : m_pCurrent(p), m_pBegin(nullptr)
        {
        }

        /**
         * Конструктор копирования
         * @param src Копируемый итератор
         */
        CIterator(const CIterator &src) : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent)
        {
        }

        /**
         * Стандартный деструктор
         */
        ~CIterator() = default;

        /**
         * Оператор копирующего присваивания
         * @param src Копируемый итератор
         * @return Ссылка на текущий итератор
         */
        CIterator &operator=(const CIterator &src)
        {
            if (this != &src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
            }

            return *this;
        }

        /**
         * Оператор сравнения итераторов
         * @param it Другой итератор
         * @return Признак равенства
         */
        bool operator!=(const CIterator &it) const
        {
            return m_pBegin != it.m_pBegin || m_pCurrent != it.m_pCurrent;
        }

        /**
         * Оператор инкремента
         */
        void operator++()
        {
            if (m_pBegin != nullptr)
            {
                m_pCurrent = m_pBegin;
                m_pBegin = nullptr;
            }
            else if (m_pCurrent != nullptr)
            {
                m_pCurrent = m_pCurrent->pNext;
            }
        }

        /**
         * Получение данных из итератора
         * @return Ссылка на хранимое значение
         */
        T &getData()
        {
            return m_pCurrent->data;
        }

        /**
         * Оператор разыменования
         * @return Ссылка на хранимое значение
         */
        T &operator*()
        {
            return m_pCurrent->data;
        }

        /**
         * Получение листа по итератору
         * @return Указатель на текущий лист
         */
        leaf *getLeaf()
        {
            return m_pCurrent;
        }

        /**
         * Сеттер текущего листа
         * @param p Новый текущий лист
         */
        void setLeaf(leaf *p)
        {
            m_pCurrent = p;
            m_pBegin = nullptr;
        }

        /**
         * Сеттер итератора до начала списка
         * @param p Первый лист списка, перед которым выставляем итератор
         */
        void setLeafPreBegin(leaf *p)
        {
            m_pBegin = p;
            m_pCurrent = nullptr;
        }

        /**
         * Проверка валидности итератора. Итератор считается валидным, если он держит указатель на лист
         * @return Признак валидности итератора
         */
        bool isValid()
        {
            return m_pCurrent != nullptr;
        }

      private:
        /**
         * Голова списка, если мы находимся перед началом
         */
        leaf *m_pBegin;

        /**
         * Текущий лист
         */
        leaf *m_pCurrent;
    };

  public:
    /**
     * Стандартный конструктор
     */
    CSingleLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr)
    {
    }

    /**
     * Виртуальный деструктор, предусмотрено наследование
     */
    virtual ~CSingleLinkedList()
    {
        for (leaf *it = m_pBegin; it != nullptr;)
        {
            leaf *to_delete = it;

            it = it->pNext;
            delete to_delete;
        }
    }

    /**
     * Добавить элемент в конец списка
     * @param data Новый элемент, добавляется копированием
     */
    void pushBack(T &data)
    {
        leaf *p_newNode = new leaf(data, nullptr);

        if (m_pEnd != nullptr)
        {
            m_pEnd->pNext = p_newNode;
        }
        else
        {
            m_pBegin = p_newNode;
        }

        m_pEnd = p_newNode;
    }

    /**
     * Добавить элемент в начало списка
     * @param data Новый элемент, добавляется копированием
     */
    void pushFront(T &data)
    {
        leaf *p_newNode = new leaf(data, m_pBegin);

        if (m_pBegin == nullptr)
        {
            m_pEnd = p_newNode;
        }

        m_pBegin = p_newNode;
    }

    /**
     * Удалить элемент из начала списка
     */
    T popFront()
    {
        T tmp = m_pBegin->data;
        leaf *p_toRemove = m_pBegin;

        m_pBegin = m_pBegin->pNext;

        delete p_toRemove;
        return tmp;
    }

    /**
     * Удалить элемент по итератору. После удаления итератор указывает на элемент перед данным
     * @param it Итератор списка
     */
    void erase(CIterator &it)
    {
        leaf *iter = nullptr;
        leaf *to_delete = it.getLeaf();

        for (iter = m_pBegin; iter != nullptr && iter->pNext != to_delete; iter = iter->pNext)
        {
        }

        if (to_delete == m_pEnd)
        {
            m_pEnd = iter;
        }

        if (iter != nullptr)
        {
            iter->pNext = to_delete->pNext;
            it.setLeaf(iter);
        }
        else if (it.getLeaf() == m_pBegin)
        {
            m_pBegin = to_delete->pNext;
            it.setLeafPreBegin(m_pBegin);
        }

        delete to_delete;
    }

    /**
     * Рассчитать длину списка
     * @return Длина списка
     */
    int getSize()
    {
        int size = 0;

        for (leaf *it = m_pBegin; it != nullptr; ++size, it = it->pNext)
        {
        }

        return size;
    }

    /**
     * Очистить список, список остается валидным
     */
    void clear()
    {
        for (leaf *it = m_pBegin; it != nullptr;)
        {
            leaf *to_delete = it;

            it = it->pNext;
            delete to_delete;
        }

        m_pBegin = m_pEnd = nullptr;
    }

    /**
     * Получить итератор на первый элемент списка
     * @return Итератор на первый элемент списка
     */
    CIterator begin()
    {
        return CIterator(m_pBegin);
    }

  private:
    /**
     * Голова и хвост списка
     */
    leaf *m_pBegin, *m_pEnd;
};

template <class T> class CDualLinkedList
{
  private:
    struct leaf
    {
        // Данные
        T data;
        // Указатель на предыдущий / следующий лист списка
        leaf *pNext, *pPrev;
        leaf(T &_data, leaf *_pPrev, leaf *_pNext) : data(_data), pPrev(_pPrev), pNext(_pNext)
        {
        }
    };

  public:
    class CIterator
    {
      public:
        CIterator() : m_pBegin(nullptr), m_pCurrent(nullptr), m_pEnd(nullptr)
        {
        }

        explicit CIterator(leaf *p) : m_pBegin(nullptr), m_pCurrent(p), m_pEnd(nullptr)
        {
        }

        CIterator(const CIterator &src) : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent), m_pEnd(src.m_pCurrent)
        {
        }

        ~CIterator() = default;

        CIterator &operator=(const CIterator &src)
        {
            if (this != &src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pEnd = src.m_pEnd;
            }

            return *this;
        }

        bool operator!=(const CIterator &it) const
        {
            return m_pBegin != it.m_pBegin || m_pCurrent != it.m_pCurrent || m_pEnd != it.m_pEnd;
        }

        void operator++()
        {
            if (m_pBegin != nullptr)
            {
                m_pCurrent = m_pBegin;
                m_pBegin = nullptr;
            }
            else if (m_pCurrent != nullptr)
            {
                m_pCurrent = m_pCurrent->pNext;
            }
        }

        void operator--()
        {
            if (m_pEnd != nullptr)
            {
                m_pCurrent = m_pEnd;
                m_pEnd = nullptr;
            }
            else if (m_pCurrent != nullptr)
            {
                m_pCurrent = m_pCurrent->pPrev;
            }
        }

        T &getData()
        {
            return m_pCurrent->data;
        }

        T &operator*()
        {
            return m_pCurrent->data;
        }

        leaf *getLeaf()
        {
            return m_pCurrent;
        }

        // Применяется в erase и eraseAndNext
        void setLeaf(leaf *p)
        {
            m_pBegin = nullptr;
            m_pCurrent = p;
            m_pEnd = nullptr;
        }

        // Применяется в erase и eraseAndNext
        void setLeafPreBegin(leaf *p)
        {
            m_pBegin = p;
            m_pCurrent = nullptr;
            m_pEnd = nullptr;
        }

        // Применяется в erase и eraseAndNext
        void setLeafPostEnd(leaf *p)
        {
            m_pBegin = nullptr;
            m_pCurrent = nullptr;
            m_pEnd = p;
        }

        bool isValid()
        {
            return m_pCurrent != nullptr;
        }

      private:
        // Храним голову списка, если мы находимся перед началом
        leaf *m_pBegin;
        // Храним текущее положение
        leaf *m_pCurrent;
        // Храним конец списка, если мы находимся после конца
        leaf *m_pEnd;
    };

  public:
    CDualLinkedList() = default;

    virtual ~CDualLinkedList()
    {
        for (leaf *it = m_pBegin; it != nullptr;)
        {
            leaf *to_delete = it;

            it = it->pNext;
            delete to_delete;
        }
    }

    void pushBack(T &data)
    {
        leaf *p_newNode = new leaf(data, m_pEnd, nullptr);

        if (m_pEnd != nullptr)
        {
            m_pEnd->pNext = p_newNode;
            m_pEnd = p_newNode;
        }
        else
        {
            m_pBegin = m_pEnd = p_newNode;
        }
    }

    T popBack()
    {
        T tmp = m_pEnd->data;
        leaf *p_toRemove = m_pEnd;

        m_pEnd = m_pEnd->pPrev;

        if (m_pEnd != nullptr)
        {
            m_pEnd->pNext = nullptr;
        }
        else
        {
            m_pBegin = nullptr;
        }

        delete p_toRemove;
        return tmp;
    }

    void pushFront(T &data)
    {
        leaf *p_newNode = new leaf(data, nullptr, m_pBegin);

        if (m_pBegin != nullptr)
        {
            m_pBegin->pPrev = p_newNode;
            m_pBegin = p_newNode;
        }
        else
        {
            m_pBegin = m_pEnd = p_newNode;
        }
    }

    T popFront()
    {
        T tmp = m_pBegin->data;
        leaf *p_toRemove = m_pBegin;

        m_pBegin = m_pBegin->pNext;

        if (m_pBegin != nullptr)
        {
            m_pBegin->pPrev = nullptr;
        }
        else
        {
            m_pEnd = nullptr;
        }

        delete p_toRemove;
        return tmp;
    }

    // Изменяет состояние итератора. выставляет предыдущую позицию.
    void erase(CIterator &it)
    {
        leaf *iter = nullptr;
        leaf *to_delete = it.getLeaf();

        for (iter = m_pBegin; iter != nullptr && iter->pNext != to_delete; iter = iter->pNext)
        {
        }

        if (to_delete == m_pEnd)
        {
            m_pEnd = iter;
        }
        else
        {
            to_delete->pNext->pPrev = iter;
        }

        if (iter != nullptr)
        {
            iter->pNext = to_delete->pNext;
            it.setLeaf(iter);
        }
        else if (to_delete == m_pBegin)
        {
            m_pBegin = to_delete->pNext;
            it.setLeafPreBegin(m_pBegin);
        }

        delete to_delete;
    }

    // Изменяет состояние итератора. выставляет следующую позицию.
    void eraseAndNext(CIterator &it)
    {
        leaf *iter = nullptr;
        leaf *to_delete = it.getLeaf();

        for (iter = m_pEnd; iter != nullptr && iter->pPrev != to_delete; iter = iter->pPrev)
        {
        }

        if (to_delete == m_pBegin)
        {
            m_pBegin = iter;
        }
        else
        {
            to_delete->pPrev->pNext = iter;
        }

        if (iter != nullptr)
        {
            iter->pPrev = to_delete->pPrev;
            it.setLeaf(iter);
        }
        else if (to_delete == m_pEnd)
        {
            m_pEnd = to_delete->pPrev;
            it.setLeafPostEnd(m_pEnd);
        }

        delete to_delete;
    }

    int getSize()
    {
        int size = 0;

        for (leaf *it = m_pBegin; it != nullptr; ++size, it = it->pNext)
        {
        }

        return size;
    }

    void clear()
    {
        for (leaf *it = m_pBegin; it != nullptr;)
        {
            leaf *to_delete = it;

            it = it->pNext;
            delete to_delete;
        }

        m_pBegin = m_pEnd = nullptr;
    }

    CIterator begin()
    {
        return CIterator(m_pBegin);
    }

    CIterator end()
    {
        return CIterator(m_pEnd);
    }

  private:
    // Храним голову и хвост списка
    leaf *m_pBegin, *m_pEnd;
};

} // namespace lab618

#endif // #ifndef TEMPLATES_LIST_2024_02_12
