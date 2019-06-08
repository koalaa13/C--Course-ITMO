//
// Created by koalaa13 on 5/30/19.
//

#include "file_reader.h"

file_reader::file_reader(const std::string &filename) : reader(filename, std::fstream::binary), cur(0), end(0) {
    if (reader.fail()) {
        reader.close();
        throw std::runtime_error("No such file");
    }
}

file_reader::~file_reader() {
    reader.close();
}

symbol file_reader::get() {
    if (cur == end) {
        reader.read(buffer, BUFF_SIZE);
        end = reader.gcount();
        if (end == 0) {
            throw std::runtime_error("Error while reading, it's nothing to read");
        }
        cur = 0;
    }
    return static_cast<symbol>(buffer[cur++]);
}

bool file_reader::eof() {
    return cur == end && reader.peek() == EOF;
}

u_ll file_reader::get_u_ll() {
    u_ll res = 0;
    for (size_t i = 0; i < 8; ++i) {
        res <<= 8ULL;
        res |= get();
    }
    return res;
}

