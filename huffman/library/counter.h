//
// Created by koalaa13 on 5/30/19.
//

#ifndef HUFFMAN_COUNTER_H
#define HUFFMAN_COUNTER_H

#include "my_consts.h"
#include <vector>

class counter {
    u_ll cnt[MAX_SYMBOL];

public:
    counter();

    void add_data(std::vector<symbol> const &symbols);

    void add_data(size_t const &ind, u_ll const &d);

    u_ll get(size_t const &c) const;
};

#endif //HUFFMAN_COUNTER_H
