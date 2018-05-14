#include <cstdint>
#include <cstdio>
#include "Instruction.cpp"

#define _print_inst(opcode, s) printf("0x%02x\t%s\n", opcode, s); break;

namespace opc {
    void print_inst(Instruction const inst) {
        uint8_t opc = inst.opc;
        switch(opc) {
            case 0x00: _print_inst(opc, "BRK")
            case 0x04: _print_inst(opc, "NOP")
            case 0x09: _print_inst(opc, "ORA #oper")
            case 0x0a: _print_inst(opc, "ASL A")
            case 0x18: _print_inst(opc, "CLC")
            case 0x29: _print_inst(opc, "AND #oper")
            case 0x49: _print_inst(opc, "EOR #oper")
            case 0x58: _print_inst(opc, "CLI")
            case 0x69: _print_inst(opc, "ADC #oper")
            case 0x81: _print_inst(opc, "STA (oper,X)")
            case 0x84: _print_inst(opc, "STY oper")
            case 0x85: _print_inst(opc, "STA oper")
            case 0x86: _print_inst(opc, "STX oper")
            case 0x8a: _print_inst(opc, "TXA")
            case 0x8c: _print_inst(opc, "STY oper")
            case 0x8d: _print_inst(opc, "STA oper")
            case 0x8e: _print_inst(opc, "STX oper")
            case 0x91: _print_inst(opc, "STA (oper),Y")
            case 0x94: _print_inst(opc, "STY oper,X")
            case 0x95: _print_inst(opc, "STA oper,X")
            case 0x96: _print_inst(opc, "STX oper,Y")
            case 0x98: _print_inst(opc, "TYA")
            case 0x99: _print_inst(opc, "STA oper,Y")
            case 0x9a: _print_inst(opc, "TXS")
            case 0x9d: _print_inst(opc, "STA oper,X")
            case 0xa0: _print_inst(opc, "LDY #oper")
            case 0xa1: _print_inst(opc, "LDA (oper,X)")
            case 0xa2: _print_inst(opc, "LDX #oper")
            case 0xa4: _print_inst(opc, "LDY oper")
            case 0xa5: _print_inst(opc, "LDA oper")
            case 0xa6: _print_inst(opc, "LDX oper")
            case 0xa8: _print_inst(opc, "TAY")
            case 0xa9: _print_inst(opc, "LDA #oper")
            case 0xaa: _print_inst(opc, "TAX")
            case 0xac: _print_inst(opc, "LDY oper")
            case 0xad: _print_inst(opc, "LDA oper")
            case 0xae: _print_inst(opc, "LDX oper")
            case 0xb1: _print_inst(opc, "LDA (oper),Y")
            case 0xb4: _print_inst(opc, "LDY oper,X")
            case 0xb5: _print_inst(opc, "LDA oper,X")
            case 0xb6: _print_inst(opc, "LDX oper,Y")
            case 0xb8: _print_inst(opc, "CLV")
            case 0xb9: _print_inst(opc, "LDA oper,Y")
            case 0xba: _print_inst(opc, "TSX")
            case 0xbc: _print_inst(opc, "LDY oper,X")
            case 0xbd: _print_inst(opc, "LDA oper,X")
            case 0xbe: _print_inst(opc, "LDX oper,Y")
            case 0xd8: _print_inst(opc, "CLD")
            case 0xe6: _print_inst(opc, "INC oper")
            case 0xee: _print_inst(opc, "INC oper")
            case 0xf6: _print_inst(opc, "INC oper,X")
            case 0xfe: _print_inst(opc, "INC oper,X")
            default: printf("UNKNOW OPCODE\n");
        }
    }
}
