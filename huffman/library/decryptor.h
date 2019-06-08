//
// Created by koalaa13 on 6/8/19.
//

#ifndef HUFFMAN_DECRYPTOR_H
#define HUFFMAN_DECRYPTOR_H

#include "huffman_tree.h"
#include "counter.h"

class decryptor {
    huffman_tree tree;
public:
    decryptor() = delete;

    explicit decryptor(counter const &cnts);

    std::vector<symbol> decrypt(symbol const &c, u_ll &memory_size);
};

#endif //HUFFMAN_DECRYPTOR_H
