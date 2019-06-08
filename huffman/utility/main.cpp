//
// Created by koalaa13 on 6/8/19.
//

#include <iostream>
#include "file_compressor.h"
#include "file_decompressor.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Wrong input.\nExpected format: mode(-c to compress or -d to decompress), SRC file, DST file.\n";
        return 0;
    }
    string const mode = argv[1];
    string const src = argv[2];
    string const dst = argv[3];
    u_ll start_time = 0, finish_time = 0;
    if (mode == "-c") {
        cout << "Compressing file, wait for some time\n";
        start_time = clock();
        try {
            compress(src, dst);
        } catch (runtime_error &e) {
            cout << "Error while compressing " << src << ".\n";
            cout << e.what();
            return 0;
        }
        finish_time = clock();
        cout << "Successfully compressed file " << src << " in " << fixed << static_cast<double>(finish_time - start_time) /
                static_cast<double>(CLOCKS_PER_SEC) << '\n';
    } else {
        if (mode == "-d") {
            cout << "Decompressing file, wait for some time\n";
            start_time = clock();
            try {
                decompress(src, dst);
            } catch (runtime_error &e) {
                cout << "Error while decompressing " << src << ".\n";
                cout << e.what();
                return 0;
            }
            finish_time = clock();
            cout << "Successfully decompressed file " << src << " in " << fixed << static_cast<double>(finish_time - start_time) /
                                                                                 static_cast<double>(CLOCKS_PER_SEC) << '\n';
        } else {
            cout << "Incorrect mode.\nSupports only -c or -d.";
        }
    }

    return 0;
}