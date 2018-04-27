#include <cstdio>

#define _print_inst(s, opcode) printf("0x%02x\t%s\n", opcode, s); break;
namespace opc {
// void _print_inst(char * const s, uint8_t const opcode) {
// printf("0x%02x\t%s\n", opcode, s);
// }

    void print_inst(uint8_t const opcode) {
        switch(opcode) {
            case 0x69: case 0x65: case 0x75: case 0x6D: case 0x7D: case 0x79:
            case 0x61: case 0x71:
                _print_inst("ADC", opcode);
            case 0x00: _print_inst("BRK", opcode);
            case 0x04: _print_inst("NOP", opcode);
        }
    }
}
