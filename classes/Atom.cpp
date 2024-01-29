#include "headers/Atom.h"

Coordinate Atom::SumOfFlows() const noexcept {
    Coordinate sum;
    for (const Coordinate& other_atom : this->Verle()) {
        sum += (this->Coor() - other_atom) * Flow(Distance(this->Coor(), other_atom));
    }
    return sum;
}

double Flow(double distance) noexcept { return Forse(distance) / distance; }

double Forse(double distance) noexcept {
    return 2 * ALPHA * D *
           (exp(-2. * ALPHA * (distance - EQUAL_DIST) - exp(-ALPHA * (distance - EQUAL_DIST))));
}

double Potential(double distance) noexcept {
    const double x = (1 - exp(-ALPHA * (distance - EQUAL_DIST)));
    return D * (1 - x) * (1 - x);
}