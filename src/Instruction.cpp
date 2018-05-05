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
            case 0x0a:  // ASL
            case 0x18:  // CLC
            case 0x58:  // CLI
            case 0xb8:  // CLV
            case 0xd8:  // CLD
                return 1;
            case 0x69: case 0x65: case 0x75: case 0x61: case 0x71:  // ADC
            case 0x29: case 0x25: case 0x35: case 0x21: case 0x31:  // AND
            case 0x06: case 0x16:   // ASL
            case 0x09: case 0x05: case 0x15: case 0x01: case 0x11:  // ORA
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
