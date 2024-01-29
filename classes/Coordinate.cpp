#include "headers/Coordinate.h"

std::ostream &operator<<(std::ostream &out, const Coordinate &vec) {
    out << std::setprecision(10) << vec.x << " " << vec.y << " " << vec.z;
    return out;
}

double Distance(const Coordinate &first, const Coordinate &second) noexcept {
    return sqrt((first.x - second.x) * (first.x - second.x) +
                (first.y - second.y) * (first.y - second.y) +
                (first.z - second.z) * (first.z - second.z));
}