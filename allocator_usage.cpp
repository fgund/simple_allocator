#include <vector>
#include <map>
#include <iostream>
#include "logging_allocator.h"
#include "simple_allocator.h"

uint64_t factorial(uint64_t num)
{
    return (num > 0) ? num*factorial(num-1) : 1;
}
int main(int, char *[]) {

    try {
        std::map<const int, int, std::less<int>, simple_allocator<std::pair<const int, int>, 10>> m{};
        for (auto i = 0; i < 10; ++i) {
            std::cout << m.size() << std::endl;
            auto p = std::pair<const int, int>(i, factorial(i));
            m.emplace(std::move(p));
        }
        for (std::pair<const int, int> pair : m) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }
    catch (const std::exception& e){
        std::cout<<e.what();
    }

    return 0;
}
