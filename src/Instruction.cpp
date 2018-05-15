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
            case 0xaa:  // TAX
            case 0xa8:  // TAY
            case 0xba:  // TSX
            case 0x8a:  // TXA
            case 0x9a:  // TXS
            case 0x98:  // TYA
            case 0x48:  // PHA
            case 0x08:  // PHP
            case 0x68:  // PLA
            case 0x28:  // PLP
                return 1;
            case 0x69: case 0x65: case 0x75: case 0x61: case 0x71:  // ADC
            case 0x29: case 0x25: case 0x35: case 0x21: case 0x31:  // AND
            case 0x06: case 0x16:   // ASL
            case 0x09: case 0x05: case 0x15: case 0x01: case 0x11:  // ORA
            case 0x49: case 0x45: case 0x55: case 0x41: case 0x51:  // EOR
            case 0xe6: case 0xf6:   // INC
            case 0xa9: case 0xa5: case 0xb5: case 0xa1: case 0xb1:  // LDA
            case 0x85: case 0x95: case 0x81: case 0x91: // STA
            case 0xa2: case 0xa6: case 0xb6:    // LDX
            case 0xa0: case 0xa4: case 0xb4:    // LDY
            case 0x86: case 0x96:   // STX
            case 0x84: case 0x94:   // STY
                return 2;
            case 0xee: case 0xff:   // INC
            case 0xad: case 0xbd: case 0xb9:    // LDA
            case 0x8d: case 0x9d: case 0x99:    // STA
            case 0xae: case 0xbe:   // LDX
            case 0xac: case 0xbc:   // LDY
            case 0x8e:  // STX
            case 0x8c:  // STY
                return 3;
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
