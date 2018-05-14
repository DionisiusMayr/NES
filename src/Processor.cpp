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
                break;
            case 0xa5:  // LDA oper
                r.a = m.at[op1];
                break;
            case 0xb5:  // LDA oper,X
                r.a = m.at[op1 + r.x];
                break;
            case 0xad:  // LDA oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[addr];
                break;
            case 0xbd:  // LDA oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[addr + r.x];
                break;
            case 0xb9:  // LDA oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.a = m.at[addr + r.y];
                break;
            case 0xa1:  // LDA (oper,X)
                // TODO: implement this
                break;
            case 0xb1:  // LDA (oper),Y
                // TODO: implement this
                break;

            /* LDX */
            case 0xa2:  // LDX #oper
                r.x = op1;
                break;
            case 0xa6:  // LDX oper
                r.x = m.at[op1];
                break;
            case 0xb6:  // LDX oper,Y
                r.x = m.at[op1 + r.y];
                break;
            case 0xae:  // LDX oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.x = m.at[addr];
                break;
            case 0xbe:  // LDX oper,Y
                addr = ((uint16_t)op1 << 8) | op2;
                r.x = m.at[addr + r.y];
                break;

            /* LDY */
            case 0xa0:  // LDY #oper
                r.y = op1;
                break;
            case 0xa4:  // LDY oper
                r.y = m.at[op1];
                break;
            case 0xb4:  // LDY oper,X
                r.y = m.at[op1 + r.x];
                break;
            case 0xac:  // LDY oper
                addr = ((uint16_t)op1 << 8) | op2;
                r.y = m.at[addr];
                break;
            case 0xbc:  // LDY oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                r.y = m.at[addr + r.x];
                break;
        }

        r.p[NEGATIVE] = _sign(r.a);
        r.p[ZERO]     = _zero(r.a);
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
                // TODO: implement this
                break;
            case 0x91:  // STA (oper),Y
                // TODO: implement this
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

    void execute() {
        uint8_t op1 = instr.byte1;
        uint8_t op2 = instr.byte2;
        uint8_t aux = 0;
        int16_t addr;

        switch (instr.opc) {
            int int_res;
            case 0x09:  // ORA #oper
                r.a = r.a | op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x0a:  // ASL A
                r.p[CARRY]    = r.a && 0x80;
                r.a = r.a << 1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x18:  // CLC
                r.p[CARRY] = 0;
                break;
            case 0x29:  // AND #oper
                r.a = r.a & op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
                break;
            case 0x49:  // EOR #oper
                r.a = r.a ^ op1;
                r.p[NEGATIVE] = _sign(r.a);
                r.p[ZERO]     = _zero(r.a);
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
            case 0xe6:  // INC oper
                aux = ++m.at[op1];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xee:  // INC oper
                break;
            case 0xf6:  // INC oper,X
                aux = ++m.at[op1 + r.x];
                r.p[NEGATIVE] = _sign(aux);
                r.p[ZERO]     = _zero(aux);
                break;
            case 0xfe:  // INC oper,X
                addr = ((uint16_t)op1 << 8) | op2;
                std::cout << dec_hex_bin_16(addr);

                break;
        }
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
    Processor() : r(), m(MEM_SIZE) {
        read_binary_program(PROGRAM);

        m.at[0] = 0x69;
        m.at[1] = 0xc0;
        m.at[2] = 0xfe;
        m.at[3] = 0x01;
        m.at[4] = 0x0a;
        m.at[5] = 0x0a;
        m.at[6] = 0x0a;
        // m.at[2] = 0x29;
        // m.at[3] = 0x00;
        m.print_mem_interval(0,5);
    }

    void exec_n_inst(size_t const qty) {
        for(size_t i = 0; i < qty; ++i) {
            fetch();
            printf("\n");
            opc::print_inst(instr);
            execute();
            r.print_regs();
        }
    }
};
