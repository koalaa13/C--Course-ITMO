//
// Created by koalaa13 on 6/8/19.
//

#include "file_decompressor.h"
#include "file_writer.h"
#include "file_reader.h"
#include "../library/counter.h"
#include "../library/huffman_tree.h"
#include "../library/decryptor.h"
#include <vector>
#include <cstddef>

void decompress(std::string const &src, std::string const &dst) {
    file_writer writer(dst);
    file_reader reader(src);
    u_ll memory_size = reader.get_u_ll();
    counter cnts;
    for (size_t i = 0; i < MAX_SYMBOL; ++i) {
        cnts.add_data(i, reader.get_u_ll());
    }
    decryptor decoder(cnts);
    while (!reader.eof()) {
        symbol c = reader.get();
        std::vector<symbol> to_print = decoder.decrypt(c, memory_size);
        for (symbol ss : to_print) {
            writer.put(ss);
        }
    }
}