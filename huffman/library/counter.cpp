//
// Created by koalaa13 on 5/30/19.
//

#include <cstring>
#include "counter.h"

counter::counter() {
    memset(cnt, 0, MAX_SYMBOL * sizeof(u_ll));
}

void counter::add_data(std::vector<symbol> const &symbols) {
    for (symbol c : symbols) {
        cnt[c]++;
    }
}

u_ll counter::get(size_t const &c) const {
    return cnt[c];
}

void counter::add_data(size_t const &ind, const u_ll &d) {
    cnt[ind] += d;
}

