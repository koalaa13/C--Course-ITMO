//
// Created by koalaa13 on 5/30/19.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <stdint-gcc.h>
#include <vector>
#include <sys/param.h>
#include "my_consts.h"
#include "code.h"
#include "counter.h"

class huffman_tree {
    struct node {
        int16_t left_son, right_son;
        u_int16_t rarity;
        u_int16_t id;

        node() : left_son(-1), right_son(-1), rarity(0), id(-1) {};

        explicit node(u_int16_t rar, u_int16_t new_id) : left_son(-1), right_son(-1), rarity(rar), id(new_id) {};

        node(int16_t new_l, int16_t new_r, u_int16_t rar, int16_t new_id) : left_son(new_l), right_son(new_r), rarity(rar), id(new_id) {};

        bool is_leaf() const {
            return left_son == -1 && right_son == -1;
        }
    };

    node cur;
    std::vector<node> g;
    code codes[MAX_SYMBOL];

    void build(counter const &cnts);

    void dfs(node const &v, code cur_code);

    void gen_codes(counter const &cnts);

public:

    explicit huffman_tree(counter const &cnts);

    code get_code(symbol const &c) const;

    u_int16_t jump(bool c);

};

#endif //HUFFMAN_HUFFMAN_TREE_H
