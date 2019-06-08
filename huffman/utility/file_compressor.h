//
// Created by koalaa13 on 6/6/19.
//

#ifndef HUFFMAN_FILE_COMPRESSOR_H
#define HUFFMAN_FILE_COMPRESSOR_H

#include "../library/counter.h"
#include <iostream>
#include <string>
#include "file_reader.h"
#include <vector>
#include "../library/my_consts.h"
#include "../library/huffman_tree.h"

counter get_count(std::string const &src);

void compress(std::string const &src, std::string const &dst);

#endif //HUFFMAN_FILE_COMPRESSOR_H
