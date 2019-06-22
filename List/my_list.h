//
// Created by koalaa13 on 6/22/19.
//

#ifndef EXAM_MY_LIST_H
#define EXAM_MY_LIST_H

#include <iterator>
#include <algorithm>

template<typename T>
class my_list {
    struct node_base {
        node_base *next;
        node_base *prev;

        node_base() noexcept {
            next = this;
            prev = this;
        }
    };

    struct node : node_base {
        T value;

        node(T const &val) : value(val) {}
    };

    node_base fake;

    template<typename U>
    class my_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
        node_base *data;

        friend my_list;

        explicit my_iterator(node_base *new_data) : data(new_data) {}

    public:

        my_iterator() = default;

        my_iterator(my_iterator<T> const &other) : data(other.data) {};

        my_iterator &operator=(my_iterator const &other) = default;

        U &operator*() const {
            return static_cast<node *>(data)->value;
        }

        U *operator->() const {
            return &static_cast<node *>(data)->value;
        }

        my_iterator &operator++() {
            data = data->next;
            return *this;
        }

        my_iterator operator++(int) {
            my_iterator copy = *this;
            ++(*this);
            return copy;
        }

        my_iterator &operator--() {
            data = data->prev;
            return (*this);
        }

        my_iterator operator--(int) {
            my_iterator copy = *this;
            --(*this);
            return copy;
        }

        friend bool operator==(my_iterator const &a, my_iterator const &other) noexcept {
            return a.data == other.data;
        }

        friend bool operator!=(my_iterator const &a, my_iterator const &other) noexcept {
            return a.data != other.data;
        }
    };

public:

    typedef T value_type;
    typedef my_iterator<T> iterator;
    typedef my_iterator<T const> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    my_list() noexcept : fake() {}

    my_list(my_list const &other) : my_list() {
        for (T const &i : other) {
            push_back(i);
        }
    }

    ~my_list() {
        clear();
    }

    my_list<T> &operator=(my_list<T> const &other) {
        if (this == &other) {
            return *this;
        }
        my_list<T> copy(other);
        swap(*this, copy);
        return *this;
    }

    bool empty() const noexcept {
        return fake.next == &fake;
    }

    iterator begin() noexcept {
        return iterator(fake.next);
    }

    const_iterator begin() const noexcept {
        return const_iterator(const_cast<node_base *>(fake.next));
    }

    iterator end() noexcept {
        return iterator(&fake);
    }

    const_iterator end() const noexcept {
        return const_iterator(const_cast<node_base *>(&fake));
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    template<typename InputIterator>
    iterator insert(InputIterator pos, T const &elem) {
        node *new_node = new node(elem);
        node *data = static_cast<node *>(pos.data);
        new_node->prev = data->prev;
        new_node->next = data;
        data->prev->next = new_node;
        data->prev = new_node;
        return iterator(new_node);
    }

    template<typename InputIterator>
    iterator erase(InputIterator pos) {
        node *data = static_cast<node *>(pos.data);
        data->next->prev = data->prev;
        data->prev->next = data->next;
        iterator res(pos.data->next);
        delete data;
        return res;
    }

    void push_back(T const elem) {
        insert(const_iterator(&fake), elem);
    }

    void pop_back() noexcept {
        erase(--end());
    }

    void push_front(T const elem) {
        insert(begin(), elem);
    }

    void pop_front() noexcept {
        erase(begin());
    }

    void clear() noexcept {
        while (!empty()) {
            pop_back();
        }
    }

    T &back() {
        return static_cast<node *>(fake.prev)->value;
    }

    T const &back() const noexcept {
        return static_cast<node *>(fake.prev)->value;
    }

    T &front() {
        return static_cast<node *>(fake.next)->value;
    }

    T const &front() const noexcept {
        return static_cast<node *>(fake.next)->value;
    }

    void splice(const_iterator pos, my_list &other, const_iterator first, const_iterator second) {
        if (first == second) {
            return;
        }
        node *node_pos = static_cast<node *>(pos.data->prev);
        node *node_first = static_cast<node *>(first.data);
        node *node_second = static_cast<node *>(second.data->prev);
        node_second->next->prev = node_first->prev;
        node_first->prev->next = node_second->next;
        node_second->next = node_pos->next;
        node_pos->next->prev = node_second;
        node_pos->next = node_first;
        node_first->prev = node_pos;
    }

    template<typename U>
    friend void swap(my_list<U> &a, my_list<U> &b);
};

template<typename U>
void swap(my_list<U> &a, my_list<U> &b) {
    if (a.empty()) {
        a.fake.next = &b.fake;
        a.fake.prev = &b.fake;
    } else {
        a.fake.next->prev = &b.fake;
        a.fake.prev->next = &b.fake;
    }
    if (b.empty()) {
        b.fake.next = &a.fake;
        b.fake.prev = &a.fake;
    } else {
        b.fake.next->prev = &a.fake;
        b.fake.prev->next = &a.fake;
    }
    std::swap(a.fake, b.fake);
}


#endif //EXAM_MY_LIST_H
