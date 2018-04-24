#include <cstdio>

#define _print_inst(s, opcode) printf("0x%02x\t%s\n", opcode, s); break;
namespace opc {
// void _print_inst(char * const s, uint8_t const opcode) {
// printf("0x%02x\t%s\n", opcode, s);
// }

    void print_inst(uint8_t const opcode) {
        switch(opcode) {
            case 0x00: _print_inst("BRK", opcode);
            case 0x04: _print_inst("NOP", opcode);
        }
    }
}