#ifndef TEMPLATES_LIST_2024_02_12
#define TEMPLATES_LIST_2024_02_12

#include <cstddef>

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
            if (m_pBegin != nullptr) {
                m_pCurrent = m_pBegin;
                m_pBegin = nullptr;
            } else if (m_pCurrent != nullptr) {
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
        // храним голову списка, если мы находимся перед началом
        leaf *m_pBegin;
        // храним текущее положение
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
            m_pEnd = p_newNode;
        }
        else
        {
            m_pBegin = m_pEnd = p_newNode;
        }
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

    // изменяет состояние итератора. выставляет предыдущую позицию.
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
    // храним голову и хвост списка
    leaf *m_pBegin, *m_pEnd;
};
} // namespace lab618

#endif // #ifndef TEMPLATES_LIST_2024_02_12
