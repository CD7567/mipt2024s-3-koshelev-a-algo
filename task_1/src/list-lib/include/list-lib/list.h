#ifndef TEMPLATES_LIST_2024_02_12
#define TEMPLATES_LIST_2024_02_12

namespace lab618
{

template <class T> class CSingleLinkedList
{
  private:
    struct leaf
    {
        // Данные
        T data;
        // Указатель на следующий лист списка
        leaf *pNext;
        leaf(T &_data, leaf *_pNext) : data(_data), pNext(_pNext)
        {
        }
    };

  public:
    class CIterator
    {
      public:
        CIterator() : m_pCurrent(nullptr), m_pBegin(nullptr)
        {
        }

        explicit CIterator(leaf *p) : m_pCurrent(p), m_pBegin(nullptr)
        {
        }

        CIterator(const CIterator &src) : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent)
        {
        }

        ~CIterator() = default;

        CIterator &operator=(const CIterator &src)
        {
            if (this != &src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
            }

            return *this;
        }

        bool operator!=(const CIterator &it) const
        {
            return m_pBegin != it.m_pBegin || m_pCurrent != it.m_pCurrent;
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

        void setLeaf(leaf *p)
        {
            m_pCurrent = p;
            m_pBegin = nullptr;
        }

        void setLeafPreBegin(leaf *p)
        {
            m_pBegin = p;
            m_pCurrent = nullptr;
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
    };

  public:
    CSingleLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr)
    {
    }

    virtual ~CSingleLinkedList()
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

    void pushFront(T &data)
    {
        leaf *p_newNode = new leaf(data, m_pBegin);

        if (m_pBegin == nullptr)
        {
            m_pEnd = p_newNode;
        }

        m_pBegin = p_newNode;
    }

    T popFront()
    {
        T tmp = m_pBegin->data;
        leaf *p_toRemove = m_pBegin;

        m_pBegin = m_pBegin->pNext;

        delete p_toRemove;
        return tmp;
    }

    // Изменяет состояние итератора. выставляет предыдущую позицию
    void erase(CIterator &it)
    {
        leaf *iter = nullptr;
        leaf *to_delete = it.getLeaf();

        for (iter = m_pBegin; iter != nullptr && iter->pNext != it.getLeaf(); iter = iter->pNext)
        {
        }

        if (it.getLeaf() == m_pEnd)
        {
            m_pEnd = iter;
        }

        if (iter != nullptr)
        {
            iter->pNext = it.getLeaf()->pNext;
            to_delete = it.getLeaf();
            it.setLeaf(iter);
        }
        else if (it.getLeaf() == m_pBegin)
        {
            m_pBegin = it.getLeaf()->pNext;
            to_delete = it.getLeaf();
            it.setLeafPreBegin(m_pBegin);
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

  private:
    // Храним голову и хвост списка
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

        for (iter = m_pBegin; iter != nullptr && iter->pNext != it.getLeaf(); iter = iter->pNext)
        {
        }

        if (it.getLeaf() == m_pEnd)
        {
            m_pEnd = iter;
        }
        else
        {
            it.getLeaf()->pNext->pPrev = iter;
        }

        if (iter != nullptr)
        {
            iter->pNext = it.getLeaf()->pNext;
            to_delete = it.getLeaf();
            it.setLeaf(iter);
        }
        else if (it.getLeaf() == m_pBegin)
        {
            m_pBegin = it.getLeaf()->pNext;
            to_delete = it.getLeaf();
            it.setLeafPreBegin(m_pBegin);
        }

        delete to_delete;
    }

    // Изменяет состояние итератора. выставляет следующую позицию.
    void eraseAndNext(CIterator &it)
    {
        leaf *iter = nullptr;
        leaf *to_delete = it.getLeaf();

        for (iter = m_pEnd; iter != nullptr && iter->pPrev != it.getLeaf(); iter = iter->pPrev)
        {
        }

        if (it.getLeaf() == m_pBegin)
        {
            m_pBegin = iter;
        }
        else
        {
            it.getLeaf()->pPrev->pNext = iter;
        }

        if (iter != nullptr)
        {
            iter->pPrev = it.getLeaf()->pPrev;
            to_delete = it.getLeaf();
            it.setLeaf(iter);
        }
        else if (it.getLeaf() == m_pEnd)
        {
            m_pEnd = it.getLeaf()->pPrev;
            to_delete = it.getLeaf();
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
