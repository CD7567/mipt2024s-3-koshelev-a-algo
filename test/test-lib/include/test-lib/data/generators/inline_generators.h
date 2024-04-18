#ifndef MIPT2024_S_KOSHELEV_A_ALGO_INLINE_GENERATORS_H
#define MIPT2024_S_KOSHELEV_A_ALGO_INLINE_GENERATORS_H

#include <cstddef>
#include <random>

/**
 * Генератор случайного size_t
 * @param lborder Левая граница
 * @param rborder Правая граница
 * @return Случайный size_t
 */
inline size_t genRandomReal(size_t lborder = 0, size_t rborder = SIZE_MAX)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<size_t> distribution(lborder, rborder);

    return distribution(generator);
}

/**
 * Генератор случайной строки строчной латиницей
 * @param size Длина строки
 * @return Случайная строка
 */
inline std::string genRandomString(size_t size)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<char> distribution(97, 122);
    std::string result;

    for (size_t i = 0; i < size; ++i)
    {
        result += distribution(generator);
    }

    return result;
}

#endif // MIPT2024_S_KOSHELEV_A_ALGO_INLINE_GENERATORS_H
