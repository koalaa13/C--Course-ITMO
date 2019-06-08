//
// Created by koalaa13 on 6/8/19.
//

#ifndef HUFFMAN_ENCRYPTOR_H
#define HUFFMAN_ENCRYPTOR_H

#include "huffman_tree.h"

class encryptor {
    huffman_tree tree;

public:
    encryptor() = delete;

    explicit encryptor(counter const &cnts);

    code get_code(symbol const &c) const;

    u_int encrypt(symbol const &c, code &to_put) const;

    void add_end(code &to_put) const;
};

#endif //HUFFMAN_ENCRYPTOR_H
