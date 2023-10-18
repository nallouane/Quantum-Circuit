#include "Gates.h"

std::shared_ptr<QuantumComponent> QuantumComponentFactory::create(const std::string& name) {
    if (name == "Hadamard") {
        return std::make_shared<HadamardGate>();
    }
    else if (name == "Pauli-X") {
        return std::make_shared<PauliXGate>();
    }
    else if (name == "Pauli-Y") {
        return std::make_shared<PauliYGate>();
    }
    else if (name == "Pauli-Z") {
        return std::make_shared<PauliZGate>();
    }
    else if (name == "CNOTcontrol") {
        return std::make_shared<CNOTcontrol>();
    }
    else if (name == "CNOTtarget") {
        return std::make_shared<CNOTtarget>();
    }
    else if (name == "Identity") {
        return std::make_shared<Identity>();
    }
    else if (name == "S-Gate") {
        return std::make_shared<SGate>();
    }
    else if (name == "T-Gate") {
        return std::make_shared<TGate>();
    }
    else if (name == "Toffoli") {
        return std::make_shared<ToffoliGatetarget>();
    }
    else {
        throw std::invalid_argument("Invalid gate name");
    }
}

Matrix HadamardGate::getMatrix() const {
    Matrix H(2, 2);
    double h = 1.0 / std::sqrt(2);
    H(1, 1) = Complex(h, 0);
    H(1, 2) = Complex(h, 0);
    H(2, 1) = Complex(h, 0);
    H(2, 2) = Complex(-h, 0);
    return H;
}

std::string HadamardGate::getName() const {
    return "Hadamard";
}

Matrix PauliXGate::getMatrix() const {
    Matrix X(2, 2);
    X(1, 2) = Complex(1, 0);
    X(2, 1) = Complex(1, 0);
    return X;
}

std::string PauliXGate::getName() const {
    return "Pauli-X";
}

Matrix PauliYGate::getMatrix() const {
    Matrix Y(2, 2);
    Y(1, 2) = Complex(0, -1);
    Y(2, 1) = Complex(0, 1);
    return Y;
}

std::string PauliYGate::getName() const {
    return "Pauli-Y";
}

Matrix PauliZGate::getMatrix() const {
    Matrix Z(2, 2);
    Z(1, 1) = Complex(1, 0);
    Z(2, 2) = Complex(-1, 0);
    return Z;
}

std::string PauliZGate::getName() const {
    return "Pauli-Z";
}

Matrix CNOTcontrol::getMatrix() const {
    Matrix I(1, 1);
    I(1, 1) = Complex(1, 0);
    return I;
}

std::string CNOTcontrol::getName() const {
    return "CNOTcontrol";
}

Matrix CNOTtarget::getMatrix() const {
    Matrix C(4, 4);
    C(1, 1) = Complex(1, 0);
    C(2, 2) = Complex(1, 0);
    C(3,4) = Complex(1, 0);
    C(4, 3) = Complex(1, 0);
    return C;
}

std::string CNOTtarget::getName() const {
    return "CNOTtarget";
}

Matrix Identity::getMatrix() const {
    Matrix I(2, 2);
    I(1, 1) = Complex(1, 0);
    I(2, 2) = Complex(1, 0);
    return I;
}

std::string Identity::getName() const {
    return ".";
}

Matrix SGate::getMatrix() const {
    Matrix S(2, 2);
    S(1, 1) = Complex(1, 0);
    S(2, 2) = Complex(0, 1);  // i
    return S;
}

std::string SGate::getName() const {
    return "S-Gate";
}

Matrix TGate::getMatrix() const {
    Matrix T(2, 2);
    T(1, 1) = Complex(1, 0);
    T(2, 2) = Complex(std::cos(M_PI/4), std::sin(M_PI/4));  // e^(iπ/4)
    return T;
}

std::string TGate::getName() const {
    return "T-Gate";
}

Matrix ToffoliGatetarget::getMatrix() const {
    Matrix Toffoli(8, 8);
    Toffoli(1, 1) = Complex(1, 0);
    Toffoli(2, 2) = Complex(1, 0);
    Toffoli(3, 3) = Complex(1, 0);
    Toffoli(4, 4) = Complex(1, 0);
    Toffoli(5, 5) = Complex(1, 0);
    Toffoli(6, 6) = Complex(1, 0);
    Toffoli(7, 8) = Complex(1, 0);
    Toffoli(8, 7) = Complex(1, 0);
    return Toffoli;
}

std::string ToffoliGatetarget::getName() const {
    return "Toffoli";
}

std::shared_ptr<QuantumComponent> HadamardGate::clone() const {
    return std::make_shared<HadamardGate>(*this);
}

std::shared_ptr<QuantumComponent> PauliXGate::clone() const {
    return std::make_shared<PauliXGate>(*this);
}

std::shared_ptr<QuantumComponent> PauliYGate::clone() const {
    return std::make_shared<PauliYGate>(*this);
}

std::shared_ptr<QuantumComponent> PauliZGate::clone() const {
    return std::make_shared<PauliZGate>(*this);
}

std::shared_ptr<QuantumComponent> CNOTcontrol::clone() const {
    return std::make_shared<CNOTcontrol>(*this);
}

std::shared_ptr<QuantumComponent> CNOTtarget::clone() const {
    return std::make_shared<CNOTtarget>(*this);
}

std::shared_ptr<QuantumComponent> Identity::clone() const {
    return std::make_shared<Identity>(*this);
}

std::shared_ptr<QuantumComponent> SGate::clone() const {
    return std::make_shared<SGate>(*this);
}

std::shared_ptr<QuantumComponent> TGate::clone() const {
    return std::make_shared<TGate>(*this);
}

std::shared_ptr<QuantumComponent> ToffoliGatetarget::clone() const {
    return std::make_shared<ToffoliGatetarget>(*this);
}

 

