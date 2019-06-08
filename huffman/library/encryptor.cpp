//
// Created by koalaa13 on 6/8/19.
//

#include "encryptor.h"

encryptor::encryptor(const counter &cnts) : tree(cnts) {}

code encryptor::get_code(symbol const &c) const {
    return tree.get_code(c);
}

u_int encryptor::encrypt(symbol const &c, code &to_put) const {
    code c_code = tree.get_code(c);
    u_int res = MAX_SYMBOL;
    for (size_t i = 0; i < c_code.length(); ++i) {
        to_put.push_back(c_code.get(i));
        if (to_put.length() == 8) {
            res = to_put.get_data();
            to_put.clear();
        }
    }
    return res;
}

void encryptor::add_end(code &to_put) const {
    if (to_put.length() > 0) {
        while(to_put.length() < 8) {
            to_put.push_back(false);
        }
    }
}


