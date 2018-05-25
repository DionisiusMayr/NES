#include "Registers.cpp"
#include "Memory.cpp"
#include "Opcodes.cpp"
#include "Instruction.cpp"
#include "utility.cpp"
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <fstream>

#define MEM_SIZE (1 << 16)
#define PROGRAM "./programs/test.6502"
#define _zero(byte) (byte == 0 ? 1 : 0);
#define _sign(byte) (byte & 0b10000000 ? 1 : 0);
#define _carry(integer) (integer & 0b100000000 ? 1 : 0);

class Processor {
private:
    Registers r;
    Memory    m;
    Instruction instr;

    void fetch() {
        instr = m.at[r.pc];
        instr.byte1 = m.at[r.pc + 1];
        instr.byte2 = m.at[r.pc + 2];
        r.pc += instr.get_size();
    }

    void load() {
        uint8_t op1 = instr.byte1;
        uint8_t op2 = instr.byte2;
        int16_t addr;

        switch (instr.opc) {
            /* LDA */
            case 0xa9:  // LDA #oper
                r.a = op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xa5:  // LDA oper
                r.a = m.at[op1];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xb5:  // LDA oper,X
                r.a = m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xad:  // LDA oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[addr];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xbd:  // LDA oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xb9:  // LDA oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[addr + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xa1:  // LDA (oper,X)
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[m.at[op1 + r.x]];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xb1:  // LDA (oper),Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[m.at[op1] + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;

                /* LDX */
            case 0xa2:  // LDX #oper
                r.x = op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xa6:  // LDX oper
                r.x = m.at[op1];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xb6:  // LDX oper,Y
                r.x = m.at[op1 + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xae:  // LDX oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.x = m.at[addr];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xbe:  // LDX oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.x = m.at[addr + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;

                /* LDY */
            case 0xa0:  // LDY #oper
                r.y = op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xa4:  // LDY oper
                r.y = m.at[op1];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xb4:  // LDY oper,X
                r.y = m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xac:  // LDY oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.y = m.at[addr];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0xbc:  // LDY oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                r.y = m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
        }
    }

    void sta() {
        uint8_t op1 = instr.byte1;
        uint8_t op2 = instr.byte2;
        int16_t addr;

        switch (instr.opc) {
            /* STA */
            case 0x85:  // STA oper
                m.at[op1] = r.a;
                break;
            case 0x95:  // STA oper,X
                m.at[op1 + r.x] = r.a;
                break;
            case 0x8d:  // STA oper
                addr = ((uint16_t)op1 << 8) | op2;
                m.at[addr] = r.a;
                break;
            case 0x9d:  // STA oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                m.at[addr + r.x] = r.a;
                break;
            case 0x99:  // STA oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                m.at[addr + r.y] = r.a;
                break;
            case 0x81:  // STA (oper,X)
                m.at[m.at[op1 + r.x]] = r.a;
                break;
            case 0x91:  // STA (oper),Y
                m.at[m.at[op1] + r.y] = r.a;
                break;

            /* STX */
            case 0x86:  // STX oper
                m.at[op1] = r.x;
                break;
            case 0x96:  // STX oper,Y
                m.at[op1 + r.y] = r.x;
                break;
            case 0x8e:  // STX oper
                addr = ((uint16_t)op1 << 8) | op2;
                m.at[addr] = r.x;
                break;

            /* STY */
            case 0x84:  // STY oper
                m.at[op1] = r.y;
                break;
            case 0x94:  // STY oper,X
                m.at[op1 + r.x] = r.y;
                break;
            case 0x8c:  // STY oper
                addr = ((uint16_t)op1 << 8) | op2;
                m.at[addr] = r.y;
                break;
        }
    }

    void tra() {
        switch (instr.opc) {
            case 0xaa:  // TAX
                r.x = r.a;
                r.p[NEGATIVE] = _sign(r.x);
                r.p[ZERO]     = _zero(r.x);
                break;
            case 0xa8:  // TAY
                r.y = r.a;
                r.p[NEGATIVE] = _sign(r.y);
                r.p[ZERO]     = _zero(r.y);
                break;
            case 0xba:  // TSX
                r.x = r.s;
                r.p[NEGATIVE] = _sign(r.x);
                r.p[ZERO]     = _zero(r.x);
                break;
            case 0x8a:  // TXA
                r.a = r.x;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x9a:  // TXS
                r.s = r.x;
                r.p[NEGATIVE] = _sign(r.s);
                r.p[ZERO]     = _zero(r.s);
                break;
            case 0x98:  // TYA
                r.a = r.y;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
        }
    }

    void data_transfers() {
        switch (instr.opc) {
            // LDA
            case 0xa9: case 0xa5: case 0xb5: case 0xad: case 0xbd: case 0xb9:
            case 0xa1: case 0xb1:
            // LDX
            case 0xa2: case 0xa6: case 0xb6: case 0xae: case 0xbe:
            // LDY
            case 0xa0: case 0xa4: case 0xb4: case 0xac: case 0xbc:
                load(); break;

            // STA
            case 0x85: case 0x95: case 0x8d: case 0x9d: case 0x99: case 0x81:
            case 0x91:
            // STX
            case 0x86: case 0x96: case 0x8e:
            // STY
            case 0x84: case 0x94: case 0x8c:
                sta(); break;

            //   TAX        TAY        TSX        TXA        TXS        TYA
            case 0xaa: case 0xa8: case 0xba: case 0x8a: case 0x9a: case 0x98:
                tra(); break;
        }
    }

    void stack_operations() {
        int16_t addr;

        switch (instr.opc) {
            case 0x48:  // PHA
                addr = ((uint16_t)0x0100) | r.s;
                m.at[addr] = r.a;
                --r.s;
                break;
            case 0x08:  // PHP
                addr = ((uint16_t)0x0100) | r.s;
                m.at[addr] = r.p.to_ulong();
                --r.s;
                break;
            case 0x68:  // PLA
                ++r.s;
                addr = ((uint16_t)0x0100) | r.s;
                r.a = m.at[addr];

                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x28:  // PLP
                ++r.s;
                addr = ((uint16_t)0x0100) | r.s;
                r.p = m.at[addr];
                break;
        }
    }

    void inc_dec() {
        uint8_t op1 = instr.byte1;
        uint8_t op2 = instr.byte2;
        uint8_t aux;
        int16_t addr;

        switch (instr.opc) {
            case 0xe6:  // INC oper
                aux = ++m.at[op1];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xf6:  // INC oper,X
                aux = ++m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xee:  // INC oper
                addr = ((uint16_t)op1 << 8) | op2;
                aux = ++m.at[addr];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xfe:  // INC oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                aux = ++m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xe8:  // INX
                ++r.x;
                r.p[NEGATIVE] = _sign(r.x);
                r.p[ZERO]     = _zero(r.x);
                break;
            case 0xc8:  // INY
                ++r.y;
                r.p[NEGATIVE] = _sign(r.y);
                r.p[ZERO]     = _zero(r.y);
                break;

            case 0xc6:  // DEC oper
                aux = --m.at[op1];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xd6:  // DEC oper,X
                aux = --m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xce:  // DEC oper
                addr = ((uint16_t)op1 << 8) | op2;
                aux = --m.at[addr];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xde:  // DEC oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                aux = --m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xca:  // DEX
                --r.x;
                r.p[NEGATIVE] = _sign(r.x);
                r.p[ZERO]     = _zero(r.x);
                break;
            case 0x88:  // DEY
                --r.y;
                r.p[NEGATIVE] = _sign(r.y);
                r.p[ZERO]     = _zero(r.y);
                break;
        }
    }

    void logical() {
        uint8_t op1 = instr.byte1;
        uint8_t op2 = instr.byte2;
        int16_t addr;

        switch (instr.opc) {
            /* AND */
            case 0x29:  // AND #oper
                r.a &= op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x25:  // AND oper
                r.a &= m.at[op1];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x35:  // AND oper,X
                r.a &= m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x2d:  // AND oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.a &= m.at[addr];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x3d:  // AND oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                r.a &= m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x39:  // AND oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.a &= m.at[addr + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x21:  // AND (oper,X)
                r.a &= m.at[m.at[op1 + r.x]];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x31:  // AND (oper),Y
                r.a &= m.at[m.at[op1] + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;

            /* ORA */
            case 0x09:  // ORA #oper
                r.a |= op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x05:  // ORA oper
                r.a |= m.at[op1];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x15:  // ORA oper,X
                r.a |= m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x01:  // ORA (oper,X)
                addr = ((uint16_t)op1 << 8) | op2;
                r.a |= m.at[addr];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x11:  // ORA (oper),Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.a |= m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x0d:  // ORA oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.a |= m.at[addr + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x1d:  // ORA oper,X
                r.a |= m.at[m.at[op1 + r.x]];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x19:  // ORA oper,Y
                r.a |= m.at[m.at[op1] + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;

            /* EOR */
            case 0x49:  // EOR #oper
                r.a ^= op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x45:  // EOR oper
                r.a ^= m.at[op1];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x55:  // EOR oper,X
                r.a ^= m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x4d:  // EOR oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.a ^= m.at[addr];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x5d:  // EOR oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                r.a ^= m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x59:  // EOR oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.a ^= m.at[addr + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x41:  // EOR (oper,X)
                r.a ^= m.at[m.at[op1 + r.x]];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x51:  // EOR (oper),Y
                r.a ^= m.at[m.at[op1] + r.y];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
        }
    }

    void data_processing() {
        uint8_t op1 = instr.byte1;
            // ADC
            // SBC
            // CLC
        inc_dec();
        logical();

        switch (instr.opc) {
            int int_res;
            case 0x0a:  // ASL A
                r.p[CARRY]    = r.a && 0x80;
                r.a = r.a << 1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x18:  // CLC
                r.p[CARRY] = 0;
                break;
            case 0x58:  // CLI
                r.p[IRQ] = 0;
                break;
            case 0x69:  // ADC #oper
                int_res = int(r.a) + op1 + r.p[CARRY];
                r.a = r.a + op1 + r.p[CARRY];
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                r.p[CARRY]    = _carry(int_res);
                // TODO: implement correct overflow flag
                r.p[OVERFLOW] = r.p[CARRY] ^ r.p[NEGATIVE];
                break;
            case 0xb8:  // CLV
                r.p[OVERFLOW] = 0;
                break;
            case 0xd8:  // CLD
                r.p[DECIMAL] = 0;
                break;
        }
    }

    void comp_branch() {
        uint8_t op1 = instr.byte1;
        uint8_t op2 = instr.byte2;
        int16_t addr;
        uint8_t aux;
        int8_t signed_op1 = 0 | op1;   // TODO: not sure if this is necessary

        switch (instr.opc) {
            case 0x30:  // BMI oper
                if (r.p[NEGATIVE] == 1)
                    r.pc += signed_op1 - 2;
                break;
            case 0x10:  // BPL oper
                if (r.p[NEGATIVE] == 0)
                    r.pc += signed_op1 - 2;
                break;
            case 0x90:  // BCC oper
                if (r.p[CARRY] == 0)
                    r.pc += signed_op1 - 2;
                break;
            case 0xb0:  // BCS oper
                if (r.p[CARRY] == 1)
                    r.pc += signed_op1 - 2;
                break;
            case 0xf0:  // BEQ oper
                if (r.p[ZERO] == 1)
                    r.pc += signed_op1 - 2;
                break;
            case 0xd0:  // BNE oper
                if (r.p[ZERO] == 0)
                    r.pc += signed_op1 - 2;
                break;
            case 0x50:  // BVC oper
                if (r.p[OVERFLOW] == 0)
                    r.pc += signed_op1 - 2;
                break;
            case 0x70:  // BVS oper
                if (r.p[OVERFLOW] == 1)
                    r.pc += signed_op1 - 2;
                break;
            case 0x4c:  // JMP oper
                r.pc = op1;
                break;
            case 0x6c:  // JMP (oper)
                // TODO: implement this
                break;
            case 0x20:  // JSR oper
                // TODO: implement this
                break;
            case 0x40:  // RTI
                // TODO: implement this
                break;
            case 0x60:  // RTS
                // TODO: implement this
                break;
            case 0x24:  // BIT oper
                aux = m.at[op1];
                r.p[NEGATIVE] = aux & 0b10000000 ? 1 : 0;
                r.p[OVERFLOW] = aux & 0b01000000 ? 1 : 0;
                r.p[ZERO]     = aux & r.a ? 1 : 0;
                break;
            case 0x2c:  // BIT oper
                addr = ((uint16_t)op1 << 8) | op2;
                aux = m.at[addr];
                r.p[NEGATIVE] = aux & 0b10000000 ? 1 : 0;
                r.p[OVERFLOW] = aux & 0b01000000 ? 1 : 0;
                r.p[ZERO]     = aux & r.a ? 1 : 0;
                break;
            case 0xc9:  // CMP #oper
                aux = r.a - op1;
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= op1;
                break;
            case 0xc5:  // CMP oper
                aux = r.a - m.at[op1];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[op1];
                break;
            case 0xd5:  // CMP oper,X
                aux = r.a - m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[op1 + r.x];
                break;
            case 0xcd:  // CMP oper
                addr = ((uint16_t)0x0100) | r.s;
                aux = r.a - m.at[addr];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[addr];
                break;
            case 0xdd:  // CMP oper,X
                addr = ((uint16_t)0x0100) | r.s;
                aux = r.a - m.at[addr + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[addr + r.x];
                break;
            case 0xd9:  // CMP oper,Y
                addr = ((uint16_t)0x0100) | r.s;
                aux = r.a - m.at[addr + r.y];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[addr + r.y];
                break;
            case 0xc1:  // CMP (oper,X)
                aux = r.a - m.at[m.at[op1 + r.x]];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[m.at[op1 + r.x]];
                break;
            case 0xd1:  // CMP (oper),Y
                aux = r.a - m.at[m.at[op1] + r.y];    // TODO: check all of those offsets
                printf("R.A: %d  M.AT: %d subtraction: %d\n", r.a, m.at[m.at[op1] + r.y], aux);
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux)
                r.p[CARRY]    = r.a >= m.at[m.at[op1] + r.y];
                break;
        // TODO: implement the CPX and CPY
        }
    }

    void execute() {
        data_transfers();
        stack_operations();
        data_processing();
        comp_branch();
    }

    void read_binary_program(const char * filename) {
        std::ifstream input(filename, std::ios::binary);
        size_t i = 0;
        while (input) {
            char b;
            input.get(b);
            if (input)
                m.at[i++] = uint8_t(b);
        }
    }

public:
    Processor(uint8_t stack, uint16_t starting_pc) : 
            r(stack, starting_pc),
            m(MEM_SIZE) {
        // read_binary_program(PROGRAM);

        // Information about the array
        m.at[0x0000] = 0x10;    // Starting addres of the array (low)
        m.at[0x0001] = 0x00;    // Starting addres of the array (high)
        m.at[0x0002] = 0xaa;    // Flag (exchanged?)
        // m.at[0x0003] = 0x00;
        // m.at[0x0004] = 0x00;
        // m.at[0x0005] = 0x00;
        // m.at[0x0006] = 0x00;
        // m.at[0x0007] = 0x00;
        m.print_mem_interval(0x0000, 0x0002, false);

        // Array to be sorted
        m.at[0x0010] = 0x06;    // First byte is the length of the list
        m.at[0x0011] = 0x04;
        m.at[0x0012] = 0x07;
        m.at[0x0013] = 0x01;
        m.at[0x0014] = 0x02;
        m.at[0x0015] = 0x01;
        m.at[0x0016] = 0x03;
        m.print_mem_interval(0x0010, 0x0016, false);

        // Program
        m.at[0x8000] = 0xa0;    // LDY #0       ; _start: Clear Y
        m.at[0x8001] = 0x00;
        m.at[0x8002] = 0x84;    // STY $2       ; Flag <- FALSE
        m.at[0x8003] = 0x02;
        m.at[0x8004] = 0xb1;    // LDA ($00),Y  ; Load qty of elements in array
        m.at[0x8005] = 0x00;
        m.at[0x8006] = 0xaa;    // TAX          ; Store qty in X
        m.at[0x8007] = 0xc8;    // INY          ; Point to the next byte
        m.at[0x8008] = 0xca;    // DEX          ; One element less
        m.at[0x8009] = 0xb1;    // LDA ($00),Y  ; _next: Load the y'th element
        m.at[0x800a] = 0x00;
        m.at[0x800b] = 0xc8;    // INY
        m.at[0x800c] = 0xd1;    // CMP ($00),Y  ; Compare with next element
        m.at[0x800d] = 0x00;
        m.at[0x800e] = 0x90;    // BCC _check   ; Smaller?
        m.at[0x800f] = 0x12;
        m.at[0x8010] = 0xf0;    // BEQ _check   ; Equal?
        m.at[0x8011] = 0x10;
        m.at[0x8012] = 0x48;    // PHA          ; Bigger! Need to exchange
        m.at[0x8013] = 0xb1;    // LDA ($00),Y  ; Get the next element
        m.at[0x8014] = 0x00;
        m.at[0x8015] = 0x88;    // DEY          ; Point to small ele position
        m.at[0x8016] = 0x91;    // STA ($00),Y  ; Store small ele correctly
        m.at[0x8017] = 0x00;
        m.at[0x8018] = 0x68;    // PLA          ; Get the bigger ele from stack
        m.at[0x8019] = 0xc8;    // INY          ; Poing to big ele position
        m.at[0x801a] = 0x91;    // STA ($00),Y  ; Store big ele correctly
        m.at[0x801b] = 0x00;
        m.at[0x801c] = 0xa9;    // LDA #$FF     ; A <- 0xFF
        m.at[0x801d] = 0xff;
        m.at[0x801e] = 0x85;    // STA $2       ; Flag <- TRUE
        m.at[0x801f] = 0x02;
        m.at[0x8020] = 0xca;    // DEX          ; _check:
        m.at[0x8021] = 0xd0;    // BNE _next    ;
        m.at[0x8022] = 0xe8;
        m.at[0x8023] = 0x24;    // BIT $2       ; Swapped anything?
        m.at[0x8024] = 0x02;
        m.at[0x8025] = 0x30;    // BMI _start   ; If yes, traverse once more
        m.at[0x8026] = 0xdb;
        // TODO: implement RTS
        m.at[0x8027] = 0x00;    // RTS          ; End of function!
        m.at[0x8028] = 0x00;    // 
        m.print_mem_interval(0x8000, 0x8010, true);
    }

    void exec_n_inst(size_t const qty) {
        for(size_t i = 0; i < qty; ++i) {
            fetch();
            printf("\n");
            opc::print_inst(instr);
            printf("\n");
            execute();
            r.print_regs();
            m.print_mem_interval(0x0011, 0x0016, false);
            m.print_mem_interval(0x0002, 0x0002, false);
        }
    }
};
