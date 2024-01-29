#pragma once

#include <initializer_list>
#include <vector>

#include "Coordinate.h"

class Cell {
   public:
    Cell(std::vector<Coordinate> coordinates_vec, double x_size, double y_size, double z_size)
        : coordinates_vec(std::move(coordinates_vec)),
          x_size(x_size),
          y_size(y_size),
          z_size(z_size) {}
    Cell(std::vector<Coordinate> coordinates_vec, double size)
        : coordinates_vec(std::move(coordinates_vec)), x_size(size), y_size(size), z_size(size) {}

    [[nodiscard]] const std::vector<Coordinate>& CoordinatesVec() const noexcept {
        return coordinates_vec;
    }
    [[nodiscard]] std::vector<Coordinate>& CoordinatesVec() noexcept { return coordinates_vec; }
    [[nodiscard]] double XSize() const noexcept { return x_size; }
    [[nodiscard]] double YSize() const noexcept { return y_size; }
    [[nodiscard]] double ZSize() const noexcept { return z_size; }

   private:
    std::vector<Coordinate> coordinates_vec;
    double x_size, y_size, z_size;
};
