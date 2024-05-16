#ifndef MIPT2024_S_KOSHELEV_A_ALGO_GENERATE_H
#define MIPT2024_S_KOSHELEV_A_ALGO_GENERATE_H

#include "data_struct.h"
#include "test-lib/data/generators/inline_generators.h"

#define MIN_LENGTH 7
#define MAX_LENGTH 20

/**
 * Генератор массива тестовых данных для профиляции
 * @param size Размер массива
 * @return Массив данных
 */
DataStruct *generateRandomStructs(size_t size);

#endif // MIPT2024_S_KOSHELEV_A_ALGO_GENERATE_H
