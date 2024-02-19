# Task 1: 08.02.2024-14.02.2024

Написать шаблонный односвязный список по шаблону:

```c++
#ifndef TEMPLATES_LIST_2024_02_12
#define TEMPLATES_LIST_2024_02_12

namespace lab618
{
    template<class T>
    class CSingleLinkedList
    {
    private:
        struct leaf
        {
            // Данные
            T data;
            // Указатель на следующий лист списка
            leaf* pNext;
            leaf(T& _data, leaf* _pNext)
            {
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(0), m_pBegin(0)
            {
            }

            CIterator(leaf* p)
            {
            }

            CIterator(const CIterator& src)
            {
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator& src)
            {
            }

            bool operator != (const CIterator& it) const
            {
                return true;
            }

            void operator++()
            {
            }

            T& getData()
            {
                return T();
            }

            T& operator* ()
            {
                T tmp;
                return tmp;
            }

            leaf* getLeaf()
            {
                return 0;
            }

            void setLeaf(leaf* p)
            {
            }

            void setLeafPreBegin(leaf* p)
            {
            }

            bool isValid() {
                return false;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList()
        {
        }

        virtual ~CSingleLinkedList()
        {
        }

        void pushBack(T& data)
        {
        }

        void pushFront(T& data)
        {
        }

        T popFront()
        {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
        }

        int getSize()
        {
            return 0;
        }

        void clear()
        {
        }

        CIterator begin()
        {
            return CIterator();
        }

    private:
        //храним голову и хвост списка
        leaf* m_pBegin, * m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2024_02_12
```