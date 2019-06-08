//
// Created by koalaa13 on 6/6/19.
//

#include "file_compressor.h"
#include "file_writer.h"

counter get_count(std::string const &filename) {
    counter res;
    file_reader reader(filename);
    std::vector<symbol> data;
    while (!reader.eof()) {
        if (data.size() == BLOCK_DATA_SIZE) {
            res.add_data(data);
            data.clear();
        }
        data.push_back(reader.get());
    }
    res.add_data(data);
    return res;
}

void compress(std::string const &src, std::string const &dst) {
    counter cnts = get_count(src);
    huffman_tree my_tree(cnts);
    u_ll memory_size = 0;
    for (size_t i = 0; i < MAX_SYMBOL; ++i) {
        memory_size += my_tree.get_code(i).length() * cnts.get(i);
    }
    file_writer writer(dst);
    file_reader reader(src);
    writer.put_u_ll(memory_size);
    for (size_t i = 0; i < MAX_SYMBOL; ++i) {
        writer.put_u_ll(cnts.get(i));
    }
    code to_put;
    while (!reader.eof()) {
        symbol c = reader.get();
        code c_code = my_tree.get_code(c);
        size_t len = c_code.length();
        for (size_t i = 0; i < len; ++i) {
            to_put.push_back(c_code.get(i));
            if (to_put.length() == 8) {
                writer.put(to_put.get_data());
                to_put.clear();
            }
        }
    }
    if (to_put.length() > 0) {
        while(to_put.length() < 8) {
            to_put.push_back(false);
        }
    }
    writer.put(to_put.get_data());
}