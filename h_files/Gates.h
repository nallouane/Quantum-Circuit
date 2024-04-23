#ifndef GATES_H
#define GATES_H
#include <cmath>
#include <memory>
#include <iostream>
#include "Matrix.h"
#include "Complex.h"

class QuantumComponent {
public:
    virtual ~QuantumComponent() = default;
    virtual Matrix getMatrix() const = 0;
    virtual std::string getName() const = 0;
    virtual std::shared_ptr<QuantumComponent> clone() const = 0;  //clone method to allow copy of circuits
};

class QuantumComponentFactory {
public:
    static std::shared_ptr<QuantumComponent> create(const std::string& name);
};

class HadamardGate : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class PauliXGate : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class PauliYGate : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class PauliZGate : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class CNOTcontrol : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class CNOTtarget : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class ToffoliGatetarget : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class Identity : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class SGate : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

class TGate : public QuantumComponent {
public:
    Matrix getMatrix() const override;
    std::string getName() const override;
    std::shared_ptr<QuantumComponent> clone() const override;
};

#endif // GATES_H