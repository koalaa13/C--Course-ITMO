//
// Created by koalaa13 on 5/30/19.
//

#include "huffman_tree.h"
#include "set"

void huffman_tree::build(counter const &cnts) {
    using std::set;
    using std::pair;

    g.resize(MAX_SYMBOL);
    u_int16_t sz = 0;
    set<pair<u_ll, u_int16_t >> ms;
    for (size_t i = 0; i < MAX_SYMBOL; ++i) {
        ms.insert(std::make_pair(cnts.get(i), sz));
        g[sz] = node(cnts.get(i), sz);
        sz++;
    }
    while (ms.size() > 1) {
        pair<u_ll, u_int16_t> x = *ms.begin();
        ms.erase(ms.begin());
        pair<u_ll, u_int16_t> y = *ms.begin();
        ms.erase(ms.begin());
        g.emplace_back(x.second, y.second, x.first + y.first, sz);
        ms.insert(std::make_pair(x.first + y.first, sz++));
    }
}

void huffman_tree::gen_codes(counter const &cnts) {
    build(cnts);
    dfs(g.back(), code());
}

void huffman_tree::dfs(huffman_tree::node const &v, code cur_code) {
    if (v.is_leaf()) {
        codes[v.id] = cur_code;
        return;
    }
    cur_code.add(false);
    dfs(g[v.left_son], cur_code);
    cur_code.erase();
    cur_code.add(true);
    dfs(g[v.right_son], cur_code);
}

code huffman_tree::get_code(symbol const &c) const {
    return codes[c];
}

huffman_tree::huffman_tree(counter const &cnts) {
    gen_codes(cnts);
    cur = g.back();
}

u_int16_t huffman_tree::jump(bool c) {
    if (cur.is_leaf()) {
        cur = g.back();
    }
    if (c) {
        cur = g[cur.right_son];
    } else {
        cur = g[cur.left_son];
    }
    return cur.is_leaf() ? cur.id : MAX_SYMBOL;
}
