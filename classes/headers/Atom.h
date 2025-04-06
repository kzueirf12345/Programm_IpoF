#pragma once

#include <functional>

#include "Constants.h"
#include "Coordinate.h"

class Atom {
   public:
    Atom(Coordinate coor) : coor(std::move(coor)) {}
    Atom(Coordinate coor, std::vector<Coordinate> verle)
        : coor(std::move(coor)), verle(std::move(verle)) {}

    [[nodiscard]] const std::vector<Coordinate> &Verle() const noexcept { return verle; }
    [[nodiscard]] std::vector<Coordinate> &Verle() noexcept { return verle; }
    [[nodiscard]] Coordinate &Coor() noexcept { return coor; }
    [[nodiscard]] const Coordinate &Coor() const noexcept { return coor; }

    bool operator==(const Atom &other) const noexcept { return this->coor == other.coor; }
    bool operator!=(const Atom &other) const noexcept { return this->coor != other.coor; }
    bool operator<(const Atom &other) const noexcept { return this->coor < other.coor; }

   private:
    Coordinate coor;
    std::vector<Coordinate> verle;
};

//ты чмо <3