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

class Processor {
    private:
        Registers r;
        Memory    m;
        Instruction inst;

        void execute(Instruction instr) {
            Registers r2;
            switch (instr.opc) {
                case 0x69:  // ADC #oper
                    r2.a = r.a + instr.byte1 + r.p[CARRY];
                    int int_res = int(r.a) + int(instr.byte1) + int(r.p[CARRY]);
                    r2.p[NEGATIVE] = r2.a & 0b1000000 ? 1 : 0;
                    r2.p[ZERO] = r2.a == 0 ? 1 : 0;
                    r2.p[CARRY] = int_res & 0b10000000 ? 1 : 0;
                    r2.p[OVERFLOW] = int_res > 127 || int_res < -128;
                    break;
            }
        }

    public:
        Processor() : r(), m(MEM_SIZE) {
            std::ifstream input(PROGRAM, std::ios::binary);
            size_t i = 0;
            while (input) {
                char b;
                input.get(b);
                if (input)
                    m.at[i++] = uint8_t(b);
            }
            // m.at[0] = 0x69;
            // m.at[1] = 0x04;
            m.print_mem_interval(0,5);
        }

        void fetch() {
            inst = m.at[r.pc];
            inst.byte1 = m.at[r.pc + 1];
            inst.byte2 = m.at[r.pc + 2];
            r.pc += inst.get_size();
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
