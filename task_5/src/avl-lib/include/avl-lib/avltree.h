#ifndef AVL_HEAD_H_2024_04_11
#define AVL_HEAD_H_2024_04_11

#include <algorithm>
#include <exception>

#include "memory-lib/mm.h"

namespace lab618
{

/**
 * Шаблонное AVL-дерево
 * @tparam T Тип хранимых данных
 * @tparam Compare Функция-компаратор
 */
template <class T, int (*Compare)(const T *pElement, const T *pElement2)> class CAVLTree
{
  private:
    /**
     * Лист AVL-дерева
     */
    struct leaf
    {
        /**
         * Указатель на хранимые данные
         */
        T *pData = nullptr;

        /**
         * Указатель на левый дочерний лист
         */
        leaf *pLeft = nullptr;

        /**
         * Указатель на правый дочерний лист
         */
        leaf *pRight = nullptr;

        /**
         * Балансировочный фактор листа
         */
        int balanceFactor = 0;
    };

    /**
     * Результат рекурсивных функция внутри дерева
     */
    struct recurseResult
    {
        /**
         * Признак необходимости обновлять балансировочный фактор
         */
        bool doChangeHeight = false;

        /**
         * Признак успеха рекурсивной операции
         */
        bool isSuccess = false;

        /**
         * Новый корень изменяемого поддерева
         */
        leaf *subtreeRoot = nullptr;
    };

  public:
    /**
     * Исключение, применяемое в работе алгоритма
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
        explicit CException(const char *msg = "Not enough memory!") : message_(msg)
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
     * @param defaultBlockSize
     */
    explicit CAVLTree(int defaultBlockSize) : m_pRoot(nullptr), m_Memory(CMemoryManager<leaf>(defaultBlockSize, true))
    {
    }

    /**
     * Стандартный деструктор
     */
    virtual ~CAVLTree()
    {
    }

    /**
     * Функция добавления элемента в дерево
     * @param pElement Указатель на добавляемый элемент
     * @return Признак добавления элемента
     */
    bool add(T *pElement)
    {
        auto result = addToSubtree(m_pRoot, pElement);
        m_pRoot = result.subtreeRoot;

        return result.isSuccess;
    }

    /**
     * Функция обновления элемента в дерево.
     * Дает гарантию нахождения элемента в дереве после операции.
     * @param pElement Указатель на обновляемый элемент
     * @return Признак обновления: true, если элемент был обновлен; false, если был добавлен
     */
    bool update(T *pElement)
    {
        auto result = updateInSubtree(m_pRoot, pElement);
        m_pRoot = result.subtreeRoot;

        return result.isSuccess;
    }

    /**
     * Функция поиска элемента в дереве
     * @param pElement Ссылка на искомый элемент
     * @return Указатель на найденный элемент
     */
    T *find(const T &pElement)
    {
        leaf *it = m_pRoot;

        while (it != nullptr && Compare(it->pData, &pElement) != 0)
        {
            if (Compare(it->pData, &pElement) > 0)
            {
                it = it->pRight;
            }
            else
            {
                it = it->pLeft;
            }
        }

        return it == nullptr ? nullptr : it->pData;
    }

    /**
     * Функция удаления элемента из дерева.
     * Дает гарантию, что после операции элемента в дереве не будет.
     * @param element Ссылка на удаляемый элемент
     * @return Признак удаления элемента
     */
    bool remove(const T &element)
    {
        auto result = removeFromSubtree(m_pRoot, &element);
        m_pRoot = result.subtreeRoot;

        return result.isSuccess;
    }
    /**
     * Функция очистки дерева
     */
    void clear()
    {
        m_Memory.clear();
        m_pRoot = nullptr;
    }

  private:
    /**
     * Малый левый поворот
     * @param subtree Изменяемое поддерево
     * @return Новый корень поддерева
     */
    leaf *smallLeftRotate(leaf *subtree)
    {
        leaf *new_root = subtree->pRight;

        subtree->pRight = new_root->pLeft;
        new_root->pLeft = subtree;

        if (new_root->balanceFactor == 0)
        {
            subtree->balanceFactor = 1;
            new_root->balanceFactor = -1;
        }
        else
        {
            subtree->balanceFactor = 0;
            new_root->balanceFactor = 0;
        }

        return new_root;
    }

    /**
     * Малый правый поворот
     * @param subtree Изменяемое поддерево
     * @return Новый корень поддерева
     */
    leaf *smallRightRotate(leaf *subtree)
    {
        leaf *new_root = subtree->pLeft;

        subtree->pLeft = new_root->pRight;
        new_root->pRight = subtree;

        if (new_root->balanceFactor == 0)
        {
            subtree->balanceFactor = -1;
            new_root->balanceFactor = 1;
        }
        else
        {
            subtree->balanceFactor = 0;
            new_root->balanceFactor = 0;
        }

        return new_root;
    }

    /**
     * Большой левый поворот
     * @param subtree Изменяемое поддерево
     * @return Новый корень поддерева
     */
    leaf *bigLeftRotate(leaf *subtree)
    {
        leaf *new_root = subtree->pRight->pLeft;

        subtree->pRight->pLeft = new_root->pRight;
        new_root->pRight = subtree->pRight;
        subtree->pRight = new_root->pLeft;
        new_root->pLeft = subtree;

        switch (new_root->balanceFactor)
        {
        case 1:
            new_root->pLeft->balanceFactor = -1;
            new_root->pRight->balanceFactor = 0;
            break;
        case 0:
            new_root->pLeft->balanceFactor = 0;
            new_root->pRight->balanceFactor = 0;
            break;
        case -1:
            new_root->pLeft->balanceFactor = 0;
            new_root->pRight->balanceFactor = 1;
        }

        new_root->balanceFactor = 0;

        return new_root;
    }

    /**
     * Большой правый поворот
     * @param subtree Изменяемое поддерево
     * @return Новый корень поддерева
     */
    leaf *bigRightRotate(leaf *subtree)
    {

        leaf *new_root = subtree->pLeft->pRight;

        subtree->pLeft->pRight = new_root->pLeft;
        new_root->pLeft = subtree->pLeft;
        subtree->pLeft = new_root->pRight;
        new_root->pRight = subtree;

        switch (new_root->balanceFactor)
        {
        case 1:
            new_root->pLeft->balanceFactor = -1;
            new_root->pRight->balanceFactor = 0;
            break;
        case 0:
            new_root->pLeft->balanceFactor = 0;
            new_root->pRight->balanceFactor = 0;
            break;
        case -1:
            new_root->pLeft->balanceFactor = 0;
            new_root->pRight->balanceFactor = 1;
        }

        new_root->balanceFactor = 0;

        return new_root;
    }

    /**
     * Функция ребалансировки поддерева
     * @param subtree Изменяемое поддерево
     * @return Новый корень поддерева
     */
    leaf *rebalance(leaf *subtree)
    {
        if (subtree->balanceFactor == 2)
        {
            if (subtree->pRight->balanceFactor == -1)
            {
                subtree = bigLeftRotate(subtree);
            }
            else
            {
                subtree = smallLeftRotate(subtree);
            }
        }
        else if (subtree->balanceFactor == -2)
        {
            if (subtree->pLeft->balanceFactor == 1)
            {
                subtree = bigRightRotate(subtree);
            }
            else
            {
                subtree = smallRightRotate(subtree);
            }
        }

        return subtree;
    }

    /**
     * Функция нахождения минимального элемента в поддереве
     * @param subtree Поддерево для поиска
     * @return Вершина с искомым значением
     */
    leaf *findMin(leaf *subtree)
    {
        while (subtree->pLeft != nullptr)
        {
            subtree = subtree->pLeft;
        }

        return subtree;
    }

    /**
     * Функция добавления элемента в поддереве
     * @param subtree Изменяемое поддерево
     * @param element Добавляемый элемент
     * @return Результат рекурсивного вызова
     */
    recurseResult addToSubtree(leaf *subtree, T *element)
    {
        if (subtree == nullptr)
        {
            try
            {
                leaf *new_leaf = m_Memory.newObject();
                new_leaf->pData = element;

                return {true, true, new_leaf};
            }
            catch (typename CMemoryManager<leaf>::CException &exception)
            {
                throw CException(exception.what());
            }
        }

        recurseResult result{};

        if (Compare(subtree->pData, element) > 0)
        {
            result = addToSubtree(subtree->pRight, element);

            subtree->pRight = result.subtreeRoot;

            if (result.doChangeHeight)
            {
                ++subtree->balanceFactor;
                subtree = rebalance(subtree);
            }
        }
        else if (Compare(subtree->pData, element) < 0)
        {
            result = addToSubtree(subtree->pLeft, element);

            subtree->pLeft = result.subtreeRoot;

            if (result.doChangeHeight)
            {
                --subtree->balanceFactor;
                subtree = rebalance(subtree);
            }
        }
        else
        {
            return {false, false, subtree};
        }

        return {result.doChangeHeight && subtree->balanceFactor != 0, result.isSuccess, subtree};
    }

    /**
     * Функция обновления элемента в поддереве
     * @param subtree Изменяемое поддерево
     * @param element Обновляемый элемент
     * @return Результат рекурсивного вызова
     */
    recurseResult updateInSubtree(leaf *subtree, T *element)
    {
        if (subtree == nullptr)
        {
            try
            {
                leaf *new_leaf = m_Memory.newObject();
                new_leaf->pData = element;

                return {true, false, new_leaf};
            }
            catch (typename CMemoryManager<leaf>::CException &exception)
            {
                throw CException(exception.what());
            }
        }

        recurseResult result{};

        if (Compare(subtree->pData, element) > 0)
        {
            result = updateInSubtree(subtree->pRight, element);

            subtree->pRight = result.subtreeRoot;

            if (result.doChangeHeight)
            {
                ++subtree->balanceFactor;
                subtree = rebalance(subtree);
            }
        }
        else if (Compare(subtree->pData, element) < 0)
        {
            result = updateInSubtree(subtree->pLeft, element);

            subtree->pLeft = result.subtreeRoot;

            if (result.doChangeHeight)
            {
                --subtree->balanceFactor;
                subtree = rebalance(subtree);
            }
        }
        else
        {
            subtree->pData = element;
            return {false, true, subtree};
        }

        return {!result.doChangeHeight && subtree->balanceFactor != 0, result.isSuccess, subtree};
    }

    /**
     * Функция удаления элемента из поддерева
     * @param subtree Изменяемое поддерево
     * @param element Удаляемый элемент
     * @return Результат рекурсивного вызова
     */
    recurseResult removeFromSubtree(leaf *subtree, const T *element)
    {

        if (subtree == nullptr)
        {
            return {false, false, nullptr};
        }

        recurseResult result{};

        if (Compare(subtree->pData, element) > 0)
        {
            result = removeFromSubtree(subtree->pRight, element);

            subtree->pRight = result.subtreeRoot;

            if (result.doChangeHeight)
            {
                --subtree->balanceFactor;
                subtree = rebalance(subtree);
            }
        }
        else if (Compare(subtree->pData, element) < 0)
        {
            result = removeFromSubtree(subtree->pLeft, element);

            subtree->pLeft = result.subtreeRoot;

            if (result.doChangeHeight)
            {
                ++subtree->balanceFactor;
                subtree = rebalance(subtree);
            }
        }
        else
        {
            if (subtree->pLeft == nullptr || subtree->pRight == nullptr)
            {
                leaf *child = subtree->pRight == nullptr ? subtree->pLeft : subtree->pRight;
                m_Memory.deleteObject(subtree);

                return {true, true, child};
            }
            else
            {
                T *min = findMin(subtree->pRight)->pData;
                result = removeFromSubtree(subtree->pRight, min);

                subtree->pData = min;
                subtree->pRight = result.subtreeRoot;

                if (result.doChangeHeight)
                {
                    --subtree->balanceFactor;
                    subtree = rebalance(subtree);
                }
            }
        }

        return {result.doChangeHeight && subtree->balanceFactor == 0, result.isSuccess, subtree};
    }

    leaf *m_pRoot;
    CMemoryManager<leaf> m_Memory;
};

} // namespace lab618

#endif // #define AVL_HEAD_H_2024_04_11
