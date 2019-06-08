//
// Created by koalaa13 on 5/31/19.
//

#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include "my_consts.h"
#include <iostream>

class code {
    u_int data;
    size_t len;

public:
    code();

    code(u_int const &new_code, size_t const &new_len);

    void add(bool bit);

    void push_back(bool bit);

    void erase();

    bool get(size_t const &ind) const;

    void clear();

    u_int get_data() const;

    size_t length() const;
};

#endif //HUFFMAN_CODE_H
