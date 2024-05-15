#include <chrono>
#include <format>
#include <iostream>

#define TIME(funcCall, ChronoType, storage)                                                                            \
    {                                                                                                                  \
        auto start = std::chrono::high_resolution_clock::now();                                                        \
        funcCall;                                                                                                      \
        auto end = std::chrono::high_resolution_clock::now();                                                          \
        storage = std::chrono::duration_cast<ChronoType>(end - start).count();                                         \
    }

template <typename... Args> std::string dyn_format(std::string_view format_str, Args &&...args)
{
    return std::vformat(format_str, std::make_format_args(args...));
}

int main(int argc, char **argv)
{
    std::cout << "Hello world!" << std::endl;
}
