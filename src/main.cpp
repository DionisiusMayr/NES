#include <iostream>
#include "Registers.cpp"
#include "Memory.cpp"
#include "Processor.cpp"

using std::cout;
using std::endl;

int main() {
    cout << "First commit" << endl;
    Registers regs;
    // regs.print_regs();
    Processor proc;
    proc.exec_n_inst(3);
}
