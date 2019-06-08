//
// Created by koalaa13 on 5/30/19.
//

#ifndef HUFFMAN_MY_CONSTS_H
#define HUFFMAN_MY_CONSTS_H

#include <stdlib.h>

typedef unsigned char symbol;
typedef unsigned long long u_ll;
typedef unsigned int u_int;

size_t const BUFF_SIZE = static_cast<size_t>(1 << 15);
size_t const MAX_SYMBOL = 256;
size_t const BLOCK_DATA_SIZE = 256;
size_t const MAX_CODE_LEN = 8;

#endif //HUFFMAN_MY_CONSTS_H
