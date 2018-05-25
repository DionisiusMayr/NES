#ifndef REGISTERS_CPP_
#define REGISTERS_CPP_

#include <iostream>
#include <bitset>
#include "utility.cpp"

using std::cout;
using std::endl;

// TODO: check how to implement this properly
#define _unset_register(p) p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; \
                           p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0;

struct Registers {
    uint8_t a;      // Accumulator
    uint8_t x, y;   // Indexes
    uint8_t s;      // Stack pointer
    uint16_t pc;    // Program counter
    std::bitset<8> p; //Status register

    Registers(uint8_t stack, uint16_t starting_pc) : a(0), x(0), y(0), s(stack), pc(starting_pc) {
        _unset_register(p);
    }

    void print_regs() const {
        uint8_t aux = pc >> 8;
        cout << "-------d---h------b------------------d---h------b----" << endl;
        cout << "|a:  " << dec_hex_bin(a) << "   |   pc_h: " << dec_hex_bin(aux)<< "|" << endl;
        cout << "|x:  " << dec_hex_bin(x) << "   |   pc_l: " << dec_hex_bin(pc) << "|" << endl;
        cout << "|y:  " << dec_hex_bin(y) << "   |   s:    " << dec_hex_bin(s) << "|" << endl;
        cout << "|                        |   p:    " << dec_hex_bin(p.to_ulong()) << "|" << endl;
        cout << "--------------------------------------------nv bdizc-" << endl;
    }
};

#endif
