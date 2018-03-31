#include <iostream>
#include "utility.cpp"

using std::cout;
using std::endl;

struct Registers {
    uint8_t a;      // Accumulator
    uint8_t x, y;   // Indexes
    uint16_t pc;    // Program counter
    uint8_t s;      // Stack pointer
    uint8_t p;      // Status register

    Registers() {
        a = x = y = pc = s = p = 0;
    }
    void print_regs() const {
        cout << "---------------------------------------------------" << endl;
        cout << "|a:  " << dec_hex_bin(a) << "   |   pc: " << dec_hex_bin(pc)<< "|" << endl;
        cout << "|x:  " << dec_hex_bin(x) << "   |   s:  " << dec_hex_bin(s) << "|" << endl;
        cout << "|y:  " << dec_hex_bin(y) << "   |   p:  " << dec_hex_bin(p) << "|" << endl;
        cout << "---------------------------------------------------" << endl;
    }
};
