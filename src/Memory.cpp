#ifndef MEMORY_CPP_
#define MEMORY_CPP_

#include <cstdio>
#include <string.h>
#include "Opcodes.cpp"
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

    void print_mem_interval(int a, int b, bool complete_mode) const {
        printf("--------------------------\n");
        for (int i = a; i <= b; ++i) {
            printf("|$%04x| %s| ", i, dec_hex_bin(at[i]).c_str());
            if (complete_mode)
                opc::print_inst(Instruction(at[i]));
            printf("\n");
        }

        printf("--------------------------\n");
    }
};

#endif
