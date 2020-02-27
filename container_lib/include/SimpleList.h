#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

#include <cstddef>
#include <memory>

// @class
// Element of the linked list
template<typename T>
struct Node {
    Node* next;
    T data;
};

template <typename T>
struct ListIterator {
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::forward_iterator_tag;

    using _self = ListIterator<T>;
    Node<T>* _node;

    // Default constructor
    ListIterator() : _node(nullptr) {};

    // Parametrized constructor
    ListIterator(Node<T>* pNode) : _node(pNode) {};

    // Get a reference for an object
    reference operator*() const {
        return _node->data;
    }

    // Get a pointer for an object
    pointer operator->() const {
        return &(_node->data);
    }

    // Increment - next element of the container
    _self& operator++() {
        if (_node == nullptr) {
            return *this;
        }
        else {
            _node = _node->next;
        }
        return *this;
    }

    // Comparison operators
    bool operator==(const _self& rhs) const {
        return _node == rhs._node;
    }

    bool operator!=(const _self& rhs) const {
        return _node != rhs._node;
    }
};

template<typename T, typename Alloc = std::allocator<T>>
class SimpleList {
    using value_type = T;
    using pointer = T*;
    using reference = const T&;

public:
    SimpleList(){
    }
    ~SimpleList(){
        auto current = head;
        while (current != nullptr) {
            auto p_rm = current;
            current = current->next;
            alloc.destroy(p_rm);
            alloc.deallocate(p_rm, 1);
        }
    }
    void pushValue(value_type value){
        Node<T> *new_node = alloc.allocate(1);
        alloc.construct(new_node);
        new_node->data = value;
        new_node->next = head;
        head = new_node;
    }

    ListIterator<T> begin() const noexcept {
        return ListIterator<T>(head);
    }

    ListIterator<T> end() noexcept {
        return ListIterator<T>();
    }

private:
    Node<T>* head = nullptr;
    using Allocator = typename Alloc::template rebind< Node<T> >::other;
    Allocator alloc;
};


#endif //SIMPLE_LIST_H
