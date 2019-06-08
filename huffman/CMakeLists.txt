cmake_minimum_required(VERSION 3.10.2)
project(huffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffman
        utility/file_reader.h
        library/my_consts.h
        utility/file_reader.cpp
        utility/file_writer.h
        utility/file_writer.cpp
        library/huffman_tree.h
        library/huffman_tree.cpp
        library/counter.cpp
        library/counter.h
        library/code.h
        library/code.cpp
        utility/file_compressor.cpp
        utility/file_compressor.h
        utility/file_decompressor.cpp
        utility/file_decompressor.h
        utility/main.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()