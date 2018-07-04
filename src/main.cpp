#include <iostream>
#include "Registers.cpp"
#include "Memory.cpp"
#include "Processor.cpp"

using std::cout;
using std::endl;

int main() {
    int qty;
    Processor proc(0xff, 0x8000);
    while (std::cin >> qty)
        proc.exec_n_inst(qty);
}
