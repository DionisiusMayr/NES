#include <cstdint>
#include <cstdio>
#include "Instruction.cpp"

#define _print_inst(opcode, s) printf("0x%02x\t%s\n", opcode, s); break;

namespace opc {
    void print_inst(Instruction const inst) {
        switch(inst.opc) {
            case 0x00: _print_inst(inst.opc, "BRK")
            case 0x04: _print_inst(inst.opc, "NOP")
            case 0x69: _print_inst(inst.opc, "ADC #oper")

            default: printf("UNKNOW OPCODE\n");
        }
    }
}
