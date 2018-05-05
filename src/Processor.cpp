#include "Registers.cpp"
#include "Memory.cpp"
#include "Opcodes.cpp"
#include "Instruction.cpp"
#include "utility.cpp"
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <fstream>

#define MEM_SIZE 1024
#define PROGRAM "./programs/test.6502"
#define _zero(byte) (byte == 0 ? 1 : 0);
#define _sign(byte) (byte & 0b10000000 ? 1 : 0);
#define _carry(integer) (integer & 0b100000000 ? 1 : 0);

class Processor {
    private:
        Registers r;
        Memory    m;
        Instruction inst;

        void fetch() {
            inst = m.at[r.pc];
            inst.byte1 = m.at[r.pc + 1];
            inst.byte2 = m.at[r.pc + 2];
            r.pc += inst.get_size();
        }

        void execute(Instruction instr) {
            uint8_t op1 = instr.byte1;
            // uint8_t op2 = instr.byte2;
            Registers r2;
            switch (instr.opc) {
                int int_res;
                case 0x09:  // ORA #oper
                    r.a = r.a | op1;
                    r.p[NEGATIVE] = _sign(r.a);
                    r.p[ZERO]     = _zero(r.a);
                    break;
                case 0x0a:  // ASL A
                    int_res = int(r.a) << 1;
                    r.a = r.a << 1;
                    r.p[NEGATIVE] = _sign(r.a);
                    r.p[ZERO]     = _zero(r.a);
                    r.p[CARRY]    = _carry(int_res);
                    break;
                case 0x18:  // CLC
                    r.p[CARRY] = 0;
                    break;
                case 0x29:  // AND #oper
                    r.a = r.a & op1;
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
            }
        }

    public:
        Processor() : r(), m(MEM_SIZE) {
            // Read binary data
            std::ifstream input(PROGRAM, std::ios::binary);
            size_t i = 0;
            while (input) {
                char b;
                input.get(b);
                if (input)
                    m.at[i++] = uint8_t(b);
            }

            m.at[0] = 0x69;
            m.at[1] = 0xf0;
            m.at[2] = 0x0a;
            m.at[3] = 0x0a;
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
                opc::print_inst(inst);
                execute(inst);
                r.print_regs();
            }
        }
};
