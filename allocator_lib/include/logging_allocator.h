#ifndef ALLOCATOR_LOGGING_ALLOCATOR_H
#define ALLOCATOR_LOGGING_ALLOCATOR_H

#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>

//#define USE_PRETTY

template<typename T, size_t n_elem>
struct logging_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;


    template<typename U>
    struct rebind {
        using other = logging_allocator<U,n_elem>;
    };

    logging_allocator() = default;
    ~logging_allocator() = default;

    template<typename U>
    logging_allocator(const logging_allocator<U,n_elem>&) {

    }

    pointer allocate(std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if (offset + n > size) {
            std::cout << "offset: " << offset <<" ,n:" << n << ", size:" << size << std::endl;
            std::cout << "Lacking memory for " << (offset + n) - size <<" elements"<< std::endl;
            while (multiplier * n_elem < offset + n) {
                multiplier++;
            }
            memory_pool = nullptr;
            offset = 0;
        }
        if (!memory_pool) {
            auto allocation_size = multiplier * n_elem * sizeof(T);
            memory_pool = reinterpret_cast<pointer>(malloc(allocation_size));
            size = allocation_size/sizeof(T);
            std::cout << "Memory allocated for " << size <<" elements" << std::endl;
            std::cout << "memory_pool_ptr " << memory_pool << std::endl;
        }
        if (!memory_pool) {
            throw std::bad_alloc();
        }
        pointer ptr = memory_pool + offset;
        offset += n;
        std::cout << "offset: " << offset <<" ,n:" << n << ", size:" << size << std::endl;
        return ptr;
    }

    void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if (!p) {
            return;
        }
        offset -= n;
        if (offset != 0) {
            return;
        }
        free(memory_pool);
        memory_pool = nullptr;
        size = 0;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);

    }

    void destroy(T *p) {
#ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~T();
    }

private:
    pointer memory_pool{nullptr};
    size_t offset{0};
    size_t multiplier{1};
    size_t size{0};
};


#endif //ALLOCATOR_LOGGING_ALLOCATOR_H
