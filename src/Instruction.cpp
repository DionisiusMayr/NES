#pragma once
#include <cstdint>
#include <cstdio>

struct Instruction {
    uint8_t opc;
    uint8_t byte1;
    uint8_t byte2;

    Instruction() {
        opc = byte1 = byte2 = 0;
    }

    uint8_t get_size() const {
        switch(opc) {
            case 0x00:
                return 1;
            case 0x69: case 0x65: case 0x75: case 0x61: case 0x71:
                return 2;
            default: // Error: instruction not implemented - stay stuck
                printf("ERROR: get_size() not implemented\n");
                return 0;
        }
    }

    void operator=(uint8_t const opcode) {
        opc = opcode;
        byte1 = 0x00;
        byte2 = 0x00;
    }
};
