//homework project for unit 26 skillfactory.ru

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

int64_t res = 0;

void sum_elements(int* _ptr_array, int _begin, int _part) {
    int64_t buffer = 0;
    for (int i = _begin; i < (_begin + _part); ++i) {
        buffer += _ptr_array[i];
    }
    res += buffer;
}

int main()
{
    int size_array = 1'000'000'000;
    int count_threads = 8;
    int part = size_array / count_threads;
    int begin = 0;

    int* ptr_array = new int[size_array];
    for (int i = 0; i < size_array; ++i) {
        ptr_array[i] = rand() % 10;
    }
    std::cout << "result = " << res << "\n";

    //check start
    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> vector_threads;
    for (int i = 0; i < count_threads; i++) {
        vector_threads.push_back(std::thread(sum_elements, ptr_array, begin, part)
        );
        begin += part;
    }
    std::for_each(vector_threads.begin(), vector_threads.end(), [](std::thread& t)
        { t.join(); });

    //check stop
    auto end = std::chrono::steady_clock::now();

    //print result and metric
    std::cout << "result = " << res << "\n";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds \n";

    delete[] ptr_array;
    return 0;
}
