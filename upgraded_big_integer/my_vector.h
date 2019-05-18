//
// Created by koalaa13 on 5/17/19.
//

#ifndef BIG_INTEGER_MY_VECTOR_H
#define BIG_INTEGER_MY_VECTOR_H

#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef unsigned int u_int;

class my_vector {
    static size_t const SMALL_SIZE = 8;
    size_t sz;

    struct big {
        size_t capacity;
        shared_ptr<u_int[]> p;

        big(u_int *ptr, size_t const &cap);
    };

    union any_data {
        u_int small_data[SMALL_SIZE];
        big big_data;

        any_data() {};

        ~any_data() {};
    } union_data;

    bool is_big() const;

    void change_capacity(size_t const &new_cap);

    static size_t get_new_capacity(size_t const &cur_cap);

    size_t get_capacity() const;

    static void swap_big_and_small(any_data &big, any_data &small);

    void divide();

    u_int *data;

public:
    my_vector();

    ~my_vector();

    my_vector(size_t const &new_size);

    my_vector(my_vector const &other);

    void reserve(size_t const &new_cap);

    void resize(size_t const &new_size);

    size_t size() const;

    bool empty() const;

    void push_back(u_int const &val);

    void pop_back();

    u_int &operator[](size_t const &ind);

    u_int const &operator[](size_t const &ind) const;

    my_vector &operator=(my_vector const &other);

    void swap(my_vector &other);

    u_int back();

    friend bool operator==(my_vector const &a, my_vector const &b);

    friend bool operator!=(my_vector const &a, my_vector const &b);
};

#endif //BIG_INTEGER_MY_VECTOR_H
