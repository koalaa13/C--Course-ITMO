//
// Created by koalaa13 on 5/31/19.
//

#include "code.h"

code::code() : data(0), len(0) {}

code::code(u_int const &new_code, size_t const &new_len) {
    data = new_code;
    len = new_len;
}

void code::add(bool bit) {
    data |= (static_cast<u_int>(bit) << len);
    ++len;
}

void code::erase() {
    --len;
}

bool code::get(size_t const &ind) const {
    return data & (static_cast<u_int>(1) << ind);
}

void code::clear() {
    data = len = 0;
}

size_t code::length() const {
    return len;
}

u_int code::get_data() const {
    return data;
}

void code::push_back(bool bit) {
    data = (data << 1ULL) | bit;
    len++;
}
