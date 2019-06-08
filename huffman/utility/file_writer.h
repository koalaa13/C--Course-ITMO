//
// Created by koalaa13 on 5/30/19.
//

#ifndef HUFFMAN_FILE_WRITER_H
#define HUFFMAN_FILE_WRITER_H

#include <fstream>
#include "../library/my_consts.h"
#include "../library/code.h"
#include <vector>

class file_writer {
    std::ofstream writer;
    char buffer[BUFF_SIZE];
    size_t cur;

public:
    file_writer() = delete;

    file_writer(std::string const &filename);

    ~file_writer();

    void put(symbol const &c);

    void put_u_ll(u_ll n);
};

#endif //HUFFMAN_FILE_WRITER_H
