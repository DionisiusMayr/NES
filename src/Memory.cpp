#ifndef MEMORY_CPP_
#define MEMORY_CPP_

#include <cstdio>
#include <string.h>
#include "utility.cpp"

struct Memory {
    int size;
    uint8_t * at;

    Memory(int s) {
        size = s;
        at = new uint8_t[size];
        memset(at, 0, sizeof(uint8_t) * size);
    }

    // TODO: Overload [] operator.

    void print_mem_interval(int a, int b) const {
        printf("--------------------------\n");
        for (int i = a; i < b; ++i)
            printf("|$%04d| %s|\n", i, dec_hex_bin(at[i]).c_str());
        printf("--------------------------\n");
    }
};

#endif
