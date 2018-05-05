#include <cstdint>
#include <cstdio>
#include "Instruction.cpp"

#define _print_inst(opcode, s) printf("0x%02x\t%s\n", opcode, s); break;

namespace opc {
    void print_inst(Instruction const inst) {
        switch(inst.opc) {
            case 0x00: _print_inst(inst.opc, "BRK")
            case 0x04: _print_inst(inst.opc, "NOP")
            case 0x09: _print_inst(inst.opc, "ORA #oper")
            case 0x0a: _print_inst(inst.opc, "ASL A")
            case 0x18: _print_inst(inst.opc, "CLC")
            case 0x29: _print_inst(inst.opc, "AND #oper")
            case 0x58: _print_inst(inst.opc, "CLI")
            case 0x69: _print_inst(inst.opc, "ADC #oper")
            case 0xb8: _print_inst(inst.opc, "CLV")
            case 0xd8: _print_inst(inst.opc, "CLD")

            default: printf("UNKNOW OPCODE\n");
        }
    }
}
