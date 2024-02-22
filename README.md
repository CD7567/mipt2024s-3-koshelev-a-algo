# mipt2024s-3-koshelev-a-algo

![Workflow badge](https://github.com/CD7567/mipt2024s-3-koshelev-a-algo/actions/workflows/cmake-single-platform.yml/badge.svg)

Репозиторий по курсу "Эффективные структуры данных и алгоритмы", МФТИ, ИСА РАН, весна 2024

## Описание фич

- Реализован полноценный `CMake` проект
- Реализовано тестирование с использованием фреймворка `doctest` (`SHARED` подключение)
- Реализована условная компиляция:
    - В профиле `Debug` по умолчанию подключены `clang-tidy`, `address sanitizer` и исполнение тестов как шаг сборки. Профиль предназначен для локальной отладки
    - В профиле `Release` все вышеперечисленное отключено, но флагами `-DDO_COMPILE_TESTS=ON` и `-DDO_AUTORUN_TESTS=ON` можно включить компиляцию и автоисполнение тестов
    - Пример использование флагов для тестирования в профиле `Release` продемонстированы в реализованном пайплайне

- Примеры команд компиляции:

```bash
    cmake -DCMAKE_BUILD_TYPE=Debug -B cmake-build-debug . && cmake --build cmake-build-debug 
```

```bash
    cmake -DCMAKE_BUILD_TYPE=Release -B cmake-build-release . && cmake --build cmake-build-release 
```

## Task 1: 08.02.2024-21.02.2024

- [x] Создать шаблонный класс `CSingleLinkedList<T>`, реализующий односвязный список
- [ ] Создать шаблонный класс `CDualLinkedList<T>`, реализующий двусвязный список
- [x] Написать тесты
