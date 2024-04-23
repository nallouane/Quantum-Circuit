#include "../h_files/Circuit.h"


Circuit::Circuit(int num_qubits) : qubits(num_qubits), stateVector(1 << num_qubits, 1) {        
    if (num_qubits < 1) {
        throw std::invalid_argument("Number of qubits must be a positive integer");
    }        
    auto identity_gate = std::make_shared<Identity>();

    for (int timestep = 0; timestep < 1; ++timestep) {
        std::vector<std::shared_ptr<QuantumComponent>> timestep_gates;

        for (int qubit = 0; qubit < num_qubits; ++qubit) {
            timestep_gates.push_back(identity_gate);
        }

        Qcircuit.push_back(timestep_gates);
    }
    stateVector(1,1) = Complex(1, 0);
}

// Copy constructor
Circuit::Circuit(const Circuit& other)
: qubits(other.qubits), stateVector(other.stateVector),
  componentLibrary(other.componentLibrary) {
    for (const auto& timestep : other.Qcircuit) {
        std::vector<std::shared_ptr<QuantumComponent>> newTimestep;
        for (const auto& component : timestep) {
            newTimestep.push_back(component->clone());
        }
        Qcircuit.push_back(newTimestep);
    }
}

// Copy assignment operator
Circuit& Circuit::operator=(const Circuit& other) {
    if (this != &other) {
        qubits = other.qubits;
        stateVector = other.stateVector;
        componentLibrary = other.componentLibrary; 
        Qcircuit.clear();
        for (const auto& timestep : other.Qcircuit) {
            std::vector<std::shared_ptr<QuantumComponent>> newTimestep;
            for (const auto& component : timestep) {
                newTimestep.push_back(component->clone());
            }
            Qcircuit.push_back(newTimestep);
        }
    }
    return *this;
}



void Circuit::initializeStateVector(const std::vector<Complex>& initialValues) {
    if (initialValues.size() != stateVector.getRows()) {
        throw std::invalid_argument("Invalid initial state vector size");
    }

    for (int i = 1; i <= initialValues.size(); i++) {
        stateVector(i, 1) = initialValues[i - 1];
    }

    std::cout << "Initialized state vector"<< stateVector<<"\n";
}

void Circuit::addGate(std::shared_ptr<QuantumComponent> gate, int qubit, int timestep) {
    if (timestep < 0) {
        throw std::invalid_argument("Timestep cannot be negative");
    }

    if (qubit < 0 || qubit >= qubits) {
        throw std::invalid_argument("Qubit out of range");
    }

    // Check if we need to add more timesteps
    while (Qcircuit.size() <= timestep) {
        std::vector<std::shared_ptr<QuantumComponent>> new_timestep(qubits, std::make_shared<Identity>());
        Qcircuit.push_back(new_timestep);
    }

    // Replace the gate at the specified qubit and timestep
    Qcircuit[timestep][qubit] = gate;
}

void Circuit::addComponentToLibrary(const std::string& name) {
    std::shared_ptr<QuantumComponent> component = QuantumComponentFactory::create(name);
    if (component) {
        componentLibrary.push_back(component);
    } else {
        std::cout << "Failed to add component: " << name << std::endl;
    }
}


Matrix Circuit::calculateTimestepMatrix(int timestep) const {
    if (timestep < 0 || timestep >= Qcircuit.size()) {
        throw std::out_of_range("Timestep out of range");
    }

    // Initialize the result to be the 1x1 identity matrix.
    Matrix result = Matrix::identityMatrix(1);  

    // Iterate over the qubits
    for (int qubit = 0; qubit < qubits; ++qubit) {
        // Get the gate that acts on the current qubit at the given timestep
        auto gate = Qcircuit[timestep][qubit];
        
        // Get the matrix of the gate
        Matrix currentMatrix = gate->getMatrix();

        // Calculate the Kronecker product of the result and the current matrix
        result = Matrix::kroneckerProduct(currentMatrix, result);
    }

    return result;
}

Matrix Circuit::calculateTotalMatrix() const {
    // Start with the identity matrix
    Matrix totalMatrix = Matrix::identityMatrix(1 << qubits);

    // Iterate over the timesteps
    for (int timestep = 0; timestep < Qcircuit.size(); ++timestep) {
        // Calculate the matrix for the current timestep
        Matrix timestepMatrix = calculateTimestepMatrix(timestep);

        // Multiply the total matrix by the timestep matrix
        totalMatrix = timestepMatrix * totalMatrix;
    }

    return totalMatrix;
}

void Circuit::configureCircuit() {
    std::string gateName;
    int qubit, timestep;
    char addMore = 'y';

    std::cout << "\n Available gates:\n\n";
    std::cout << "----------------\n";
    std::cout << "Hadamard\n";
    std::cout << "Pauli-X\n";
    std::cout << "Pauli-Y\n";
    std::cout << "Pauli-Z\n";
    std::cout << "CNOTcontrol\n";
    std::cout << "CNOTtarget\n";
    std::cout << "Toffoli\n";
    std::cout << "Identity\n";
    std::cout << "S-Gate\n";
    std::cout << "T-Gate\n";


    // Ask user to add gates to the library
    while (addMore == 'y' || addMore == 'Y') {
        std::cout << "\n Enter the name of the gate you want to add to the library: ";
        std::cin >> gateName;

        auto gate = QuantumComponentFactory::create(gateName);
        if (!gate) {
            std::cout << "Invalid gate name.\n";
            continue;
        }

        addComponentToLibrary(gateName);
        std::cout << "Gate added to the library.\n";

        std::cout << "Do you want to add more gates to the library? (y/n): ";
        std::cin >> addMore;
    }

    // Print gates in the library
    std::cout << "\nGates in the library:\n";
    for (const auto& gate : componentLibrary) {
        std::cout << gate->getName() << '\n';
    }

    // Ask user to add gates to the circuit
    addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        std::cout << "\nEnter the gate name to add to the circuit: ";
        std::cin >> gateName;

        // Check if the gate exists in the library
        std::shared_ptr<QuantumComponent> gate;
        for (const auto& component : componentLibrary) {
            if (component->getName() == gateName) {
                gate = component;
                break;
            }
        }

        if (!gate) {
            std::cout << "The specified gate is not in the library.\n";
            continue;
        }

        std::cout << "Enter the timestep for this gate (0 based indexing applies): ";
        int timestep;

        while(!(std::cin >> timestep) || timestep < 0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Timestep must be a non-negative integer. Please try again: ";
        }


        std::cout << "Enter the target qubit for this gate (0 based indexing applies): ";
        int qubit;

        while(!(std::cin >> qubit) || qubit < 0 || qubit >= qubits){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Qubit index must be a non-negative integer less than " << qubits << ". Please try again: ";
        }

        // Add the gate to the circuit
        addGate(gate, qubit, timestep);

        std::cout << "Do you want to add more gates to the circuit? (y/n): ";
        std::cin >> addMore;
  
    }

applyCircuit();    
printCircuit();      

}

void Circuit::applyCircuit() {
    // Calculate the total matrix of the circuit
    Matrix totalMatrix = calculateTotalMatrix();

    // Multiply the state vector by the total matrix
    stateVector = totalMatrix * stateVector;
    std::cout << " Superposition State :\n" << stateVector << '\n';
    // Output the probability amplitude for each state
    for (int i = 1; i < stateVector.getRows()+ 1; ++i) {

    Complex amplitude = stateVector(i, 1);
    double probability = pow(amplitude.modulus(), 2);
    // Check if the probability isn't zero
    if (probability != 0) {
        std::cout << "State |" << i - 1  << ">: Amplitude = " << amplitude 
                  << ", Probability = " << probability << '\n';
    }
}

}

void Circuit::printCircuit() const {
    std::string horizontal_line = "-----";
    std::string vertical_line = "|";
    int max_gate_name_length = 4;  // default minimum length for gate name

    // Calculate the maximum gate name length
    for (const auto& timestep : Qcircuit) {
        for (const auto& gate : timestep) {
            int gate_name_length = gate->getName().length();
            if (gate_name_length > max_gate_name_length) {
                max_gate_name_length = gate_name_length;
            }
        }
    }

    // Print header
    std::cout << "\033[1m" << "Quantum Circuit: " << "\033[0m" << "\n";
    std::cout << "Number of qubits: " << qubits << "\n";
    std::cout << "Number of timesteps: " << Qcircuit.size() << "\n\n";

    // Print each qubit
    for (int i = 0; i < qubits; i++) {
        std::cout << "Qubit " << i + 1 << ": ";
        
        // Print gates in each timestep
        for (const auto& timestep : Qcircuit) {
            std::cout << vertical_line << std::setw(max_gate_name_length) << std::left 
                      << timestep[i]->getName() << vertical_line;
            
            std::cout << horizontal_line;
        }
        std::cout << "\n";
    }
std::cout << "\n\n\n";
}