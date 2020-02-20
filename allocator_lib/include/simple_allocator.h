#ifndef ALLOCATOR_SIMPLE_ALLOCATOR_H
#define ALLOCATOR_SIMPLE_ALLOCATOR_H

#include <cstddef>

template<typename T, size_t n_elem>
struct simple_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = simple_allocator<U, n_elem>;
    };

    simple_allocator() = default;
    ~simple_allocator() = default;

    template<typename U>
    simple_allocator(const simple_allocator<U, n_elem>&) {
    }

    pointer allocate(std::size_t n) {
        if (offset + n > size) {
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
        }
        if (!memory_pool) {
            throw std::bad_alloc();
        }
        pointer ptr = memory_pool + offset;
        offset += n;
        return ptr;
    }

    void deallocate(T *p, std::size_t n) {
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
        new(p) U(std::forward<Args>(args)...);

    };

    void destroy(T *p) {
        p->~T();
    }

private:
    pointer memory_pool{nullptr};
    size_t offset{0};
    size_t multiplier{1};
    size_t size{0};
};


#endif //ALLOCATOR_SIMPLE_ALLOCATOR_H
