#include <iostream>
#include <memory> 
#include "Complex.h"
#include "Matrix.h"
#include "Gates.h"
#include "Circuit.h"

int main() {
    
    std::cout << "\n" "Welcome to the Quantum Circuit Simulator!\n"
            "You can create your circuits by declaring them. While this function is designed to enhance user functionality, "
            "it's not necessary to use it for basic operations. Feel free to explore all the gates defined in the 'gates.h' file. "
            "Enjoy your quantum computing journey!" << std::endl;

    //Example 2 qubit circuit. 
    Circuit circuit(2);

    circuit.configureCircuit();

    return 0;
}
