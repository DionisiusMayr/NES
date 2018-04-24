#include "Registers.cpp"
#include "Memory.cpp"
#include "Opcodes.cpp"
#include <cstdio>

#define MEM_SIZE 1024

class Processor {
    private:
        Registers r;
        Memory    m;
    public:
        Processor() : r(), m(MEM_SIZE) {
            m.at[0] = 4;
        }

        void fetch() {
            uint8_t instruction = m.at[r.pc];
            // TODO: check if the increment is always 1 byte.
            ++r.pc;
            opc::print_inst(instruction);
        }
};
