#include <vector>
#include <map>
#include <iostream>
#include "logging_allocator.h"
#include "simple_allocator.h"
#include "SimpleList.h"

uint64_t factorial(uint64_t num)
{
    return (num > 0) ? num*factorial(num-1) : 1;
}
int main(int, char *[]) {

    try {

        std::map<const int, int> standard_allocated_map;
        for (auto i = 0; i < 10; ++i) {
            standard_allocated_map.emplace(std::pair<const int, int>(i, factorial(i)));
        }
        for (std::pair<const int, int> pair : standard_allocated_map) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }

        std::map<const int, int, std::less<const int>, simple_allocator<std::pair<const int, int>, 10>> custom_preallocated_map;
        for (auto i = 0; i < 10; ++i) {
            custom_preallocated_map.emplace(std::pair<const int, int>(i, factorial(i)));
        }
        for (std::pair<const int, int> pair : custom_preallocated_map) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }

        SimpleList<int> standard_allocated_list;
        for (auto i = 0; i < 10; ++i) {
            standard_allocated_list.pushValue(i);
        }
        for (const auto &elem : standard_allocated_list) {
            std::cout << elem<< std::endl;
        }

        SimpleList<int,simple_allocator<int, 10>> custom_preallocated_list;
        for (auto i = 0; i < 10; ++i) {
            custom_preallocated_list.pushValue(i);
        }
        for (const auto &elem : custom_preallocated_list) {
            std::cout << elem<< std::endl;
        }
    }
    catch (const std::exception& e){
        std::cout<<e.what();
    }

    return 0;
}
