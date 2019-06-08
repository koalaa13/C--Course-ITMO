//
// Created by koalaa13 on 5/30/19.
//

#ifndef HUFFMAN_FILE_READER_H
#define HUFFMAN_FILE_READER_H

#include <fstream>
#include "../library/my_consts.h"

class file_reader {
    std::ifstream reader;
    char buffer[BUFF_SIZE];
    size_t cur, end;

public:
    file_reader() = delete;

    file_reader(std::string const &filename);

    ~file_reader();

    bool eof();

    symbol get();

    u_ll get_u_ll();
};

#endif //HUFFMAN_FILE_READER_H
