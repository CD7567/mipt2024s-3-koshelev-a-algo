#include <chrono>
#include <fstream>
#include <iostream>

#include "avl-lib/avltree.h"
#include "binsearch.h"
#include "generate.h"
#include "hash-lib/hash.h"
#include "sort-lib/sort.h"

#define TIME(funcCall, ChronoType, storage)                                                                            \
    {                                                                                                                  \
        auto start = std::chrono::high_resolution_clock::now();                                                        \
        funcCall;                                                                                                      \
        auto end = std::chrono::high_resolution_clock::now();                                                          \
        storage = std::chrono::duration_cast<ChronoType>(end - start).count();                                         \
    }

inline void printRow(std::ostream &out, std::string tag, int size, std::string method, size_t duration)
{
    out << tag << ", " << size << ", " << method << ", " << duration << "\n";
}

inline void profileArray(DataStruct *array, DataStruct *doubled_array, std::ostream &out, int test_min_size,
                         int test_max_size)
{
    size_t time;

    for (int i = test_min_size; i < test_max_size; i += 50000)
    {
        DataStruct *new_array = new DataStruct[i];
        DataStruct **new_ppArray = new DataStruct *[i];

        TIME(
            {
                std::copy(array, array + i, new_array);

                for (int j = 0; j < i; ++j)
                {
                    new_ppArray[j] = new_array + j;
                }

                templates::quickSort(new_ppArray, i, DataStruct::Compare);
            },
            std::chrono::milliseconds, time)
        printRow(out, "ARRAY", i, "ADD", time);

        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    binsearch(new_ppArray, 0, i - 1, array[j], DataStruct::Compare);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "ARRAY", i, "FIND", time);

        TIME(
            {
                for (int j = 0; j < 2 * i; ++j)
                {
                    binsearch(new_ppArray, 0, i - 1, doubled_array[j], DataStruct::Compare);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "ARRAY", i, "FIND2N", time);

        TIME(
            {
                delete[] new_array;
                delete[] new_ppArray;
            },
            std::chrono::milliseconds, time)
        printRow(out, "ARRAY", i, "CLEAR", time);
    }
}

inline void profileHash(DataStruct *array, DataStruct *doubled_array, std::ostream &out, int test_min_size,
                        int test_max_size)
{
    lab618::CHash<DataStruct, DataStruct::Hash, DataStruct::Compare> hashtable{test_max_size / 10, 1024};

    size_t time;

    for (int i = test_min_size; i < test_max_size; i += 50000)
    {
        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    hashtable.add(array + j);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "HASH", i, "ADD", time);

        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    hashtable.find(array[j]);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "HASH", i, "FIND", time);

        TIME(
            {
                for (int j = 0; j < 2 * i; ++j)
                {
                    hashtable.find(doubled_array[j]);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "HASH", i, "FIND2N", time);

        TIME(hashtable.clear(), std::chrono::milliseconds, time)
        printRow(out, "HASH", i, "CLEAR", time);

        for (int j = 0; j < i; ++j)
        {
            hashtable.add(array + j);
        }

        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    hashtable.remove(array[i]);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "HASH", i, "REMOVE", time);
    }
}

inline void profileAVL(DataStruct *array, DataStruct *doubled_array, std::ostream &out, int test_min_size,
                       int test_max_size)
{
    lab618::CAVLTree<DataStruct, DataStruct::Compare> avltree{1024};

    size_t time;

    for (int i = test_min_size; i < test_max_size; i += 50000)
    {
        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    avltree.add(array + j);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "AVL", i, "ADD", time);

        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    avltree.find(array[j]);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "AVL", i, "FIND", time);

        TIME(
            {
                for (int j = 0; j < 2 * i; ++j)
                {
                    avltree.find(doubled_array[j]);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "AVL", i, "FIND2N", time);

        TIME(avltree.clear(), std::chrono::milliseconds, time)
        printRow(out, "AVL", i, "CLEAR", time);

        for (int j = 0; j < i; ++j)
        {
            avltree.add(array + j);
        }

        TIME(
            {
                for (int j = 0; j < i; ++j)
                {
                    avltree.remove(array[i]);
                }
            },
            std::chrono::milliseconds, time)
        printRow(out, "AVL", i, "REMOVE", time);
    }
}

/**
 * Main функция раннера
 * @param argc Количество аргументов командной строки
 * @param argv[1] Путь к csv файлу для вывода
 * @param argv[2] Количество итераций
 * @param argv[3] Минимальная длина профилирования
 * @param argv[4] Максимальная длина профилирования
 * @return Код возврата
 */
int main(int argc, char **argv)
{
    std::ofstream::sync_with_stdio(false);
    std::ifstream::sync_with_stdio(false);

    if (argc < 5)
    {
        std::cerr << "Wrong amount of arguments detected!"
                  << "\n";
        return 1;
    }

    std::ofstream csv_ostream(argv[1], std::ios_base::app);

    const int test_max_iter = std::stoi(argv[2]);
    const int test_min_size = std::stoi(argv[3]);
    const int test_max_size = std::stoi(argv[4]);

    if (!csv_ostream.good())
    {
        std::cerr << "Couldn't open files!"
                  << "\n";
        return 1;
    }

    csv_ostream << "TAG, SIZE, METHOD, DURATION"
                << "\n";

    DataStruct *array = generateRandomStructs(test_max_size);
    DataStruct *doubled_array = generateRandomStructs(2 * test_max_size);

    for (size_t i = 0; i < test_max_iter; ++i)
    {
        profileArray(array, doubled_array, csv_ostream, test_min_size, test_max_size);
        profileHash(array, doubled_array, csv_ostream, test_min_size, test_max_size);
        profileAVL(array, doubled_array, csv_ostream, test_min_size, test_max_size);
    }

    delete[] array;
    delete[] doubled_array;

    return 0;
}
