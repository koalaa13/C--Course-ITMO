//
// Created by koalaa13 on 6/8/19.
//

#include "file_decompressor.h"
#include "file_writer.h"
#include "file_reader.h"
#include "../library/counter.h"
#include "../library/huffman_tree.h"
#include <vector>

void decompress(std::string const &src, std::string const &dst) {
    file_writer writer(dst);
    file_reader reader(src);
    u_ll memory_size = reader.get_u_ll();
    counter cnts;
    for (size_t i = 0; i < MAX_SYMBOL; ++i) {
        cnts.add_data(i, reader.get_u_ll());
    }
    huffman_tree my_tree(cnts);
    while (!reader.eof()) {
        symbol c = reader.get();
        if (memory_size >= 8) {
            memory_size -= 8;
            for (ptrdiff_t i = 7; i >= 0; --i) {
                bool to_go = c & (1 << i);
                u_int16_t res = my_tree.jump(to_go);
                if (res < MAX_SYMBOL) {
                    writer.put(static_cast<symbol>(res));
                }
            }
        } else {
            for (size_t i = 0, bit_id = 7; i < memory_size; ++i, --bit_id) {
                bool to_go = c & (1 << bit_id);
                u_int16_t res = my_tree.jump(to_go);
                if (res < MAX_SYMBOL) {
                    writer.put(static_cast<symbol>(res));
                }
            }
        }
    }
}