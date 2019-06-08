//
// Created by koalaa13 on 5/30/19.
//

#include "file_writer.h"
#include <cstddef>

file_writer::file_writer(const std::string &filename) : writer(filename, std::ofstream::binary), cur(0) {}

file_writer::~file_writer() {
    writer.write(buffer, cur);
    writer.close();
}

void file_writer::put(symbol const &c) {
    if (cur == BUFF_SIZE) {
        writer.write(buffer, cur);
        cur = 0;
    }
    buffer[cur++] = static_cast<char>(c);
}

void file_writer::put_u_ll(u_ll n) {
    for (ptrdiff_t i = 56; i >= 0; i -= 8) {
        put(n >> i);
    }
}




