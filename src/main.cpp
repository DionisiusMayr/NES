#include <iostream>
#include "Registers.cpp"
#include "Memory.cpp"

using std::cout;
using std::endl;

int main() {
    cout << "First commit" << endl;
    Registers regs;
    regs.print_regs();
    Memory mem(8096);
    mem.at[2] = 0xff;
    mem.print_mem_interval(1,5);
}
