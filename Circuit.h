#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <memory>
#include <algorithm>
#include <complex>
#include <limits>

#include "Matrix.h"               
#include "Gates.h"     
#include "Complex.h"             

class Circuit {
private:
    int qubits;
    Matrix stateVector;
    std::vector<std::vector<std::shared_ptr<QuantumComponent>>> Qcircuit;  // outer vector: timesteps, inner vector: gates for each qubit
    std::vector<std::shared_ptr<QuantumComponent>> componentLibrary;

public:
    // Constructor
    Circuit(int num_qubits);
    // Copy constructor & assignment operator
    Circuit(const Circuit& other);
    Circuit& operator=(const Circuit& other);

    // Initialization methods
    void initializeStateVector(const std::vector<Complex>& initialValues);
    void addGate(std::shared_ptr<QuantumComponent> gate, int qubit, int timestep);
    void addComponentToLibrary(const std::string& name);

    // Calculation methods
    Matrix calculateTimestepMatrix(int timestep) const;
    Matrix calculateTotalMatrix() const;

    // Circuit configuration and application
    void configureCircuit();
    void applyCircuit();

    // Printing
    void printCircuit() const;
};

#endif // CIRCUIT_H
